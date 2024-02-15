/**
 * \file cmd_keypad_msg.cpp
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */
/**
    \brief Event message

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "cmd_keypad_msg.hpp"
#include "commander.hpp"
#include "engine_event_handler.hpp"
#include "hid_handler.hpp"
#include "keypad.hpp"
#include "macros.hpp"
#include "payload_identifier.hpp"
#include "revision.h"
#include "serial_frame.hpp"

namespace engine
{
    namespace hci
    {
        namespace cmd
        {
            namespace keypad
            {
                static const size_t BUFFER_SIZE = 20;
                static const size_t CFM_SIZE = 4;
                static const size_t IND_SIZE = 1;

                /**
                    \brief Event request message
                */
                extern void request(chunk_t const *const _chunk, message_t *const _msg)
                {
                    using IDENTIFIER = engine::payload::keypad::IDENTIFIER;

                    assert(_chunk != NULL && _msg != NULL); /* clean request chunk null */

                    /* deserialize */
                    _msg->result = RESULT::SUCCESS;
                    _msg->keypad.deserialize(_chunk->space);

                    if (_msg->keypad.identifier == payload::keypad::IDENTIFIER::UNDEFINED)
                    {
                        _msg->result = RESULT::WRONG_IDENTIFIER;
                    }
                    else if (_msg->keypad.function == payload::keypad::FUNCTION::UNDEFINED)
                    {
                        _msg->result = RESULT::WRONG_FUNCTION;
                    }
                    else
                    {
                        switch (_msg->keypad.identifier)
                        {
                        case IDENTIFIER::HCI:
                            if (_msg->keypad.function == payload::keypad::FUNCTION::ENABLE)
                            {
                                engine::handler::set_hci_enabled(true);
                            }
                            else if (_msg->keypad.function == payload::keypad::FUNCTION::DISABLE)
                            {
                                engine::handler::set_hci_enabled(false);
                            }
                            else
                            {
                                _msg->result = RESULT::WRONG_FUNCTION;
                            }
                            break;
                        case IDENTIFIER::HID:

                            if (_msg->keypad.function == payload::keypad::FUNCTION::ENABLE)
                            {
                                engine::handler::set_hid_enabled(true);
                            }
                            else if (_msg->keypad.function == payload::keypad::FUNCTION::DISABLE)
                            {
                                engine::handler::set_hid_enabled(false);
                            }
                            else
                            {
                                _msg->result = RESULT::WRONG_FUNCTION;
                            }
                            break;
                        case IDENTIFIER::MAPPING:
                            if (_msg->keypad.function == payload::keypad::FUNCTION::SET)
                            {
                                engine::keypad::set_mapping(_msg->keypad.table);
                                _msg->keypad.table = engine::keypad::get_mapping();
                            }
                            else if (_msg->keypad.function == payload::keypad::FUNCTION::GET)
                            {
                                _msg->keypad.table = engine::keypad::get_mapping();
                            }
                            else
                            {
                                _msg->result = RESULT::WRONG_FUNCTION;
                            }
                            break;
                        case IDENTIFIER::KEYCODE:
                            engine::keypad::push_key_event(engine::keypad::to_identifier(_msg->keypad.code),
                                                           engine::keypad::STATE::PRESS);
                            engine::keypad::push_key_event(engine::keypad::to_identifier(_msg->keypad.code),
                                                           engine::keypad::STATE::RELEASE);
                            break;
                        default:
                            _msg->result = RESULT::WRONG_IDENTIFIER;
                            break;
                        }
                    }
                    _msg->value.size = 0;
                    _msg->value.space = 0;
                }

                /**
                    \brief Event confirmation message
                */
                extern void confirmation(message_t *const _msg)
                {
                    assert(_msg != NULL); /* event confirmation chunk null */

                    /* handle */
                    uint8_t space[CFM_SIZE + BUFFER_SIZE] = {0};
                    _msg->value.space = space;
                    _msg->value.size = CFM_SIZE;
                    uint8_t *ptr = space;

                    *ptr++ = (uint8_t)engine::hci::COMMAND::KEYPAD_CFM;
                    *ptr++ = (uint8_t)_msg->result;
                    _msg->keypad.serialize(ptr);

                    serial::frame::send(engine::hci::INTERPRETER_ADDRESS, &_msg->value);
                }

                /**
                    \brief Event indication message
                */
                extern void indication(message_t *const _msg)
                {
                    assert(_msg != NULL); /* event indication chunk null */

                    /* handle */
                    uint8_t space[IND_SIZE + BUFFER_SIZE] = {0};
                    _msg->value.space = space;
                    _msg->value.size = IND_SIZE;
                    uint8_t *ptr = space;

                    *ptr++ = (uint8_t)engine::hci::COMMAND::KEYPAD_IND;
                    _msg->keycode.serialize(ptr);
                    _msg->value.size += _msg->keycode.size();

                    serial::frame::send(engine::hci::INTERPRETER_ADDRESS, &_msg->value);
                }
            }
        }
    }
}
