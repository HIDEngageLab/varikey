/**
 * \file backlight_type.hpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#ifndef PLATFORM_BACKLIGHT_HPP_
#define PLATFORM_BACKLIGHT_HPP_

#include "backlight_gossenmetrawatt.hpp"
#include "backlight_varikey.hpp"
#include "platform_defines.hpp"
#include "revision.h"

namespace platform
{
    namespace hardware
    {
        namespace backlight
        {
            template <platform::defines::Identifier>
            struct Entity
            {
                using Type = platform::Undefined;
            };

            template <>
            struct Entity<platform::defines::Identifier::VARIKEY_1_0>
            {
                using Type = platform::hardware::BacklightVarikey;
            };
            template <>
            struct Entity<platform::defines::Identifier::GOSSENMETRAWATT_1_0>
            {
                using Type = platform::hardware::BacklightGossenmetrawatt;
            };
        }
        using Backlight = backlight::Entity<platform::defines::Identifier(HARDWARE_IDENTIFIER)>::Type;
    }
}

#endif /* PLATFORM_BACKLIGHT_HPP_ */
