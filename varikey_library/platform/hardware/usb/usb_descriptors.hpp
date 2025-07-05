// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: Hardware usb descriptors functionality
// SPDX-FileType: SOURCE

#pragma once

#include <stdint.h>

namespace platform::usb
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
