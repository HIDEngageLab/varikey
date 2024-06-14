/**
 * \file identity_settings.hpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#ifndef __ENGINE_IDENTITY_SETTINGS_HPP__
#define __ENGINE_IDENTITY_SETTINGS_HPP__

#include "engine_defines.hpp"
#include "identity_10bwdb.hpp"
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
    }
    using Settings = identity::variant::Entity<engine::defines::Identifier(identity::firmware::IDENTIFIER)>::Settings;
}

#endif /* __ENGINE_IDENTITY_SETTINGS_HPP__ */
