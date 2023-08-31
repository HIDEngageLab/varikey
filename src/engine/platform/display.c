/**
 * \file display.c
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * @copyright Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 *
 */

#include <stdio.h>

#include "display.h"
#include "ssd1306.h"

uint8_t line = 0;
uint8_t column = 0;
FONT_SIZE font_size = FONT_SMALL;
uint8_t high_pages = 1;
uint8_t width_cols = 7;
uint8_t symbol_size = 8;

extern void display_init(void)
{
}

extern void display_perform(void)
{
}

extern void display_set_cursor(const uint8_t _line, const uint8_t _column)
{
    line = _line % 4;
    column = _column % 128;
}

extern void display_set_font(const FONT_SIZE size)
{
    switch (size)
    {
    case FONT_SMALL:
        font_size = size;
        high_pages = 1;
        width_cols = 7;
        symbol_size = 8;
        break;

    case FONT_BIG:
        font_size = size;
        high_pages = 2;
        width_cols = 8;
        symbol_size = 16;
        break;

    case FONT_HUGE:
        font_size = size;
        high_pages = 3;
        width_cols = 16;
        symbol_size = 48;
        break;

    default:
        font_size = FONT_SMALL;
        high_pages = 1;
        width_cols = 8;
        symbol_size = 8;
        break;
    }
}

extern void display_print(char const *const text)
{
    uint8_t text_len = 0;

    char const *ptr = &text[0];
    while (*ptr != 0 && text_len++ < 16)
    {
        uint8_t character = (*ptr) % 128;
        uint8_t const *const symbol = font_character(font_size, character);

        printf("%c", character);

        platform_ssd1306_symbol(line, line + high_pages - 1, column, column + width_cols - 1, symbol, symbol_size);

        column = ((column + width_cols) < 128) ? column + width_cols : column;

        ptr++;
    }
}

extern void display_draw(image_t const *const image)
{
    const uint8_t lines = (uint8_t)(image->height / 8);
    if ((line + lines - 1) > 3)
        return;

    const uint8_t columns = image->width;
    // const uint8_t data_size = sizeof(image->data) / sizeof(uint8_t);
    const uint8_t data_size = lines * columns;

    platform_ssd1306_symbol(line, line + lines - 1, column, column + columns - 1, image->data, data_size);
}

extern void display_clean()
{
    platform_ssd1306_clean();
}
