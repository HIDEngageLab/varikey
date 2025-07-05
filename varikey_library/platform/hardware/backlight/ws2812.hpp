// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: WS2812 LED driver interface for platform hardware abstraction
// SPDX-FileType: SOURCE

#pragma once

#include <stdint.h>

namespace platform::hardware::ws2812
{
    extern void init(void);
    extern void put_pixel(uint8_t r, uint8_t g, uint8_t b);
}
