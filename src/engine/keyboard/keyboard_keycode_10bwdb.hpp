/**
 * \file keyboard_keycode_10bwdb.hpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#ifndef __ENGINE_KEYPAD_KEYCODE_10BWDB_HPP__
#define __ENGINE_KEYPAD_KEYCODE_10BWDB_HPP__

#include "tusb.h"

namespace engine
{
    namespace keypad
    {
        struct Keypad10BWDB
        {
            enum class KEYCODE : uint8_t
            {
                LEFT_1 = HID_KEY_ESCAPE,
                LEFT_2 = HID_KEY_F2,
                LEFT_3 = HID_KEY_F1,
                LEFT_4 = HID_KEY_F3,
                LEFT_5 = HID_KEY_F4,
                RIGHT_1 = HID_KEY_F5,
                RIGHT_2 = HID_KEY_F6,
                RIGHT_3 = HID_KEY_F7,
                RIGHT_4 = HID_KEY_F8,
                RIGHT_5 = HID_KEY_F9,
                LEFT = HID_KEY_PAGE_DOWN,
                RIGHT = HID_KEY_PAGE_UP,
                ENTER = HID_KEY_ENTER,
            };
        };
    }
}

#endif // __ENGINE_KEYPAD_KEYCODE_10BWDB_HPP__
