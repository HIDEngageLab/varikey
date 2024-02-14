/**
 * \file display_font.hpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#ifndef __ENGINE_DISPLAY_FONTS_HPP__
#define __ENGINE_DISPLAY_FONTS_HPP__

#include <cstddef>
#include <cstdint>

namespace engine
{
    namespace display
    {
        enum class FONT : uint8_t
        {
            SMALL = 0x00, /* default */
            NORMAL = 0x01,
            BIG = 0x02,
            HUGE = 0x03,
            SYMBOL = 0x04,
            UNDEFINED = 0xff,
        };

        namespace font
        {
            struct Type
            {
                struct Meta
                {
                    uint8_t high_pages;
                    uint8_t width_cols;
                    size_t symbol_size;
                } meta;
                const unsigned char **data;
            };

            /**
             * \brief number of signs in a font ASCII 0-127
             */
            static const size_t NUMBER_OF_SIGNS = 128;

            static const size_t SIZE = 5;
            extern const Type font[SIZE];

            extern const bool is_defined(const engine::display::FONT);
            extern const Type::Meta &get_meta(const engine::display::FONT);
            extern const uint8_t *const get_character(const engine::display::FONT, uint8_t const ascii);
        }
    }
}

#endif /* __ENGINE_DISPLAY_FONTS_HPP__ */
