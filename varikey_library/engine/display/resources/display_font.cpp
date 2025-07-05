// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: Display font implementation
// SPDX-FileType: SOURCE

#include "display_font.hpp"
#include "font_big.h"
#include "font_huge.h"
#include "font_normal.h"
#include "font_small.h"
#include "font_symbol.h"

namespace engine::display::font
{
    extern const Type font[SIZE] = {
        {.meta = {.high_pages = 1, .width_cols = 7, .symbol_size = 8}, .data = FONT_TABLE_SMALL},
        {.meta = {.high_pages = 2, .width_cols = 8, .symbol_size = 16}, .data = FONT_TABLE_NORMAL},
        {.meta = {.high_pages = 3, .width_cols = 16, .symbol_size = 48}, .data = FONT_TABLE_BIG},
        {.meta = {.high_pages = 4, .width_cols = 24, .symbol_size = 96}, .data = FONT_TABLE_HUGE},
        {.meta = {.high_pages = 2, .width_cols = 16, .symbol_size = 32}, .data = FONT_TABLE_SYMBOL},
    };

    static size_t get_font_index(const engine::display::FONT _font_size)
    {
        size_t font_index = 0;
        switch (_font_size)
        {
        case engine::display::FONT::SMALL:
            font_index = 0;
            break;
        case engine::display::FONT::NORMAL:
            font_index = 1;
            break;
        case engine::display::FONT::BIG:
            font_index = 2;
            break;
        case engine::display::FONT::HUGE:
            font_index = 3;
            break;
        case engine::display::FONT::SYMBOL:
            font_index = 4;
            break;
        default:
            font_index = 0;
            break;
        }
        return font_index;
    }

    extern const bool is_defined(const engine::display::FONT _font)
    {
        if (_font == FONT::SMALL)
        {
            return true;
        }
        else if (_font == FONT::NORMAL)
        {
            return true;
        }
        else if (_font == FONT::BIG)
        {
            return true;
        }
        else if (_font == FONT::HUGE)
        {
            return true;
        }
        else if (_font == FONT::SYMBOL)
        {
            return true;
        }
        return false;
    }

    extern const engine::display::font::Type::Meta &get_meta(const engine::display::FONT _font)
    {
        const size_t font_index = get_font_index(_font);
        return font[font_index].meta;
    }

    extern const uint8_t *const get_character(const engine::display::FONT _font, uint8_t const ascii)
    {
        const size_t font_index = get_font_index(_font);
        const uint8_t character = ascii % NUMBER_OF_SIGNS;
        return font[font_index].data[character];
    }
}