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

#include "font_identifier.hpp"
#include "image_type.hpp"
#include "image_identifier.hpp"

extern void display_set_cursor(const uint8_t line, const uint8_t column);
extern void display_set_font(const FONT_SIZE);
extern void display_print(char const *const text);
extern void display_draw(const KEYPAD_ICON);
extern void display_clean();

#endif // __PLATFORM_DISPLAY_HPP__
