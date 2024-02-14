/**
 * \file board_type.hpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#ifndef __PLATFORM_BOARD_TYPE_HPP__
#define __PLATFORM_BOARD_TYPE_HPP__

#include "board_gossenmetrawatt_1_0.hpp"
#include "board_varikey_1_0.hpp"
#include "platform_defines.hpp"
#include "revision.h"

namespace platform
{
    namespace board
    {
        template <platform::defines::Identifier>
        struct Entity
        {
            using Type = platform::Undefined;
        };

        template <>
        struct Entity<platform::defines::Identifier::VARIKEY_1_0>
        {
            using Type = platform::board::Varikey_1_0;
        };

        template <>
        struct Entity<platform::defines::Identifier::GOSSENMETRAWATT_1_0>
        {
            using Type = platform::board::Gossenmetrawatt_1_0;
        };
    }
    using Board = platform::board::Entity<platform::defines::Identifier(identity::hardware::IDENTIFIER)>::Type;
}

#endif /* __PLATFORM_BOARD_TYPE_HPP__ */
