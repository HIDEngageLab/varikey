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

                    msg.result = gpio::RESULT::SUCCESS;
                    if (msg.content.identifier == platform::board::IDENTIFIER::UNDEFINED)
                    {
                        msg.result = gpio::RESULT::WRONG_IDENTIFIER;
                    }
                    else
                    {
                        switch (msg.content.function)
                        {
                        case payload::gpio::FUNCTION::DIRECTION:
                        {
                            msg.result = gpio::RESULT::SUCCESS;
                            const platform::board::DIRECTION direction = engine::gpio::get_direction(msg.content.identifier);
                            switch (direction)
                            {
                            case platform::board::DIRECTION::INPUT:
                                msg.content.function = payload::gpio::FUNCTION::IN;
                                break;
                            case platform::board::DIRECTION::OUTPUT:
                                msg.content.function = payload::gpio::FUNCTION::OUT;
                                break;
                            default:
                                msg.content.function = payload::gpio::FUNCTION::UNDEFINED;
                                msg.result = gpio::RESULT::WRONG_DIRECTION;
                                break;
                            }
                        }
                        case payload::gpio::FUNCTION::IN:
                            msg.result = gpio::RESULT::SUCCESS;
                            engine::gpio::set_direction(msg.content.identifier, engine::gpio::DIRECTION::INPUT);
                            break;
                        case payload::gpio::FUNCTION::OUT:
                            msg.result = gpio::RESULT::SUCCESS;
                            engine::gpio::set_direction(msg.content.identifier, engine::gpio::DIRECTION::OUTPUT);
                            break;
                        case payload::gpio::FUNCTION::ENABLE:
                            msg.result = gpio::RESULT::SUCCESS;
                            engine::gpio::enable_event(true);
                            break;
                        case payload::gpio::FUNCTION::DISABLE:
                            msg.result = gpio::RESULT::SUCCESS;
                            engine::gpio::enable_event(false);
                            break;
                        case payload::gpio::FUNCTION::VALUE:
                        {
                            msg.result = gpio::RESULT::SUCCESS;
                            const platform::board::VALUE value = engine::gpio::get_value(msg.content.identifier);
                            switch (value)
                            {
                            case platform::board::VALUE::LOW:
                                msg.content.function = payload::gpio::FUNCTION::LOW;
                                break;
                            case platform::board::VALUE::HIGH:
                                msg.content.function = payload::gpio::FUNCTION::HIGH;
                                break;
                            default:
                                msg.result = gpio::RESULT::UNKNOWN;
                                msg.content.function = payload::gpio::FUNCTION::UNDEFINED;
                                break;
                            }
                            break;
                        }
                        case payload::gpio::FUNCTION::HIGH:
                        {
                            msg.result = gpio::RESULT::SUCCESS;
                            const platform::board::DIRECTION direction = engine::gpio::get_direction(msg.content.identifier);
                            if (direction == platform::board::DIRECTION::OUTPUT)
                            {
                                engine::gpio::set_value(msg.content.identifier, true);
                            }
                            else
                            {
                                msg.result = gpio::RESULT::WRONG_DIRECTION;
                            }
                            break;
                        }
                        case payload::gpio::FUNCTION::LOW:
                        {
                            msg.result = gpio::RESULT::SUCCESS;
                            const platform::board::DIRECTION direction = engine::gpio::get_direction(msg.content.identifier);
                            if (direction == platform::board::DIRECTION::OUTPUT)
                            {
                                engine::gpio::set_value(msg.content.identifier, false);
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
                extern void gpio_indication(const FUNCTION _function, const IDENTIFIER _identifier, const uint32_t _timestamp)
                {
                    gpio::message_t msg;

                    msg.content.function = _function;
                    msg.content.identifier = _identifier;
                    msg.content.diff = _timestamp;
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
                extern void key_indication(const payload::keypad::content_t &_event)
                {
                    keypad::message_t msg;
                    msg.result = engine::hci::cmd::keypad::RESULT::SUCCESS;

                    msg.keypad.identifier = _event.identifier;
                    msg.keypad.function = _event.function;
                    msg.keypad.key.code = _event.key.code;
                    msg.keypad.key.modifier = _event.key.modifier;
                    msg.keypad.table = _event.table;

                    keypad::indication(&msg);
                }
            }
        }
    }
}