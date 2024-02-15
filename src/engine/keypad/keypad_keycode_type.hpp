/**
 * \file keypad_keycode_type.hpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#ifndef __ENGINE_KEYPAD_KEYCODE_TYPE_HPP__
#define __ENGINE_KEYPAD_KEYCODE_TYPE_HPP__

#include "engine_defines.hpp"
#include "keypad_keycode_10bwdb.hpp"
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
        }
    }
    using Keycode = engine::keypad::variant::Entity<engine::defines::Identifier(identity::firmware::IDENTIFIER)>::Type;
}

#endif /* __ENGINE_KEYPAD_KEYCODE_VARIANT_HPP__ */
