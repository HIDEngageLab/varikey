// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: Hardware ssd1306 functionality
// SPDX-FileType: SOURCE

#pragma once

#include <stdint.h>

namespace platform::hardware::ssd1306
{
    extern void initialize(const uint8_t DATA_COMMAND_SELECT_PIN,
                           const uint8_t SPI_CSN_PIN);
    extern void clean(void);
    extern void mask(uint8_t const *const image);
    extern void symbol(uint8_t const page_start, uint8_t const page_end,
                       uint8_t const column_start, uint8_t const column_end,
                       uint8_t const *const data, size_t const len);
    extern void set_inverse(void);
    extern void set_normal(void);
}
