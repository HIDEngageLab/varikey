/**
 * \file cmd_feature.cpp
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */
/**
    \brief Event handling

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#include "cmd_feature.hpp"
#include "board.hpp"
#include "checksum.hpp"
#include "cmd_backlight_msg.hpp"
#include "cmd_display_msg.hpp"
#include "cmd_gpio_msg.hpp"
#include "cmd_keypad_msg.hpp"
#include "commander.hpp"
#include "engine.hpp"
#include "gpio_defines.hpp"
#include "param_keypad.hpp"
#include "parameter.hpp"
#include "payload_gpio.hpp"
#include "payload_identifier.hpp"
#include "serial_frame.hpp"
#include "usart.hpp"
#include "varikey.hpp"

namespace engine
{
    namespace hci
    {
        namespace cmd
        {
            namespace feature
            {
                static const uint8_t MAX_NUMBER_OF_RETRY = 3;

                /**
                 * \brief handle backlight request
                 *
                 * \param _chunk
                 */
                extern void backlight_request(chunk_t const *const _chunk)
                {
                    backlight::message_t msg;
                    backlight::request(_chunk, &msg);
                    backlight::confirmation(&msg);
                }

                /**
                 * \brief handle display request
                 *
                 * \param _chunk
                 */
                extern void display_request(chunk_t const *const _chunk)
                {
                    display::message_t msg;
                    display::request(_chunk, &msg);
                    display::confirmation(&msg);
                }

                /**
                 * \brief Module local GPIO interrupt handler
                 *
                 * \param _identifier
                 * \param _level
                 */
                void gpio_callback(uint8_t _identifier, bool _level)
                {
                    using IDENTIFIER = engine::payload::gpio::IDENTIFIER;
                    using LEVEL = engine::payload::gpio::LEVEL;

                    IDENTIFIER identifier{IDENTIFIER::UNDEFINED};
                    LEVEL level = LEVEL::UNDEFINED;
                    switch (_identifier)
                    {
                    case 0:
                        identifier = IDENTIFIER::PIN1;
                        break;
                    case 1:
                        identifier = IDENTIFIER::PIN2;
                        break;
                    case 2:
                        identifier = IDENTIFIER::PIN3;
                        break;
                    case 3:
                        identifier = IDENTIFIER::PIN4;
                        break;
                    default:
                        break;
                    }
                    if (_level)
                    {
                        level = LEVEL::HIGH;
                    }
                    else
                    {
                        level = LEVEL::LOW;
                    }
                    gpio_indication(identifier, level);
                }

                /**
                    \brief Handle gpio request
                */
                extern void gpio_request(chunk_t const *const _chunk)
                {
                    gpio::message_t msg;
                    gpio::request(_chunk, &msg);

                    msg.result = gpio::RESULT::FAILURE;

                    platform::driver::soc::gpio::IDENTIFIER identifier;
                    switch (msg.content.identifier)
                    {
                    case payload::gpio::IDENTIFIER::PIN1:
                        identifier = platform::driver::soc::gpio::IDENTIFIER::GPIO0;
                        break;
                    case payload::gpio::IDENTIFIER::PIN2:
                        identifier = platform::driver::soc::gpio::IDENTIFIER::GPIO1;
                        break;
                    case payload::gpio::IDENTIFIER::PIN3:
                        identifier = platform::driver::soc::gpio::IDENTIFIER::GPIO2;
                        break;
                    case payload::gpio::IDENTIFIER::PIN4:
                        identifier = platform::driver::soc::gpio::IDENTIFIER::GPIO3;
                        break;
                    default:
                        msg.result = gpio::RESULT::WRONG_IDENTIFIER;
                        break;
                    }

                    if (msg.result != gpio::RESULT::WRONG_IDENTIFIER)
                    {
                        switch (msg.content.function)
                        {
                        case payload::gpio::FUNCTION::DIRECTION_GET:
                        {
                            platform::driver::soc::gpio::DIRECTION direction = board.soc.get_gpio_direction(identifier);
                            msg.result = gpio::RESULT::SUCCESS;
                            switch (direction)
                            {
                            case platform::driver::soc::gpio::DIRECTION::INPUT:
                                msg.content.direction = payload::gpio::DIRECTION::INPUT;
                                break;
                            case platform::driver::soc::gpio::DIRECTION::OUTPUT:
                                msg.content.direction = payload::gpio::DIRECTION::OUTPUT;
                                break;
                            default:
                                msg.content.direction = payload::gpio::DIRECTION::UNDEFINED;
                                msg.result = gpio::RESULT::WRONG_DIRECTION;
                                break;
                            }
                        }
                        case payload::gpio::FUNCTION::DIRECTION_SET:
                            msg.result = gpio::RESULT::SUCCESS;
                            switch (msg.content.direction)
                            {
                            case payload::gpio::DIRECTION::INPUT:
                                board.soc.set_gpio_direction(identifier, platform::driver::soc::gpio::DIRECTION::INPUT);
                                break;
                            case payload::gpio::DIRECTION::OUTPUT:
                                board.soc.set_gpio_direction(identifier, platform::driver::soc::gpio::DIRECTION::OUTPUT);
                                break;
                            default:
                                msg.result = gpio::RESULT::WRONG_DIRECTION;
                                break;
                            }
                            break;
                        case payload::gpio::FUNCTION::ENABLE:
                            msg.result = gpio::RESULT::SUCCESS;
                            board.soc.enable_gpio_event(gpio_callback, true);
                            break;
                        case payload::gpio::FUNCTION::DISABLE:
                            msg.result = gpio::RESULT::SUCCESS;
                            board.soc.enable_gpio_event(gpio_callback, false);
                            break;
                        case payload::gpio::FUNCTION::LEVEL_GET:
                        {
                            platform::driver::soc::gpio::VALUE value = board.soc.get_value(identifier);
                            msg.result = gpio::RESULT::SUCCESS;
                            switch (value)
                            {
                            case platform::driver::soc::gpio::VALUE::LOW:
                                msg.content.level = payload::gpio::LEVEL::LOW;
                                break;
                            case platform::driver::soc::gpio::VALUE::HIGH:
                                msg.content.level = payload::gpio::LEVEL::HIGH;
                                break;
                            default:
                                msg.result = gpio::RESULT::UNKNOWN;
                                msg.content.level = payload::gpio::LEVEL::UNDEFINED;
                                break;
                            }
                            break;
                        }
                        case payload::gpio::FUNCTION::LEVEL_SET:
                        {
                            platform::driver::soc::gpio::DIRECTION direction = board.soc.get_gpio_direction(identifier);

                            if (direction == platform::driver::soc::gpio::DIRECTION::OUTPUT)
                            {
                                msg.result = gpio::RESULT::SUCCESS;
                                switch (msg.content.level)
                                {
                                case payload::gpio::LEVEL::LOW:
                                    board.soc.set_value(identifier, false);
                                    msg.result = gpio::RESULT::SUCCESS;
                                    break;
                                case payload::gpio::LEVEL::HIGH:
                                    board.soc.set_value(identifier, true);
                                    msg.result = gpio::RESULT::SUCCESS;
                                    break;
                                default:
                                    msg.result = gpio::RESULT::UNKNOWN;
                                    break;
                                }
                            }
                            else
                            {
                                msg.result = gpio::RESULT::WRONG_DIRECTION;
                            }
                            break;
                        }
                        default:
                            msg.result = gpio::RESULT::UNSUPPORTED;
                            break;
                        }
                    }
                    confirmation(&msg);
                }

                /**
                 * \brief GPIO indication message
                 *
                 * \param _identifier
                 * \param _level
                 */
                extern void gpio_indication(const IDENTIFIER _identifier, const LEVEL _level)
                {
                    gpio::message_t msg;

                    msg.content.identifier = _identifier;
                    msg.content.level = _level;
                    gpio::indication(&msg);
                }

                /**
                    \brief HCI event trigger request

                    Sends a confirmation message
                */
                extern void keypad_request(chunk_t const *_chunk)
                {
                    keypad::message_t msg;
                    keypad::request(_chunk, &msg);
                    keypad::confirmation(&msg);
                }

                /**
                 * \brief Send hci key event
                 *
                 * \param _event key event data
                 */
                extern void key_indication(const payload::keycode::content_t &_event)
                {
                    keypad::message_t msg;
                    msg.result = engine::hci::cmd::keypad::RESULT::SUCCESS;
                    
                    msg.keycode.control = _event.control;
                    msg.keycode.key_id = _event.key_id;
                    msg.keycode.state = _event.state;
                    msg.keycode.table = _event.table;

                    keypad::indication(&msg);
                }
            }
        }
    }
}