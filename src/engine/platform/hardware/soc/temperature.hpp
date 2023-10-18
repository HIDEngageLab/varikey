/**
 * \file temperature.hpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#ifndef __PLATFORM_TEMPERATURE_HPP__
#define __PLATFORM_TEMPERATURE_HPP__

#include "platform_defines.hpp"
#include "temperature_rp2040.hpp"

namespace platform
{
    namespace driver
    {
        namespace temperature
        {
            template <platform::defines::Value>
            struct Entity
            {
                using Type = platform::Undefined;
            };

            template <>
            struct Entity<platform::defines::Value::VARIKEY_1_0>
            {
                using Type = platform::driver::TemperatureRP2040;
            };
            template <>
            struct Entity<platform::defines::Value::GOSSENMETRAWATT_1_0>
            {
                using Type = platform::driver::TemperatureRP2040;
            };
        }

        using Temperature = temperature::Entity<platform::defines::Value(HARDWARE_IDENTIFIER)>::Type;
    }
}

#endif /* __PLATFORM_TEMPERATURE_HPP__ */
