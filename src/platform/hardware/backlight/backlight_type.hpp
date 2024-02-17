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
                    using Type = VarikeyPrototype;
                };
                template <>
                struct Entity<platform::defines::IDENTIFIER::GOSSENMETRAWATT_1_0>
                {
                    using Type = GMCI1;
                };
            }
        }
        using Backlight = backlight::variant::Entity<platform::defines::IDENTIFIER(identity::hardware::IDENTIFIER)>::Type;
    }
}

#endif /* PLATFORM_BACKLIGHT_HPP_ */
