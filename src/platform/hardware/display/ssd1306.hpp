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
        extern void platform_ssd1306_init(uint8_t data_command_select_pin);
        extern void platform_ssd1306_clean(void);
        extern void platform_ssd1306_mask(uint8_t const *const image);
        extern void platform_ssd1306_symbol(uint8_t const page_start, uint8_t const page_end, uint8_t const column_start, uint8_t const column_end, uint8_t const *const data, uint8_t const len);
        extern void platform_ssd1306_set_inverse(void);
        extern void platform_ssd1306_set_normal(void);
    }
}

#endif // __PLATFORM_SSD1306_HPP__
