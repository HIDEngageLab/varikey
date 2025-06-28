/**
 * \file keymatrix_adp5585_handler_type.hpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "keymatrix_handler_type_varikey_15sbla.hpp"
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
        struct Entity<platform::defines::IDENTIFIER::VARIKEY_2_3>
        {
            using Type = platform::hardware::KeymatrixHandlerVarikey15SBLA;
        };

    }
    using KeyHandler = platform::hardware::handler::variant::Entity<platform::defines::IDENTIFIER(identity::hardware::IDENTIFIER)>::Type;
}
