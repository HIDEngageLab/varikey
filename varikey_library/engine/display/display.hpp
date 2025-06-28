/**
 * \file display.hpp
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#ifndef __PLATFORM_DISPLAY_HPP__
#define __PLATFORM_DISPLAY_HPP__

#include <stdint.h>

#include "display_font.hpp"
#include "display_image.hpp"

namespace engine
{
    namespace display
    {
        extern void set_font(const engine::display::FONT);
        extern void set_cursor(const uint8_t line, const uint8_t column);
        extern void print(char const *const text);
        extern void draw(const engine::display::ICON);
        extern void clean();
    }
}

#endif // __PLATFORM_DISPLAY_HPP__
