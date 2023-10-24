/**
 * \file backlight3.hpp
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#ifndef __BACKLIGHT3_HPP__
#define __BACKLIGHT3_HPP__

#include <stdint.h>

typedef enum
{
    BACKLIGHT_PROGRAM_MEDIUM = 0,
    BACKLIGHT_PROGRAM_SLOW = 1,
    BACKLIGHT_PROGRAM_TURBO = 2,
    BACKLIGHT_CONST = 3,
    BACKLIGHT_NOT_MOUNTED = 4,
    BACKLIGHT_MOUNTED = 5,
    BACKLIGHT_SUSPENDED = 6,
    BACKLIGHT_OFF = 7,
} backlight_mode_t;

extern void backlight_init(void);
extern void backlight_perform(void);

extern void backlight_mode(const backlight_mode_t, const uint64_t _delay_ms);

extern void backlight_set_left(const uint8_t r, const uint8_t g, const uint8_t b);
extern void backlight_set_right(const uint8_t r, const uint8_t g, const uint8_t b);

extern void backlight_morph_left(const uint8_t r, const uint8_t g, const uint8_t b);
extern void backlight_morph_right(const uint8_t r, const uint8_t g, const uint8_t b);

#endif // __BACKLIGHT3_HPP__
