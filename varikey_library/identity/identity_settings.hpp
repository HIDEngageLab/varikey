// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: Identity settings configuration
// SPDX-FileType: SOURCE

#pragma once

#include "engine_defines.hpp"
#include "identity_10bwdb.hpp"
#include "identity_15sbla.hpp"
#include "identity_demo.hpp"
#include "revision.h"

namespace identity
{
    namespace variant
    {
        template <engine::defines::Identifier>
        struct Entity
        {
            using Settings = engine::Undefined;
        };

        template <>
        struct Entity<engine::defines::Identifier::KEYPAD_DEMO>
        {
            using Settings = engine::identity::IdentityDemo;
        };

        template <>
        struct Entity<engine::defines::Identifier::KEYPAD_10BWDB>
        {
            using Settings = engine::identity::Identity10BWDB;
        };

        template <>
        struct Entity<engine::defines::Identifier::KEYPAD_15SBLA>
        {
            using Settings = engine::identity::Identity15SBLA;
        };
    }
    using Settings = identity::variant::Entity<engine::defines::Identifier(identity::firmware::IDENTIFIER)>::Settings;
}
