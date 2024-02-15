/**
 * \file keymatrix.hpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#ifndef __PLATFORM_KEYMATRIX_ADP5585_TYPE_HPP__
#define __PLATFORM_KEYMATRIX_ADP5585_TYPE_HPP__

#include "keymatrix_adp5585_gossenmetrawatt.hpp"
#include "keymatrix_adp5585_varikey.hpp"
#include "platform_defines.hpp"
#include "revision.h"

namespace platform
{
    namespace hardware
    {
        namespace keymatrix
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
                    using Type = platform::hardware::KeymatrixApd5585Varikey;
                };
                template <>
                struct Entity<platform::defines::IDENTIFIER::GOSSENMETRAWATT_1_0>
                {
                    using Type = platform::hardware::KeymatrixApd5585Gossenmetrawatt;
                };
            }
        }
        using Keymatrix = keymatrix::variant::Entity<platform::defines::IDENTIFIER(identity::hardware::IDENTIFIER)>::Type;
    }
}

#endif /* __PLATFORM_KEYMATRIX_ADP5585_TYPE_HPP__ */
