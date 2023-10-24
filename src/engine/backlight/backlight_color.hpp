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

typedef union
{
    uint32_t value;
    struct
    {
        uint8_t dummy;
        uint8_t r;
        uint8_t g;
        uint8_t b;
    } rgb;
} color_t;

#endif // __BACKLIGHT_COLOR_HPP__
