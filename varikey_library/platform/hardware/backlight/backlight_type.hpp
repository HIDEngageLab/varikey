// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: Hardware backlight type functionality
// SPDX-FileType: SOURCE

#pragma once

#include "backlight_gmc.hpp"
#include "backlight_varikey.hpp"
#include "backlight_varikey_15sbla.hpp"
#include "platform_defines.hpp"
#include "revision.h"

namespace platform::hardware
{
    namespace backlight::variant
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
        struct Entity<platform::defines::IDENTIFIER::VARIKEY_2_3>
        {
            using Type = Varikey15SBLA;
        };

        template <>
        struct Entity<platform::defines::IDENTIFIER::GMCI_1_0>
        {
            using Type = GMCI1;
        };
    }
    using Backlight = backlight::variant::Entity<platform::defines::IDENTIFIER(identity::hardware::IDENTIFIER)>::Type;
}
