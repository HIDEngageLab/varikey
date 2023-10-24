/**
 * \file display.cpp
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#include <stdio.h>

#include "display.hpp"
#include "display_type.hpp"
#include "font_big.h"
#include "font_huge.h"
#include "font_identifier.hpp"
#include "font_normal.h"
#include "font_small.h"
#include "font_symbol.h"
#include "image_frame.h"
#include "image_gmc.h"
#include "image_heart.h"
#include "image_identifier.hpp"
#include "image_type.hpp"
#include "image_varikey.h"
#include "ssd1306.hpp"

/**
 * \brief number of signs in a font ASCII 0-127
 */
/* @{ */
#define NUMBER_OF_SIGNS 128
/* @} */

uint8_t line = 0;
uint8_t column = 0;

FONT_SIZE font_size = FONT_SIZE::FONT_SMALL;
uint8_t high_pages = 1;
uint8_t width_cols = 7;
uint8_t symbol_size = 8;

const unsigned char **font[5] = {
    FONT_TABLE_SMALL,
    FONT_TABLE_NORMAL,
    FONT_TABLE_BIG,
    FONT_TABLE_HUGE,
    FONT_TABLE_SYMBOL,
};

const image_t images[4] = {
    {.width = 128, .height = 32, .data = IMAGE_FRAME},
    {.width = 32, .height = 32, .data = IMAGE_VARIKEY},
    {.width = 32, .height = 32, .data = IMAGE_GMC},
    {.width = 32, .height = 32, .data = IMAGE_HEART},
};

static const uint8_t get_image_index(const KEYPAD_ICON _icon);
static const uint8_t *const font_character(const FONT_SIZE font, uint8_t const ascii);

extern void display_set_cursor(const uint8_t _line, const uint8_t _column)
{
    line = _line % platform::hardware::Display::R;
    column = _column % platform::hardware::Display::C;
}

extern void display_set_font(const FONT_SIZE size)
{
    switch (size)
    {
    case FONT_SIZE::FONT_SMALL:
        font_size = size;
        high_pages = 1;
        width_cols = 7;
        symbol_size = 8;
        break;

    case FONT_SIZE::FONT_NORMAL:
        font_size = size;
        high_pages = 2;
        width_cols = 8;
        symbol_size = 16;
        break;

    case FONT_SIZE::FONT_BIG:
        font_size = size;
        high_pages = 3;
        width_cols = 16;
        symbol_size = 48;
        break;

    case FONT_SIZE::FONT_HUGE:
        font_size = size;
        high_pages = 4;
        width_cols = 24;
        symbol_size = 96;
        break;

    case FONT_SIZE::FONT_SYMBOL:
        font_size = size;
        high_pages = 2;
        width_cols = 16;
        symbol_size = 32;
        break;

    default:
        font_size = FONT_SIZE::FONT_SMALL;
        high_pages = 1;
        width_cols = 7;
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
        uint8_t character = (*ptr) % NUMBER_OF_SIGNS;
        uint8_t const *const symbol = font_character(font_size, character);

        platform::hardware::platform_ssd1306_symbol(line, line + high_pages - 1, column, column + width_cols - 1, symbol, symbol_size);

        column = ((column + width_cols) < platform::hardware::Display::C) ? column + width_cols : column;

        ptr++;
    }
}

extern void display_draw(const KEYPAD_ICON _icon)
{
    const image_t *image = &images[get_image_index(_icon)];

    const uint8_t lines = (uint8_t)(image->height / 8);
    if ((line + lines) > platform::hardware::Display::R)
        return;

    const uint8_t columns = image->width;
    // const uint8_t data_size = sizeof(image->data) / sizeof(uint8_t);
    const uint8_t data_size = lines * columns;

    platform::hardware::platform_ssd1306_symbol(line, line + lines - 1, column, column + columns - 1, image->data, data_size);
}

extern void display_clean()
{
    platform::hardware::platform_ssd1306_clean();
}

static const uint8_t *const font_character(const FONT_SIZE font_size, uint8_t const ascii)
{
    uint8_t font_index = 0;
    switch (font_size)
    {
    case FONT_SIZE::FONT_SMALL:
        font_index = 0;
        break;
    case FONT_SIZE::FONT_NORMAL:
        font_index = 1;
        break;
    case FONT_SIZE::FONT_BIG:
        font_index = 2;
        break;
    case FONT_SIZE::FONT_HUGE:
        font_index = 3;
        break;
    case FONT_SIZE::FONT_SYMBOL:
        font_index = 4;
        break;
    default:
        font_index = 0;
        break;
    }
    return font[font_index][ascii];
}

static const uint8_t get_image_index(const KEYPAD_ICON _icon)
{
    uint8_t image_index = 0;
    switch (_icon)
    {
    case KEYPAD_ICON::KEYPAD_ICON_FRAME:
        image_index = 0;
        break;
    case KEYPAD_ICON::KEYPAD_ICON_VARIKEY_LOGO:
        image_index = 1;
        break;
    case KEYPAD_ICON::KEYPAD_ICON_GOSSENMETRAWATT_LOGO:
        image_index = 2;
        break;
    case KEYPAD_ICON::KEYPAD_ICON_HEART:
        image_index = 3;
        break;
    default:
        image_index = 0;
        break;
    }

    return image_index;
}
