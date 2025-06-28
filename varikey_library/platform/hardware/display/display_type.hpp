/**
 * \file display_type.hpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "display_dummy.hpp"
#include "display_oled_128x32_gossenmetrawatt.hpp"
#include "display_oled_128x32_varikey.hpp"
#include "platform_defines.hpp"
#include "revision.h"

namespace platform::hardware
{
    namespace display
    {
        namespace variant
        {
            template <platform::defines::IDENTIFIER>
            struct Entity
            {
                using Type = platform::Undefined;
            };

            template <>
            struct Entity<platform::defines::IDENTIFIER::VARIKEY_1_0>
            {
                using Type = platform::hardware::DisplayOLED128x32Varikey;
            };

            template <>
            struct Entity<platform::defines::IDENTIFIER::VARIKEY_2_3>
            {
                using Type = platform::hardware::DisplayDummy;
            };

            template <>
            struct Entity<platform::defines::IDENTIFIER::GOSSENMETRAWATT_1_0>
            {
                using Type = platform::hardware::DisplayOLED128x32Gossenmetrawatt;
            };
        }
    }
    using Display = display::variant::Entity<platform::defines::IDENTIFIER(identity::hardware::IDENTIFIER)>::Type;
}
