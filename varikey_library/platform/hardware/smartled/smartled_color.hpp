// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: Backlight color definitions
// SPDX-FileType: SOURCE

#pragma once

#include <stdint.h>

namespace platform::hardware::smartled
{
    union Color
    {
        uint8_t value[3];
        struct
        {
            uint8_t r;
            uint8_t g;
            uint8_t b;
        } rgb;
    };

    static bool operator==(const Color &left, const Color &right)
    {
        return left.value[0] == right.value[0] &&
               left.value[1] == right.value[1] &&
               left.value[2] == right.value[2];
    }
    static bool operator!=(const Color &left, const Color &right)
    {
        return !(left == right);
    }
}
