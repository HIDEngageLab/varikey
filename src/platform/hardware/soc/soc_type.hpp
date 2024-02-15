/**
 * \file soc_type.hpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#ifndef __PLATFORM_SOC_TYPE_HPP__
#define __PLATFORM_SOC_TYPE_HPP__

#include "platform_defines.hpp"
#include "revision.h"
#include "rp2040_soc_gossenmetrawatt.hpp"
#include "rp2040_soc_varikey.hpp"

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
                struct Entity<platform::defines::IDENTIFIER::GOSSENMETRAWATT_1_0>
                {
                    using Type = platform::soc::RP2040Gossenmetrawatt;
                };
            }
        }
        using SoC = platform::driver::soc::variant::Entity<platform::defines::IDENTIFIER(identity::hardware::IDENTIFIER)>::Type;
    }
}

#endif // __PLATFORM_SOC_TYPE_HPP__
