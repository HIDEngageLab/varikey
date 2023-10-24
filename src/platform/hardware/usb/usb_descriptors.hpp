/**
 * \file usb_descriptors.hpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#ifndef __USB_DESCRIPTORS_HPP__
#define __USB_DESCRIPTORS_HPP__

#include <stdint.h>

namespace platform
{
    namespace usb
    {
        enum class REPORT_ID : uint8_t
        {
            KEYBOARD = 1,
            MOUSE = 2,
            CONSUMER_CONTROL = 3,
            GAMEPAD = 4,
            COUNT = 5,
            CUSTOM = 6,
            SERIAL = 7,
            GADGET = 8,
            UNIQUE = 9,
            HARDWARE = 10,
            VERSION = 11,
            TEMPERATURE = 12,
        };

        enum class KEYPAD_COMMAND : uint8_t
        {
            RESET = 1,
            POSITION,
            ICON,
            FONT_SIZE,
            TEXT,
            BACKLIGHT,
            CONFIG,
        };
    }
}

#endif /* __USB_DESCRIPTORS_HPP__ */
