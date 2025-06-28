/**
 * \file display.cpp
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#include <stdio.h>

#include "board_assembly.hpp"
#include "display.hpp"
#include "display_font.hpp"
#include "display_image.hpp"
#include "display_type.hpp"


namespace engine
{
    namespace display
    {
        uint8_t line = 0;
        uint8_t column = 0;

        engine::display::FONT font_size = engine::display::FONT::SMALL;

        extern void set_font(const engine::display::FONT _font)
        {
            font_size = _font;
        }

        extern void set_cursor(const uint8_t _line, const uint8_t _column)
        {
            line = _line % platform::hardware::Display::R;
            column = _column % platform::hardware::Display::C;
        }

        extern void print(char const *const text)
        {
            uint8_t text_len = 0;

            char const *ptr = &text[0];
            while (*ptr != 0 && text_len++ < platform::hardware::Display::MAX_LINE_LENGTH)
            {
                const font::Type::Meta meta = font::get_meta(font_size);
                uint8_t const *const symbol = engine::display::font::get_character(font_size, *ptr);
                platform::board::assembly.display.symbol(line, line + meta.high_pages - 1,
                                                         column, column + meta.width_cols - 1,
                                                         symbol, meta.symbol_size);

                if ((column + meta.width_cols) < platform::hardware::Display::C)
                {
                    column += meta.width_cols;
                    ptr++;
                }
                else
                {
                    break;
                }
            }
        }

        void draw(const engine::display::ICON _icon)
        {
            const image::Type *image = image::get_image(_icon);

            const uint8_t lines = (uint8_t)(image->height / 8);
            if ((line + lines) > platform::hardware::Display::R)
                return;

            const uint8_t columns = image->width;
            const size_t data_size = lines * columns;

            platform::board::assembly.display.symbol(line, line + lines - 1,
                                                     column, column + columns - 1,
                                                     image->data, data_size);
        }

        void clean()
        {
            platform::board::assembly.display.clean();
        }
    }
}
