/**
 * \file platform_name.hpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#ifndef __PLATFORM_DEFINES_HPP__
#define __PLATFORM_DEFINES_HPP__

namespace platform
{
    struct Undefined
    {
    };

    namespace defines
    {
        enum class Value
        {
            VARIKEY_1_0 = 1,
            GOSSENMETRAWATT_1_0 = 2,
        };
    }
}

#endif // __PLATFORM_DEFINES_HPP__
