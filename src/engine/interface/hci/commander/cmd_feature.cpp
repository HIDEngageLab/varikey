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
#include "board_defines.hpp"
#include "checksum.hpp"
#include "cmd_backlight_msg.hpp"
#include "cmd_display_msg.hpp"
#include "cmd_gpio_msg.hpp"
#include "cmd_keypad_msg.hpp"
#include "commander.hpp"
#include "engine.hpp"
#include "engine_gpio.hpp"
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
                    \brief Handle gpio request
                */
                extern void gpio_request(chunk_t const *const _chunk)
                {
                    gpio::message_t msg;
                    gpio::request(_chunk, &msg);

                    msg.result = gpio::RESULT::FAILURE;

                    platform::board::IDENTIFIER identifier;
                    switch (msg.content.identifier)
                    {
                    case payload::gpio::IDENTIFIER::GPIO0:
                        identifier = platform::board::IDENTIFIER::GPIO0;
                        break;
                    case payload::gpio::IDENTIFIER::GPIO1:
                        identifier = platform::board::IDENTIFIER::GPIO1;
                        break;
                    case payload::gpio::IDENTIFIER::GPIO2:
                        identifier = platform::board::IDENTIFIER::GPIO2;
                        break;
                    case payload::gpio::IDENTIFIER::GPIO3:
                        identifier = platform::board::IDENTIFIER::GPIO3;
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
                            platform::board::DIRECTION direction = engine::gpio::get_direction(identifier);
                            msg.result = gpio::RESULT::SUCCESS;
                            switch (direction)
                            {
                            case platform::board::DIRECTION::INPUT:
                                msg.content.direction = payload::gpio::DIRECTION::INPUT;
                                break;
                            case platform::board::DIRECTION::OUTPUT:
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
                                engine::gpio::set_direction(identifier, platform::board::DIRECTION::INPUT);
                                break;
                            case payload::gpio::DIRECTION::OUTPUT:
                                engine::gpio::set_direction(identifier, platform::board::DIRECTION::OUTPUT);
                                break;
                            default:
                                msg.result = gpio::RESULT::WRONG_DIRECTION;
                                break;
                            }
                            break;
                        case payload::gpio::FUNCTION::ENABLE:
                            msg.result = gpio::RESULT::SUCCESS;
                            engine::gpio::enable_event(true);
                            break;
                        case payload::gpio::FUNCTION::DISABLE:
                            msg.result = gpio::RESULT::SUCCESS;
                            engine::gpio::enable_event(false);
                            break;
                        case payload::gpio::FUNCTION::LEVEL_GET:
                        {
                            platform::board::VALUE value = engine::gpio::get_value(identifier);
                            msg.result = gpio::RESULT::SUCCESS;
                            switch (value)
                            {
                            case platform::board::VALUE::LOW:
                                msg.content.level = payload::gpio::LEVEL::LOW;
                                break;
                            case platform::board::VALUE::HIGH:
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
                            platform::board::DIRECTION direction = engine::gpio::get_direction(identifier);

                            if (direction == platform::board::DIRECTION::OUTPUT)
                            {
                                msg.result = gpio::RESULT::SUCCESS;
                                switch (msg.content.level)
                                {
                                case payload::gpio::LEVEL::LOW:
                                    engine::gpio::set_value(identifier, false);
                                    msg.result = gpio::RESULT::SUCCESS;
                                    break;
                                case payload::gpio::LEVEL::HIGH:
                                    engine::gpio::set_value(identifier, true);
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