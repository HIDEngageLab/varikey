/**
 * \file adp5585.hpp
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#ifndef __PLATFORM_ADP5585_HPP__
#define __PLATFORM_ADP5585_HPP__

#include <pico/stdlib.h>

namespace platform
{
    namespace hardware
    {
        extern void platform_adp5585_init(int const _address);
        extern bool platform_adp5585_has_event(void);
        extern void platform_adp5585_get_event(uint8_t *const _state, uint8_t *const _identifier);
    }
}

#endif // __PLATFORM_ADP5585_HPP__