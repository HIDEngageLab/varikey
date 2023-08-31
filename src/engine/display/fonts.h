/**
 * \file fonts.h
 * \author Koch, Roman (koch.roman@googlemail.com)
 * \brief
 * \version 0.1
 * @date 2023-03-28
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef __DISPLAY_FONTS_H__
#define __DISPLAY_FONTS_H__

#include <stdint.h>

typedef enum
{
    FONT_SMALL = 0,
    FONT_NORMAL = 1,
    FONT_BIG = 2,
    FONT_HUGE = 3,
    FONT_SYMBOL = 4,
} FONT_SIZE;

uint8_t const *const font_character(const FONT_SIZE font, uint8_t const ascii);

#endif // __DISPLAY_FONTS_H__