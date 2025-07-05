// SPDX-FileCopyrightText: 2024 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: Keymatrix chip keymatrix chip handler type functionality
// SPDX-FileType: SOURCE

#pragma once

#include "keymatrix_handler_type_gmc.hpp"
#include "keymatrix_handler_type_varikey.hpp"
#include "platform_defines.hpp"
#include "revision.h"

namespace platform::hardware
{
    namespace handler::variant
    {
        template <platform::defines::IDENTIFIER>
        struct Entity
        {
            using Type = platform::Undefined;
        };

        template <>
        struct Entity<platform::defines::IDENTIFIER::VARIKEY_1_0>
        {
            using Type = platform::hardware::KeymatrixHandlerVarikey;
        };

        template <>
        struct Entity<platform::defines::IDENTIFIER::GMCI_1_0>
        {
            using Type = platform::hardware::KeymatrixHandlerGmc;
        };

    }
    using KeyHandler = platform::hardware::handler::variant::Entity<platform::defines::IDENTIFIER(identity::hardware::IDENTIFIER)>::Type;
}
