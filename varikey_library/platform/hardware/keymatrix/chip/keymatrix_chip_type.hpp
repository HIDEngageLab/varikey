/**
 * \file keymatrix.hpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "keymatrix_type_gmc.hpp"
#include "keymatrix_type_varikey.hpp"
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
        struct Entity<platform::defines::IDENTIFIER::VARIKEY_1_0>
        {
            using Type = platform::hardware::KeymatrixApd5585Varikey;
        };

        template <>
        struct Entity<platform::defines::IDENTIFIER::GOSSENMETRAWATT_1_0>
        {
            using Type = platform::hardware::KeymatrixApd5585Gmc;
        };
    }
    using Keymatrix = keymatrix::variant::Entity<platform::defines::IDENTIFIER(identity::hardware::IDENTIFIER)>::Type;
}
