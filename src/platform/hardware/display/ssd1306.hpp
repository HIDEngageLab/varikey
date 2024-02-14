/**
 * \file ssd1306.hpp
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#ifndef __PLATFORM_SSD1306_HPP__
#define __PLATFORM_SSD1306_HPP__

#include <stdint.h>

namespace platform
{
    namespace hardware
    {
        namespace ssd1306
        {
            extern void initialize(uint8_t data_command_select_pin);
            extern void clean(void);
            extern void mask(uint8_t const *const image);
            extern void symbol(uint8_t const page_start, uint8_t const page_end,
                               uint8_t const column_start, uint8_t const column_end,
                               uint8_t const *const data, size_t const len);
            extern void set_inverse(void);
            extern void set_normal(void);
        }
    }
}

#endif // __PLATFORM_SSD1306_HPP__
