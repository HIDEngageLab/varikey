/**
 * \file backlight.h
 * \author Koch, Roman (koch.roman@googlemail.com)
 * \brief
 *
 * @copyright Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 *
 */

#ifndef __BACKLIGHT_H__
#define __BACKLIGHT_H__

#include <stdint.h>

typedef enum
{
    BACKLIGHT_PROGRAM_MEDIUM = 0,
    BACKLIGHT_PROGRAM_SLOW,
    BACKLIGHT_PROGRAM_TURBO,
    BACKLIGHT_CONST,
    BACKLIGHT_NOT_MOUNTED,
    BACKLIGHT_MOUNTED,
    BACKLIGHT_SUSPENDED,
    BACKLIGHT_OFF,
} backlight_mode_t;

extern void backlight_init(void);
extern void backlight_perform(void);

extern void backlight_mode(const backlight_mode_t, const uint64_t _delay_ms);

extern void backlight_set_left(const uint8_t r, const uint8_t g, const uint8_t b);
extern void backlight_set_right(const uint8_t r, const uint8_t g, const uint8_t b);

extern void backlight_morph_left(const uint8_t r, const uint8_t g, const uint8_t b);
extern void backlight_morph_right(const uint8_t r, const uint8_t g, const uint8_t b);

#endif // __BACKLIGHT_H__
