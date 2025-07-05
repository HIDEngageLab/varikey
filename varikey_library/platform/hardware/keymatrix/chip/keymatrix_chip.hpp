// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: Keymatrix chip keymatrix chip functionality
// SPDX-FileType: SOURCE

#pragma once

// #include <pico/stdlib.h>

#include <cstdint>
#include <cstdlib>

namespace platform::hardware
{
    extern void platform_adp5585_init(int const _address);
    extern bool platform_adp5585_has_event(void);
    extern void platform_adp5585_get_event(uint8_t *const _state, uint8_t *const _identifier);
}