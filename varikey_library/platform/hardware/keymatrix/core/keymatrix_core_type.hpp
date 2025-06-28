/**
 * \file keymatrix.hpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "keymatrix_type_varikey_15sbla.hpp"
#include "platform_defines.hpp"
#include "revision.h"

namespace platform::hardware
{
    namespace keymatrix::variant
    {

        template <platform::defines::IDENTIFIER>
        struct Entity
        {
            using Type = platform::Undefined;
        };

        template <>
        struct Entity<platform::defines::IDENTIFIER::VARIKEY_2_3>
        {
            using Type = platform::hardware::KeymatrixVarikey15SBLA;
        };

    }
    using Keymatrix = keymatrix::variant::Entity<platform::defines::IDENTIFIER(identity::hardware::IDENTIFIER)>::Type;
}
