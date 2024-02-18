/**
 * \file keypad.cpp
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#include "keypad.hpp"
#include "backlight3.hpp"
#include "board.hpp"
#include "display.hpp"
#include "engine_event_handler.hpp"
#include "hid_handler.hpp"
#include "hid_report.hpp"
#include "keypad_keycode_type.hpp"
#include "macros.hpp"
#include "param_serial_number.hpp"
#include "payload_keycode.hpp"
#include "revision.h"
#include "usb_descriptors.hpp"

namespace engine
{
    namespace keypad
    {
        static engine::Keycode keypad_code_table;

        using CONTROL = payload::keycode::CONTROL;

        enum TRIGGER
        {
            UP,
            DN,
            UNDEFINED,
        };

        struct keycode_item_t
        {
            payload::keycode::content_t content;
            TRIGGER trigger;
        };

        keycode_item_t stack[2][4];

        static void push_wheel_turn(const CONTROL _control, const TRIGGER _trigger,
                                    const KEY_ID _key_id, const STATE _state)
        {
            int wheel_index = 0;
            if (_control == CONTROL::WHEEL_1)
            {
                wheel_index = 0;
            }
            else if (_control == CONTROL::WHEEL_2)
            {
                wheel_index = 1;
            }
            else
            {
                /* todo: wheel? */
            }

            if (_trigger != stack[wheel_index][3].trigger)
            {
                for (uint8_t stack_index = 0; stack_index < 3; ++stack_index)
                {
                    stack[wheel_index][stack_index].content.state = stack[wheel_index][stack_index + 1].content.state;
                    stack[wheel_index][stack_index].content.key_id = stack[wheel_index][stack_index + 1].content.key_id;
                    stack[wheel_index][stack_index].trigger = stack[wheel_index][stack_index + 1].trigger;
                }
            }

            stack[wheel_index][3].content.state = transfer_state<engine::keypad::STATE, engine::payload::keycode::STATE>(_state);
            stack[wheel_index][3].content.key_id = _key_id;
            stack[wheel_index][3].trigger = _trigger;

            auto cleanup_stack = [&]()
            {
                stack[wheel_index][0].content.key_id = engine::keypad::KEY_ID::UNDEFINED;
                stack[wheel_index][1].content.key_id = engine::keypad::KEY_ID::UNDEFINED;
                stack[wheel_index][2].content.key_id = engine::keypad::KEY_ID::UNDEFINED;
                stack[wheel_index][3].content.key_id = engine::keypad::KEY_ID::UNDEFINED;
                stack[wheel_index][0].content.state = payload::keycode::STATE::UNDEFINED;
                stack[wheel_index][1].content.state = payload::keycode::STATE::UNDEFINED;
                stack[wheel_index][2].content.state = payload::keycode::STATE::UNDEFINED;
                stack[wheel_index][3].content.state = payload::keycode::STATE::UNDEFINED;
                stack[wheel_index][0].trigger = TRIGGER::UNDEFINED;
                stack[wheel_index][1].trigger = TRIGGER::UNDEFINED;
                stack[wheel_index][2].trigger = TRIGGER::UNDEFINED;
                stack[wheel_index][3].trigger = TRIGGER::UNDEFINED;
            };

            auto check_state = [&]()
            {
                return (stack[wheel_index][0].content.state == payload::keycode::STATE::PRESS &&
                        stack[wheel_index][1].content.state == payload::keycode::STATE::PRESS &&
                        stack[wheel_index][2].content.state == payload::keycode::STATE::RELEASE &&
                        stack[wheel_index][3].content.state == payload::keycode::STATE::RELEASE)
                           ? true
                           : false;
            };

            auto push_wheel_event = [](auto _control,
                                       auto _identifier,
                                       auto _state)
            {
                const payload::keycode::content_t keycode = {
                    .control = _control,
                    .key_id = _identifier,
                    .state = transfer_state<engine::keypad::STATE, engine::payload::keycode::STATE>(_state),
                    .table = engine::keypad::get_mapping(),
                };
                const engine::handler::event_t event = {
                    .identifier = payload::IDENTIFIER::KEYCODE,
                    .keycode = keycode,
                };
                handler::event_queue.push(event);
            };

            if (stack[wheel_index][0].trigger == TRIGGER::UP &&
                stack[wheel_index][1].trigger == TRIGGER::DN &&
                stack[wheel_index][2].trigger == TRIGGER::UP &&
                stack[wheel_index][3].trigger == TRIGGER::DN &&
                check_state())
            {
                cleanup_stack();
                push_wheel_event(_control,
                                 _key_id,
                                 engine::keypad::STATE::PRESS);
                push_wheel_event(_control,
                                 _key_id,
                                 engine::keypad::STATE::RELEASE);
            }
            else if (stack[wheel_index][0].trigger == TRIGGER::DN &&
                     stack[wheel_index][1].trigger == TRIGGER::UP &&
                     stack[wheel_index][2].trigger == TRIGGER::DN &&
                     stack[wheel_index][3].trigger == TRIGGER::UP &&
                     check_state())
            {
                cleanup_stack();
                push_wheel_event(_control,
                                 _key_id,
                                 engine::keypad::STATE::PRESS);
                push_wheel_event(_control,
                                 _key_id,
                                 engine::keypad::STATE::RELEASE);
            }
        }

        extern void switch_key(const KEY_ID _identifier, const STATE _state)
        {
            auto push_key_event = [](const engine::keypad::KEY_ID _identifier,
                                     const engine::keypad::STATE _state)
            {
                payload::keycode::content_t key_event = {
                    .control = CONTROL::BUTTON,
                    .key_id = _identifier,
                    .state = transfer_state<engine::keypad::STATE, engine::payload::keycode::STATE>(_state),
                    .table = engine::keypad::get_mapping(),
                };
                engine::handler::event_t event = {
                    .identifier = engine::payload::IDENTIFIER::KEYCODE,
                    .keycode = key_event,
                };
                handler::event_queue.push(event);
            };

            auto push_wheel_switch = [](const CONTROL _control,
                                        const engine::keypad::KEY_ID _identifier,
                                        const engine::keypad::STATE _state)
            {
                const payload::keycode::content_t key_event = {
                    .control = _control,
                    .key_id = _identifier,
                    .state = transfer_state<engine::keypad::STATE, engine::payload::keycode::STATE>(_state),
                    .table = engine::keypad::get_mapping(),
                };
                const engine::handler::event_t event = {
                    .identifier = payload::IDENTIFIER::KEYCODE,
                    .keycode = key_event,
                };
                handler::event_queue.push(event);
            };

            auto push_joystick_event = [](const CONTROL _control,
                                          const engine::keypad::KEY_ID _identifier,
                                          const engine::keypad::STATE _state)
            {
                payload::keycode::content_t key_event = {
                    .control = _control,
                    .key_id = _identifier,
                    .state = transfer_state<engine::keypad::STATE, engine::payload::keycode::STATE>(_state),
                    .table = engine::keypad::get_mapping(),
                };
                engine::handler::event_t event = {
                    .identifier = payload::IDENTIFIER::KEYCODE,
                    .keycode = key_event,
                };
                handler::event_queue.push(event);
            };

            switch (_identifier)
            {
            case KEY_ID::KEY_01:
                push_key_event(_identifier, _state);
                break;
            case KEY_ID::KEY_02:
                push_key_event(_identifier, _state);
                break;
            case KEY_ID::KEY_03:
                push_key_event(_identifier, _state);
                break;
            case KEY_ID::KEY_04:
                push_key_event(_identifier, _state);
                break;
            case KEY_ID::KEY_05:
                push_key_event(_identifier, _state);
                break;
            case KEY_ID::KEY_06:
                push_key_event(_identifier, _state);
                break;
            case KEY_ID::KEY_07:
                push_key_event(_identifier, _state);
                break;
            case KEY_ID::KEY_08:
                push_key_event(_identifier, _state);
                break;
            case KEY_ID::KEY_09:
                push_key_event(_identifier, _state);
                break;
            case KEY_ID::KEY_10:
                push_key_event(_identifier, _state);
                break;

            case KEY_ID::KEY_70:
                push_wheel_turn(CONTROL::WHEEL_1,
                                TRIGGER::UP,
                                _identifier, _state);
                break;
            case KEY_ID::KEY_71:
                push_wheel_turn(CONTROL::WHEEL_1,
                                TRIGGER::DN,
                                _identifier, _state);
                break;
            case KEY_ID::KEY_72:
                push_wheel_switch(CONTROL::WHEEL_1,
                                  _identifier, _state);
                break;
            case KEY_ID::KEY_73:
                push_wheel_turn(CONTROL::WHEEL_2,
                                TRIGGER::UP,
                                _identifier, _state);
                break;
            case KEY_ID::KEY_74:
                push_wheel_turn(CONTROL::WHEEL_2,
                                TRIGGER::DN,
                                _identifier, _state);
                break;
            case KEY_ID::KEY_75:
                push_wheel_switch(CONTROL::WHEEL_2,
                                  _identifier, _state);
                break;

            case KEY_ID::KEY_80:
                push_joystick_event(CONTROL::JOYSTICK_1,
                                    _identifier, _state);
                break;
            case KEY_ID::KEY_81:
                push_joystick_event(CONTROL::JOYSTICK_1,
                                    _identifier, _state);
                break;
            case KEY_ID::KEY_82:
                push_joystick_event(CONTROL::JOYSTICK_1,
                                    _identifier, _state);
                break;
            case KEY_ID::KEY_83:
                push_joystick_event(CONTROL::JOYSTICK_1,
                                    _identifier, _state);
                break;
            case KEY_ID::KEY_84:
                push_joystick_event(CONTROL::JOYSTICK_2,
                                    _identifier, _state);
                break;
            case KEY_ID::KEY_85:
                push_joystick_event(CONTROL::JOYSTICK_2,
                                    _identifier, _state);
                break;
            case KEY_ID::KEY_86:
                push_joystick_event(CONTROL::JOYSTICK_2,
                                    _identifier, _state);
                break;
            case KEY_ID::KEY_87:
                push_joystick_event(CONTROL::JOYSTICK_2,
                                    _identifier, _state);
                break;

            default:
                break;
            }
        }

        extern void press_key(const KEY_ID _identifier)
        {
            switch_key(_identifier, STATE::PRESS);
        }

        extern void release_ley(const KEY_ID _identifier)
        {
            switch_key(_identifier, STATE::RELEASE);
        }

        extern void set_mapping(const TABLE _table)
        {
            if (_table == TABLE::CUSTOM ||
                _table == TABLE::FUNCTIONAL ||
                _table == TABLE::MULTIMEDIA ||
                _table == TABLE::NAVIGATION ||
                _table == TABLE::NUMBER ||
                _table == TABLE::TELEFON)
            {
                keypad_code_table.set_table(_table);
            }
            else
            {
                keypad_code_table.set_table(KeypadCode::DEFAULT_MAPPING_TABLE);
            }
        }

        extern const TABLE get_mapping(void)
        {
            return keypad_code_table.get_table();
        }

        extern void perform_hid_key(const KEY_ID _identifier, const TABLE _table)
        {
            keypad_code_table.set_table(_table);
            keypad_code_table.perform(_identifier);
        }

        extern void clean(void)
        {
            keypad_code_table.clean();
        }

        extern const uint8_t id2int(const KEY_ID _identifier)
        {
            return keypad_code_table.get_code(_identifier);
        }

        extern const KEY_ID int2id(const uint8_t _value)
        {
            if (_value >= 0x00 && _value <= 0x17)
            {
                return static_cast<const engine::keypad::KEY_ID>(_value);
            }
            return engine::keypad::KEY_ID::UNDEFINED;
        }
    }
}