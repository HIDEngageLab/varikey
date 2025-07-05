// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: Hardware soc type functionality
// SPDX-FileType: SOURCE

#pragma once

#include "platform_defines.hpp"
#include "revision.h"
#include "rp2040_soc_gmci.hpp"
#include "rp2040_soc_varikey.hpp"
#include "rp2040_soc_varikey_15sbla.hpp"

namespace platform::driver
{
    namespace soc::variant
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
        struct Entity<platform::defines::IDENTIFIER::GMCI_1_0>
        {
            using Type = platform::soc::RP2040Gmci;
        };
    }
    using SoC = soc::variant::Entity<platform::defines::IDENTIFIER(identity::hardware::IDENTIFIER)>::Type;
}
