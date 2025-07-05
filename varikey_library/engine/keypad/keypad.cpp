// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: keypad module
// SPDX-FileType: SOURCE

#include "keypad.hpp"
#include "backlight3.hpp"
#include "display.hpp"
#include "engine_event_handler.hpp"
#include "hid_handler.hpp"
#include "hid_report.hpp"
#include "keypad_keycode_type.hpp"
#include "macros.hpp"
#include "param_serial_number.hpp"
#include "payload_keypad.hpp"
#include "revision.h"
#include "usb_descriptors.hpp"

namespace engine::keypad
{
    static engine::Keycode keypad_code_table;

    extern void switch_key(const KEY_ID _identifier, const STATE _state)
    {
        switch (_identifier)
        {
        case KEY_ID::KEY_01:
            engine::handler::push_key_event(_identifier, _state);
            break;
        case KEY_ID::KEY_02:
            engine::handler::push_key_event(_identifier, _state);
            break;
        case KEY_ID::KEY_03:
            engine::handler::push_key_event(_identifier, _state);
            break;
        case KEY_ID::KEY_04:
            engine::handler::push_key_event(_identifier, _state);
            break;
        case KEY_ID::KEY_05:
            engine::handler::push_key_event(_identifier, _state);
            break;
        case KEY_ID::KEY_06:
            engine::handler::push_key_event(_identifier, _state);
            break;
        case KEY_ID::KEY_07:
            engine::handler::push_key_event(_identifier, _state);
            break;
        case KEY_ID::KEY_08:
            engine::handler::push_key_event(_identifier, _state);
            break;
        case KEY_ID::KEY_09:
            engine::handler::push_key_event(_identifier, _state);
            break;
        case KEY_ID::KEY_10:
            engine::handler::push_key_event(_identifier, _state);
            break;

        case KEY_ID::KEY_70:
            engine::handler::push_key_event(_identifier, _state);
            break;
        case KEY_ID::KEY_71:
            engine::handler::push_key_event(_identifier, _state);
            break;
        case KEY_ID::KEY_72:
            engine::handler::push_key_event(_identifier, _state);
            break;
        case KEY_ID::KEY_73:
            engine::handler::push_key_event(_identifier, _state);
            break;
        case KEY_ID::KEY_74:
            engine::handler::push_key_event(_identifier, _state);
            break;
        case KEY_ID::KEY_75:
            engine::handler::push_key_event(_identifier, _state);
            break;

        case KEY_ID::KEY_80:
            engine::handler::push_key_event(_identifier, _state);
            break;
        case KEY_ID::KEY_81:
            engine::handler::push_key_event(_identifier, _state);
            break;
        case KEY_ID::KEY_82:
            engine::handler::push_key_event(_identifier, _state);
            break;
        case KEY_ID::KEY_83:
            engine::handler::push_key_event(_identifier, _state);
            break;
        case KEY_ID::KEY_84:
            engine::handler::push_key_event(_identifier, _state);
            break;
        case KEY_ID::KEY_85:
            engine::handler::push_key_event(_identifier, _state);
            break;
        case KEY_ID::KEY_86:
            engine::handler::push_key_event(_identifier, _state);
            break;
        case KEY_ID::KEY_87:
            engine::handler::push_key_event(_identifier, _state);
            break;

        default:
            break;
        }

        if (_state == STATE::RELEASE)
        {
            engine::keypad::perform(_identifier);
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

    extern void enable_nums(const bool _enable)
    {
        static TABLE last_mode = keypad_code_table.get_table();
        if (_enable)
        {
            last_mode = keypad_code_table.get_table();
            keypad_code_table.set_table(TABLE::NUMBER);
        }
        else
        {
            keypad_code_table.set_table(last_mode);
        }
    }

    extern void enable_cups(const bool _enable)
    {
        enable_shift(_enable);
    }

    extern void enable_scroll(const bool _enable)
    {
    }

    extern void perform(const KEY_ID _identifier)
    {
        keypad_code_table.perform(_identifier);
    }

    extern void reset(void)
    {
        keypad_code_table.reset();
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
