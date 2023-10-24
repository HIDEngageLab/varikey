/**
 * \file keyboard_keycode_demo.hpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#ifndef __ENGINE_KEYPAD_KEYCODE_DEMO_HPP__
#define __ENGINE_KEYPAD_KEYCODE_DEMO_HPP__

#include "tusb.h"

namespace engine
{
    namespace keypad
    {
        struct KeypadDemo
        {
            enum class KEYCODE : uint8_t
            {
                LEFT_1 = HID_KEY_0,
                LEFT_2 = HID_KEY_1,
                LEFT_3 = HID_KEY_2,
                LEFT_4 = HID_KEY_3,
                LEFT_5 = HID_KEY_4,
                RIGHT_1 = HID_KEY_5,
                RIGHT_2 = HID_KEY_6,
                RIGHT_3 = HID_KEY_7,
                RIGHT_4 = HID_KEY_8,
                RIGHT_5 = HID_KEY_9,
                LEFT = HID_KEY_A,
                RIGHT = HID_KEY_B,
                ENTER = HID_KEY_C,
            };
        };
    }
}

#define EMBEDDED_KEYBOARD

#endif // __ENGINE_KEYPAD_KEYCODE_DEMO_HPP__
