/**
 * \file display.hpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#ifndef PLATFORM_DISPLAY_H_
#define PLATFORM_DISPLAY_H_

#include "display_oled_128x32_gossenmetrawatt.hpp"
#include "display_oled_128x32_varikey.hpp"
#include "platform_defines.hpp"
#include "revision.h"

namespace platform
{
    namespace hardware
    {
        namespace display
        {
            template <platform::defines::Value>
            struct Entity
            {
                using Type = platform::Undefined;
            };

            template <>
            struct Entity<platform::defines::Value::VARIKEY_1_0>
            {
                using Type = platform::hardware::DisplayOLED128x32Varikey;
            };
            template <>
            struct Entity<platform::defines::Value::GOSSENMETRAWATT_1_0>
            {
                using Type = platform::hardware::DisplayOLED128x32Gossenmetrawatt;
            };
        }
        using Display = display::Entity<platform::defines::Value(HARDWARE_IDENTIFIER)>::Type;
    }
}

#endif /* PLATFORM_DISPLAY_H_ */
