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
        enum class COMMAND : uint8_t
        {
            KEYBOARD = 1,
            MOUSE = 2,
            CONSUMER = 3,
            CUSTOM = 0xE0,
        };

        extern void sent_keycode(const uint8_t _modifier, const uint8_t _code);
        extern void sent_keycode();
    }
}

#endif /* __USB_DESCRIPTORS_HPP__ */
