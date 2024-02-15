/**
 * \file keymatrix_adp5585_handler_type.hpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#ifndef __PLATFORM_KEYMATRIX_ADP5585_HANDLER_TYPE_HPP__
#define __PLATFORM_KEYMATRIX_ADP5585_HANDLER_TYPE_HPP__

#include "keymatrix_adp5585_handler_gossenmetrawatt.hpp"
#include "keymatrix_adp5585_handler_varikey.hpp"
#include "platform_defines.hpp"
#include "revision.h"

namespace platform
{
    namespace hardware
    {
        namespace handler
        {
            namespace variant
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
                    using Type = platform::hardware::KeymatrixHandlerGossenmetrawatt;
                };

            }
        }
        using KeyHandler = platform::hardware::handler::variant::Entity<platform::defines::IDENTIFIER(identity::hardware::IDENTIFIER)>::Type;
    }
}

#endif /* __PLATFORM_KEYMATRIX_ADP5585_HANDLER_TYPE_HPP__ */
