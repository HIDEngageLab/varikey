/**
 * \file keymatrix_adp5585_handler_type.hpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#ifndef __PLATFORM_KEYMATRIX_ADP5585_HANDLER_TYPE_HPP__
#define __PLATFORM_KEYMATRIX_ADP5585_HANDLER_TYPE_HPP__

#include "keymatrix_adp5585_handler_varikey.hpp"
#include "keymatrix_adp5585_handler_gossenmetrawatt.hpp"
#include "platform_defines.hpp"
#include "revision.h"

namespace platform
{
    namespace hardware
    {
        namespace keymatrix
        {
            template <platform::defines::Identifier>
            struct Entity
            {
                using Type = platform::Undefined;
            };

            template <>
            struct Entity<platform::defines::Identifier::VARIKEY_1_0>
            {
                using Type = platform::hardware::KeymatrixHandlerVarikey;
            };
            template <>
            struct Entity<platform::defines::Identifier::GOSSENMETRAWATT_1_0>
            {
                using Type = platform::hardware::KeymatrixHandlerGossenmetrawatt;
            };

        }
        using KeyHandler = keymatrix::Entity<platform::defines::Identifier(identity::hardware::IDENTIFIER)>::Type;
    }
}

#endif /* __PLATFORM_KEYMATRIX_ADP5585_HANDLER_TYPE_HPP__ */
