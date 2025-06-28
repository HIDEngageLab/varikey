/**
 * \file keypad_keycode_type.hpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "engine_defines.hpp"
#include "keypad_keycode_10bwdb.hpp"
#include "keypad_keycode_15sbla.hpp"
#include "keypad_keycode_varikey.hpp"
#include "revision.h"

namespace engine
{
    namespace keypad
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
                using Type = engine::keypad::KeypadVarikey;
            };

            template <>
            struct Entity<engine::defines::Identifier::KEYPAD_10BWDB>
            {
                using Type = engine::keypad::Keypad10BWDB;
            };

            template <>
            struct Entity<engine::defines::Identifier::KEYPAD_15SBLA>
            {
                using Type = engine::keypad::Keypad15SBLA;
            };
        }
    }
    using Keycode = engine::keypad::variant::Entity<engine::defines::Identifier(identity::firmware::IDENTIFIER)>::Type;
}
