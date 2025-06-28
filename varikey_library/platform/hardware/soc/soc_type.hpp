/**
 * \file soc_type.hpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "platform_defines.hpp"
#include "revision.h"
#include "rp2040_soc_gossenmetrawatt.hpp"
#include "rp2040_soc_varikey.hpp"
#include "rp2040_soc_varikey_15sbla.hpp"

namespace platform
{
    namespace driver
    {
        namespace soc
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
                    using Type = platform::soc::RP2040Varikey;
                };

                template <>
                struct Entity<platform::defines::IDENTIFIER::VARIKEY_2_3>
                {
                    using Type = platform::soc::RP2040Varikey;
                };

                template <>
                struct Entity<platform::defines::IDENTIFIER::GOSSENMETRAWATT_1_0>
                {
                    using Type = platform::soc::RP2040Gossenmetrawatt;
                };
            }
        }
        using SoC = platform::driver::soc::variant::Entity<platform::defines::IDENTIFIER(identity::hardware::IDENTIFIER)>::Type;
    }
}
