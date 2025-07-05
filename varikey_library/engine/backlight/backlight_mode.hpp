// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: Backlight mode definitions
// SPDX-FileType: SOURCE

#pragma once

#include <stdint.h>

namespace engine::backlight
{
    enum class PROGRAM : uint8_t
    {
        ALERT = 0x00,
        CONST = 0x01,
        MEDIUM = 0x02,
        MORPH = 0x03,
        MOUNT = 0x04,
        OFF = 0x05,
        SET = 0x06,
        SLOW = 0x07,
        SUSPEND = 0x08,
        TURBO = 0x09,
        UNDEFINED = 0xff,
    };
}
