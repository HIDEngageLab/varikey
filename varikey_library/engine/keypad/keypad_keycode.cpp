// SPDX-FileCopyrightText: 2024 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: keypad keycode module
// SPDX-FileType: SOURCE

#include <cassert>

#include "keypad_keycode.hpp"
#include "keypad_keycode_type.hpp"
#include "keypad_modifiers.hpp"
#include "param_mapping.hpp"

namespace engine::keypad
{
    code_table_t KeypadCode::custom_value = {
        {key_code_t::SINGLE, 0, 0, {0xff}},
        {key_code_t::SINGLE, 0, 0, {0xff}},
        {key_code_t::SINGLE, 0, 0, {0xff}},
        {key_code_t::SINGLE, 0, 0, {0xff}},
        {key_code_t::SINGLE, 0, 0, {0xff}},

        {key_code_t::SINGLE, 0, 0, {0xff}},
        {key_code_t::SINGLE, 0, 0, {0xff}},
        {key_code_t::SINGLE, 0, 0, {0xff}},
        {key_code_t::SINGLE, 0, 0, {0xff}},
        {key_code_t::SINGLE, 0, 0, {0xff}},

        {key_code_t::SINGLE, 0, 0, {0xff}},
        {key_code_t::SINGLE, 0, 0, {0xff}},
        {key_code_t::SINGLE, 0, 0, {0xff}},

        {key_code_t::SINGLE, 0, 0, {0xff}},
        {key_code_t::SINGLE, 0, 0, {0xff}},
        {key_code_t::SINGLE, 0, 0, {0xff}},

        {key_code_t::SINGLE, 0, 0, {0xff}},
        {key_code_t::SINGLE, 0, 0, {0xff}},
        {key_code_t::SINGLE, 0, 0, {0xff}},
        {key_code_t::SINGLE, 0, 0, {0xff}},

        {key_code_t::SINGLE, 0, 0, {0xff}},
        {key_code_t::SINGLE, 0, 0, {0xff}},
        {key_code_t::SINGLE, 0, 0, {0xff}},
        {key_code_t::SINGLE, 0, 0, {0xff}},
    };

    void KeypadCode::set_table(const TABLE _table)
    {
        table = _table;
        if (table == TABLE::CUSTOM)
        {
            size_t parameter_index = 0;
            for (auto &i : Keycode::custom_value)
            {
                i.modifier.value = registry::parameter::mapping::g_register.value[parameter_index].modifier;
                i.value[0] = registry::parameter::mapping::g_register.value[parameter_index].code;

                if (parameter_index < registry::parameter::mapping::SIZE)
                    parameter_index++;
                else
                    break;
            }
        }
    }

    keypad::code_table_t &KeypadCode::get_table_content() const
    {
        switch (table)
        {
        case engine::keypad::TABLE::NUMBER:
            return Keycode::number_value;
        case engine::keypad::TABLE::FUNCTIONAL:
            return Keycode::functional_value;
        case engine::keypad::TABLE::NAVIGATION:
            return Keycode::navigation_value;
        case engine::keypad::TABLE::TELEFON:
            return Keycode::telephon_value;
        case engine::keypad::TABLE::MULTIMEDIA:
            return Keycode::multimedia_value;
        case engine::keypad::TABLE::CUSTOM:
            return Keycode::custom_value;
        default:
            break;
        }
        return Keycode::number_value;
    }

    const uint8_t KeypadCode::get_code(const KEY_ID _identifier) const
    {
        const keypad::code_table_t &current_table = static_cast<const keypad::code_table_t>(get_table_content());
        const uint8_t key_index = static_cast<const uint8_t>(_identifier);

        const key_code_t &key_item = current_table[key_index];

        return key_item.value[key_item.cursor];
    }

    void KeypadCode::perform(const KEY_ID _identifier)
    {
        keypad::code_table_t &current_table = get_table_content();
        const uint8_t key_index = static_cast<const uint8_t>(_identifier);

        if (key_index < current_table.size())
        {
            if (key_index == (uint8_t)KEY_ID::KEY_70 ||
                key_index == (uint8_t)KEY_ID::KEY_73)
            {
                key_code_t &up_key = current_table[key_index];
                if (up_key.mode == engine::keypad::key_code_t::MODE::ROTATION)
                {
                    up_key.cursor = (up_key.cursor < up_key.value.size() - 1) ? up_key.cursor + 1 : 0;
                }

                key_code_t &dn_key = current_table[key_index + 1];
                if (dn_key.mode == engine::keypad::key_code_t::MODE::ROTATION)
                {
                    dn_key.cursor = (dn_key.cursor < dn_key.value.size() - 1) ? dn_key.cursor + 1 : 0;
                }
            }
            else if (key_index == (uint8_t)KEY_ID::KEY_71 ||
                     key_index == (uint8_t)KEY_ID::KEY_74)
            {
                key_code_t &up_key = current_table[key_index - 1];
                if (up_key.mode == engine::keypad::key_code_t::MODE::ROTATION)
                {
                    up_key.cursor = (up_key.cursor > 0) ? up_key.cursor - 1 : up_key.value.size() - 1;
                }

                key_code_t &dn_key = current_table[key_index];
                if (dn_key.mode == engine::keypad::key_code_t::MODE::ROTATION)
                {
                    dn_key.cursor = (dn_key.cursor > 0) ? dn_key.cursor - 1 : dn_key.value.size() - 1;
                }
            }
            else
            {
                key_code_t &key_item = current_table[key_index];
                if (key_item.mode == engine::keypad::key_code_t::MODE::ROTATION)
                {
                    key_item.cursor = (key_item.cursor < key_item.value.size() - 1) ? key_item.cursor + 1 : 0;
                }
                else
                {
                    key_item.cursor = 0;
                }
            }
        }
    }

    void KeypadCode::reset(void)
    {
        auto reset_cursor = [this](engine::keypad::code_table_t &_table)
        {
            for (key_code_t &i : _table)
            {
                i.cursor = 0;
            }
        };

        reset_cursor(Keycode::number_value);
        reset_cursor(Keycode::functional_value);
        reset_cursor(Keycode::navigation_value);
        reset_cursor(Keycode::telephon_value);
        reset_cursor(Keycode::multimedia_value);
        reset_cursor(Keycode::custom_value);
    }
}
