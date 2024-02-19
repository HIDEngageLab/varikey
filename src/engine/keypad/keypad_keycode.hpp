/**
 * \file keypad_keycode.hpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#ifndef __ENGINE_KEYPAD_KEYCODE_HPP__
#define __ENGINE_KEYPAD_KEYCODE_HPP__

#include <cstdint>
#include <cstdlib>
#include <vector>

namespace engine
{
    namespace keypad
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

            KEY_70 = 0x0a, /* wheel 1 up */
            KEY_71 = 0x0b, /* wheel 1 down */
            KEY_72 = 0x0c, /* wheel 1 switch */
            KEY_73 = 0x0d, /* wheel 2 up */
            KEY_74 = 0x0e, /* wheel 2 down */
            KEY_75 = 0x0f, /* wheel 2 switch */

            KEY_80 = 0x10, /* joystick 1 down */
            KEY_81 = 0x11, /* joystick 1 left */
            KEY_82 = 0x12, /* joystick 1 right */
            KEY_83 = 0x13, /* joystick 1 up */
            KEY_84 = 0x14, /* joystick 2 down */
            KEY_85 = 0x15, /* joystick 2 left */
            KEY_86 = 0x16, /* joystick 2 right */
            KEY_87 = 0x17, /* joystick 2 up */

            UNDEFINED = 0xff,
        };

        enum class STATE : uint8_t
        {
            PRESS = 0x00,
            RELEASE = 0x01,

            UNDEFINED = 0xff,
        };

        enum class TABLE : uint8_t
        {
            CUSTOM = 0x05,
            FUNCTIONAL = 0x01,
            MULTIMEDIA = 0x04,
            NAVIGATION = 0x02,
            NUMBER = 0x00,
            TELEFON = 0x03,

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
            std::vector<int> value;
        };

        typedef std::vector<key_code_t> code_table_t;

        struct KeypadCode
        {
            static const TABLE DEFAULT_MAPPING_TABLE = TABLE::NUMBER;

            void set_table(const TABLE _table);
            const TABLE get_table() const { return table; }

            const uint8_t get_code(const KEY_ID) const;

            void perform(const KEY_ID);
            void clean(void);

        private:
            TABLE table{DEFAULT_MAPPING_TABLE};

            keypad::code_table_t &get_table_content(void) const;
        };

        template <typename T, typename U>
        U transfer_state(const T _state)
        {
            switch (_state)
            {
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
}

#endif // __ENGINE_KEYPAD_KEYCODE_HPP__
