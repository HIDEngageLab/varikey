/**
 * \file fonts.c
 * \author Koch, Roman (koch.roman@googlemail.com)
 * \brief 
 * \version 0.1
 * @date 2023-03-28
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "fonts.h"
#include "font_small.h"
#include "font_normal.h"
#include "font_big.h"
#include "font_huge.h"
#include "font_symbol.h"

const unsigned char **font[3] = {FONT_TABLE_SMALL, FONT_TABLE_NORMAL, FONT_TABLE_BIG, FONT_TABLE_HUGE};

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
    return font[FONT_SMALL][ascii];
}
