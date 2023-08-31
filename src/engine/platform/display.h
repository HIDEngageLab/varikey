/**
 * \file display.h
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 *
 */

#ifndef __PLATFORM_DISPLAY_H__
#define __PLATFORM_DISPLAY_H__

#include <stdint.h>

#include "fonts.h"
#include "images.h"

extern void display_init(void);
extern void display_perform(void);

extern void display_set_cursor(const uint8_t line, const uint8_t column);
extern void display_set_font(const FONT_SIZE size);
extern void display_print(char const *const text);
extern void display_draw(image_t const *const image);
extern void display_clean();

#endif // __PLATFORM_DISPLAY_H__
