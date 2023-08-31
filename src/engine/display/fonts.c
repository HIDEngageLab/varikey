/**
 * \file fonts.c
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * @copyright Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 *
 */

#include "fonts.h"
#include "font_big.h"
#include "font_huge.h"
#include "font_normal.h"
#include "font_small.h"
#include "font_symbol.h"

const unsigned char **font[5] = {
    FONT_TABLE_SMALL,
    FONT_TABLE_NORMAL,
    FONT_TABLE_BIG,
    FONT_TABLE_HUGE,
    FONT_TABLE_SYMBOL,
};

uint8_t const *const font_character(const FONT_SIZE font_size, uint8_t const ascii)
{
    if (font_size == FONT_BIG)
    {
        return font[font_size][ascii];
    }
    else if (font_size == FONT_HUGE)
    {
        return font[font_size][ascii];
    }
    else if (font_size == FONT_NORMAL)
    {
        return font[font_size][ascii];
    }
    else if (font_size == FONT_SYMBOL)
    {
        return font[font_size][ascii];
    }
    return font[FONT_SMALL][ascii];
}
