/**
 * \file backlight3.hpp
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#ifndef __ENGINE_BACKLIGHT3_HPP__
#define __ENGINE_BACKLIGHT3_HPP__

#include <stdint.h>

#include "backlight_color.hpp"
#include "backlight_mode.hpp"

namespace engine
{
    namespace backlight
    {
        extern void initialize(void);
        extern void perform(void);

        extern void set_mode(const MODE, const uint64_t _delay_ms);

        extern void set_left(const uint8_t r, const uint8_t g, const uint8_t b);
        extern void set_right(const uint8_t r, const uint8_t g, const uint8_t b);

        extern void morph_left(const uint8_t r, const uint8_t g, const uint8_t b);
        extern void morph_right(const uint8_t r, const uint8_t g, const uint8_t b);

        extern inline void set_left(const Color &_color) { set_left(_color.rgb.r, _color.rgb.g, _color.rgb.b); }
        extern inline void set_right(const Color &_color) { set_right(_color.rgb.r, _color.rgb.g, _color.rgb.b); }
        extern inline void morph_left(const Color &_color) { morph_left(_color.rgb.r, _color.rgb.g, _color.rgb.b); }
        extern inline void morph_right(const Color &_color) { morph_right(_color.rgb.r, _color.rgb.g, _color.rgb.b); }
    }
}

#endif // __ENGINE_BACKLIGHT3_HPP__
