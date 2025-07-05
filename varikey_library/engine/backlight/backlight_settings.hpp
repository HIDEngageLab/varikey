// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: Backlight settings configuration
// SPDX-FileType: SOURCE

#pragma once

#include "backlight_10bwdb.hpp"
#include "backlight_15sbla.hpp"
#include "backlight_demo.hpp"
#include "engine_defines.hpp"
#include "revision.h"

namespace engine::backlight
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
            using Settings = engine::backlight::BacklightDemo;
        };

        template <>
        struct Entity<engine::defines::Identifier::KEYPAD_10BWDB>
        {
            using Settings = engine::backlight::Backlight10BWDB;
        };

        template <>
        struct Entity<engine::defines::Identifier::KEYPAD_15SBLA>
        {
            using Settings = engine::backlight::Backlight15SBLA;
        };
    }
    using Settings = engine::backlight::variant::Entity<engine::defines::Identifier(identity::firmware::IDENTIFIER)>::Settings;
}
