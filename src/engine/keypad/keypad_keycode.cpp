/**
 * \file keypad_keycode.cpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#include <cassert>

#include "keypad_keycode.hpp"
#include "keypad_keycode_type.hpp"

namespace engine
{
    namespace keypad
    {
        const uint8_t KeypadCode::key_code(const KEY_ID _identifier, const TABLE _table)
        {
            auto get_value = [this](code_table_t &_table, const uint8_t _index) -> int
            {
                u_int8_t value{_index};

                if (_index < _table.size())
                {
                    key_code_t &key_code = _table[_index];

                    if (_index == (uint8_t)KEY_ID::KEY_70 ||
                        _index == (uint8_t)KEY_ID::KEY_73)
                    {
                        if (key_code.mode == engine::keypad::key_code_t::MODE::ROTATION)
                        {
                            key_code.cursor = (key_code.cursor < key_code.value.size() - 1) ? key_code.cursor + 1 : 0;
                        }

                        key_code_t &dn_key = _table[_index + 1];
                        if (dn_key.mode == engine::keypad::key_code_t::MODE::ROTATION)
                        {
                            dn_key.cursor = (dn_key.cursor < dn_key.value.size() - 1) ? dn_key.cursor + 1 : 0;
                        }
                    }
                    else if (_index == (uint8_t)KEY_ID::KEY_71 ||
                             _index == (uint8_t)KEY_ID::KEY_74)
                    {
                        if (key_code.mode == engine::keypad::key_code_t::MODE::ROTATION)
                        {
                            key_code.cursor = (key_code.cursor > 0) ? key_code.cursor - 1 : key_code.value.size() - 1;
                        }

                        key_code_t &up_key = _table[_index - 1];
                        if (up_key.mode == engine::keypad::key_code_t::MODE::ROTATION)
                        {
                            up_key.cursor = (up_key.cursor > 0) ? up_key.cursor - 1 : up_key.value.size() - 1;
                        }
                    }
                    else
                    {
                        if (key_code.mode == engine::keypad::key_code_t::MODE::ROTATION)
                        {
                            key_code.cursor = (key_code.cursor < key_code.value.size()) ? key_code.cursor + 1 : 0;
                        }
                        else
                        {
                            key_code.cursor = 0;
                        }
                    }
                    value = key_code.value[key_code.cursor];
                }

                return value;
            };

            uint8_t value = 0xff;
            const uint8_t key_index = static_cast<const uint8_t>(_identifier);
            const TABLE table_index = (_table == TABLE::UNDEFINED) ? table : _table;
            switch (table_index)
            {
            case engine::keypad::TABLE::NUMBER:
                value = get_value(Keycode::number_value, key_index);
                break;
            case engine::keypad::TABLE::FUNCTIONAL:
                value = get_value(Keycode::functional_value, key_index);
                break;
            case engine::keypad::TABLE::NAVIGATION:
                value = get_value(Keycode::navigation_value, key_index);
                break;
            case engine::keypad::TABLE::TELEFON:
                value = get_value(Keycode::telephon_value, key_index);
                break;
            case engine::keypad::TABLE::MULTIMEDIA:
                value = get_value(Keycode::multimedia_value, key_index);
                break;
            case engine::keypad::TABLE::CUSTOM:
                value = get_value(Keycode::custom_value, key_index);
                break;
            default:
                break;
            }
            return value;
        }
    }
}
