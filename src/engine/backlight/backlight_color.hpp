/**
 * \file backlight_color.hpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#ifndef __BACKLIGHT_COLOR_HPP__
#define __BACKLIGHT_COLOR_HPP__

#include <stdint.h>

namespace engine
{
    namespace backlight
    {
        typedef union
        {
            uint8_t value[3];
            struct
            {
                uint8_t r;
                uint8_t g;
                uint8_t b;
            } rgb;
        } color_t;

        static const color_t BLACK_COLOR{.rgb = {.r = 0, .g = 0, .b = 0}};
        static const color_t ALERT_COLOR{.rgb = {.r = 0x3f, .g = 0, .b = 0}};
        static const color_t SUSPEND_COLOR{.rgb = {.r = 0x1f, .g = 0x1f, .b = 0}};
    }

    static bool operator==(const backlight::color_t &left, const backlight::color_t &right)
    {
        if ((left.value[0] == right.value[0]) &&
            (left.value[1] == right.value[1]) &&
            (left.value[2] == right.value[2]))
        {
            return true;
        }

        return false;
    }
}

#endif // __BACKLIGHT_COLOR_HPP__
