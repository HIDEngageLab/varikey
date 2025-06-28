/**
 * \file backlight_settings.hpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "backlight_10bwdb.hpp"
#include "backlight_15sbla.hpp"
#include "backlight_demo.hpp"
#include "engine_defines.hpp"
#include "revision.h"

namespace engine
{
    namespace backlight
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
    using BacklightSetting = engine::backlight::Entity<engine::defines::Identifier(identity::firmware::IDENTIFIER)>::Settings;
}
