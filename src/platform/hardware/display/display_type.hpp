/**
 * \file display_type.hpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#ifndef PLATFORM_DISPLAY_HPP_
#define PLATFORM_DISPLAY_HPP_

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
            template <platform::defines::Identifier>
            struct Entity
            {
                using Type = platform::Undefined;
            };

            template <>
            struct Entity<platform::defines::Identifier::VARIKEY_1_0>
            {
                using Type = platform::hardware::DisplayOLED128x32Varikey;
            };
            template <>
            struct Entity<platform::defines::Identifier::GOSSENMETRAWATT_1_0>
            {
                using Type = platform::hardware::DisplayOLED128x32Gossenmetrawatt;
            };
        }
        using Display = display::Entity<platform::defines::Identifier(HARDWARE_IDENTIFIER)>::Type;
    }
}

#endif /* PLATFORM_DISPLAY_HPP_ */
