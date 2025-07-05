// SPDX-FileCopyrightText: 2024 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: keypad keycode module
// SPDX-FileType: SOURCE

#pragma once

#include <cstdint>
#include <cstdlib>
#include <vector>

#include "keypad_modifiers.hpp"

namespace engine::keypad
{
    enum class KEY_ID : uint8_t
    {
        KEY_01 = 0x00,
        KEY_02 = 0x01,
        KEY_03 = 0x02,
        KEY_04 = 0x03,
        KEY_05 = 0x04,
        KEY_06 = 0x05,
        KEY_07 = 0x06,
        KEY_08 = 0x07,
        KEY_09 = 0x08,
        KEY_10 = 0x09,
        KEY_11 = 0x0a,
        KEY_12 = 0x0b,
        KEY_13 = 0x0c,
        KEY_14 = 0x0d,
        KEY_15 = 0x0e,

        KEY_70 = 0x7a,
        KEY_71 = 0x7b,
        KEY_72 = 0x7c,
        KEY_73 = 0x7d,
        KEY_74 = 0x7e,
        KEY_75 = 0x7f,

        KEY_80 = 0x80,
        KEY_81 = 0x81,
        KEY_82 = 0x82,
        KEY_83 = 0x83,
        KEY_84 = 0x84,
        KEY_85 = 0x85,
        KEY_86 = 0x86,
        KEY_87 = 0x87,

        UNDEFINED = 0xff,
    };

    enum class STATE : uint8_t
    {
        CLICK = 0x00,
        PRESS = 0x01,
        PUSH = 0x02,
        RELEASE = 0x03,

        UNDEFINED = 0xff,
    };

    enum class TABLE : uint8_t
    {
        FUNCTIONAL = 0x01,
        MULTIMEDIA = 0x04,
        NAVIGATION = 0x02,
        NUMBER = 0x00,
        TELEFON = 0x03,

        CUSTOM = 0x05,

        UNDEFINED = 0xff,
    };

    struct key_code_t
    {
        enum MODE
        {
            ROTATION,
            SEQUENCE,
            SINGLE,
        } mode;
        size_t cursor;
        MODIFIER modifier;
        std::vector<int> value;
    };

    typedef std::vector<key_code_t> code_table_t;

    struct KeypadCode
    {
        static const TABLE DEFAULT_MAPPING_TABLE = TABLE::NUMBER;

        static code_table_t custom_value;

        void set_table(const TABLE _table);
        const TABLE get_table() const { return table; }

        const uint8_t get_code(const KEY_ID) const;

        void perform(const KEY_ID);
        void reset(void);

    private:
        TABLE table{DEFAULT_MAPPING_TABLE};

        keypad::code_table_t &get_table_content(void) const;
    };

    template <typename T, typename U>
    U transfer_state(const T _state)
    {
        switch (_state)
        {
        case T::CLICK:
            return U::CLICK;
        case T::PUSH:
            return U::PUSH;
        case T::PRESS:
            return U::PRESS;
        case T::RELEASE:
            return U::RELEASE;
        default:
            return U::UNDEFINED;
        }
        return U::UNDEFINED;
    };
}
