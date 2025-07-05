// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: cmd keypad msg module
// SPDX-FileType: SOURCE

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "cmd_keypad_msg.hpp"
#include "commander.hpp"
#include "engine_event_handler.hpp"
#include "hid_handler.hpp"
#include "keypad.hpp"
#include "keypad_modifiers.hpp"
#include "macros.hpp"
#include "payload_identifier.hpp"
#include "revision.h"
#include "serial_frame.hpp"

namespace engine::hci::cmd::keypad
{
    static const size_t BUFFER_SIZE = 20;
    static const size_t CFM_SIZE = 2;
    static const size_t IND_SIZE = 1;

    extern void request(chunk_t const *const _chunk, message_t *const _msg)
    {
        using IDENTIFIER = engine::payload::keypad::IDENTIFIER;

        assert(_chunk != NULL && _msg != NULL);

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
            case IDENTIFIER::KEYCODE:
            {
                const engine::keypad::KEY_ID key_code_id = _msg->keypad.key.code;
                if (key_code_id != engine::keypad::KEY_ID::UNDEFINED)
                {
                    if (_msg->keypad.function == engine::payload::keypad::FUNCTION::CLICK ||
                        _msg->keypad.function == engine::payload::keypad::FUNCTION::PUSH)
                    {
                        engine::keypad::set_modifier(_msg->keypad.key.modifier);
                        engine::keypad::press_key(key_code_id);
                        engine::keypad::release_ley(key_code_id);
                    }
                    else if (_msg->keypad.function == engine::payload::keypad::FUNCTION::PRESS)
                    {
                        engine::keypad::set_modifier(_msg->keypad.key.modifier);
                        engine::keypad::press_key(key_code_id);
                    }
                    else if (_msg->keypad.function == engine::payload::keypad::FUNCTION::RELEASE)
                    {
                        engine::keypad::release_ley(key_code_id);
                    }
                }
                break;
            }
            case IDENTIFIER::MAPPING:
                if (_msg->keypad.function == payload::keypad::FUNCTION::SET)
                {
                    if (_msg->keypad.table != payload::keypad::TABLE::UNDEFINED)
                    {
                        engine::keypad::set_mapping(_msg->keypad.table);
                    }
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
            default:
                _msg->result = RESULT::WRONG_IDENTIFIER;
                break;
            }
        }
        _msg->value.size = 0;
        _msg->value.space = 0;
    }

    extern void confirmation(message_t *const _msg)
    {
        assert(_msg != NULL);

        uint8_t space[CFM_SIZE + BUFFER_SIZE] = {0};
        _msg->value.space = space;
        _msg->value.size = CFM_SIZE;
        uint8_t *ptr = space;

        *ptr++ = (uint8_t)engine::hci::COMMAND::KEYPAD_CFM;
        *ptr++ = (uint8_t)_msg->result;
        _msg->keypad.serialize(&ptr);
        _msg->value.size += _msg->keypad.size();

        serial::frame::send(engine::hci::INTERPRETER_ADDRESS, &_msg->value);
    }

    extern void indication(message_t *const _msg)
    {
        assert(_msg != NULL);

        uint8_t space[IND_SIZE + BUFFER_SIZE] = {0};
        _msg->value.space = space;
        _msg->value.size = IND_SIZE;
        uint8_t *ptr = space;

        *ptr++ = (uint8_t)engine::hci::COMMAND::KEYPAD_IND;
        _msg->keypad.serialize(&ptr);
        _msg->value.size += _msg->keypad.size();

        serial::frame::send(engine::hci::INTERPRETER_ADDRESS, &_msg->value);
    }
}