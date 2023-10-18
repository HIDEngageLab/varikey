/**
 * \file temperature_rp2040.hpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#ifndef __PLATFORM_TEMPERATURE_RP2040_HPP__
#define __PLATFORM_TEMPERATURE_RP2040_HPP__

#include "temperature_interface.hpp"

namespace platform
{
    namespace driver
    {
        struct TemperatureRP2040 : public TemperatureInterface
        {
            const int get() const;
        };
    }
}

#endif /* __PLATFORM_TEMPERATURE_RP2040_HPP__ */
