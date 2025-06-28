/**
 * \file keymatrix_adp5585_handler_type.hpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "keymatrix_handler_type_gmc.hpp"
#include "keymatrix_handler_type_varikey.hpp"
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
        struct Entity<platform::defines::IDENTIFIER::VARIKEY_1_0>
        {
            using Type = platform::hardware::KeymatrixHandlerVarikey;
        };

        template <>
        struct Entity<platform::defines::IDENTIFIER::GOSSENMETRAWATT_1_0>
        {
            using Type = platform::hardware::KeymatrixHandlerGmc;
        };

    }
    using KeyHandler = platform::hardware::handler::variant::Entity<platform::defines::IDENTIFIER(identity::hardware::IDENTIFIER)>::Type;
}
