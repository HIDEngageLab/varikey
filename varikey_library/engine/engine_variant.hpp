// SPDX-FileCopyrightText: 2024 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: Engine variant definitions
// SPDX-FileType: SOURCE

#pragma once

#include "engine_defines.hpp"
#include "engine_defines_gmc.hpp"
#include "engine_defines_varikey.hpp"
#include "engine_defines_varikey_15sbla.hpp"
#include "revision.h"

namespace engine
{
    namespace variant
    {
        template <engine::defines::Identifier>
        struct Entity
        {
            using Type = engine::Undefined;
        };

        template <>
        struct Entity<engine::defines::Identifier::KEYPAD_DEMO>
        {
            using Type = engine::defines::Varikey;
        };

        template <>
        struct Entity<engine::defines::Identifier::KEYPAD_15SBLA>
        {
            using Type = engine::defines::Varikey15SBLA;
        };

        template <>
        struct Entity<engine::defines::Identifier::KEYPAD_10BWDB>
        {
            using Type = engine::defines::Gmci;
        };
    }
    using Variant = engine::variant::Entity<engine::defines::Identifier(identity::firmware::IDENTIFIER)>::Type;
}
