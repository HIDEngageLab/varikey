/**
 * \file engine_variant.hpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#ifndef __ENGINE_ENGINE_TYPE_HPP__
#define __ENGINE_ENGINE_TYPE_HPP__

#include "engine_defines.hpp"
#include "engine_defines_gossenmetrawatt.hpp"
#include "engine_defines_varikey.hpp"
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
        struct Entity<engine::defines::Identifier::KEYPAD_10BWDB>
        {
            using Type = engine::defines::Gossenmetrawatt;
        };
    }
    using Variant = engine::variant::Entity<engine::defines::Identifier(identity::firmware::IDENTIFIER)>::Type;
}

#endif /* __ENGINE_ENGINE_TYPE_HPP__ */
