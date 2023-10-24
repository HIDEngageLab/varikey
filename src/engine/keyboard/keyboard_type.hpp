/**
 * \file keyboard_type.hpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 * 
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#ifndef __ENGINE_KEYBOARD_TYPE_HPP__
#define __ENGINE_KEYBOARD_TYPE_HPP__

#include "keyboard_keycode_10bwdb.hpp"
#include "keyboard_keycode_demo.hpp"
#include "engine_defines.hpp"
#include "revision.h"

namespace engine
{
    namespace keypad
    {
        template <engine::defines::Identifier>
        struct Entity
        {
            using Type = engine::Undefined;
        };

        template <>
        struct Entity<engine::defines::Identifier::KEYPAD_DEMO>
        {
            using Type = engine::keypad::KeypadDemo;
        };

        template <>
        struct Entity<engine::defines::Identifier::KEYPAD_10BWDB>
        {
            using Type = engine::keypad::Keypad10BWDB;
        };
    }
    using Keypad = engine::keypad::Entity<engine::defines::Identifier(FIRMWARE_IDENTIFIER)>::Type;
}

#endif /* __ENGINE_KEYBOARD_TYPE_HPP__ */
