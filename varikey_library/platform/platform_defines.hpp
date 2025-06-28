/**
 * \file platform_defines.hpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#ifndef __PLATFORM_DEFINES_HPP__
#define __PLATFORM_DEFINES_HPP__

#include <cstdint>

#include "revision.h"

namespace platform
{
    struct Undefined
    {
    };

    namespace defines
    {
        enum class IDENTIFIER
        {
            GOSSENMETRAWATT_1_0 = 2,
            VARIKEY_1_0 = 1,
            VARIKEY_2_3 = 3,
        };

        namespace usb
        {
            static const uint16_t PID_MASK = 0xffe0;
            static const uint16_t PID = (identity::firmware::IDENTIFIER << 5) & PID_MASK; /* mask: 0xffe0, 5 lsb are reserved for product interface capabilities */
            static const uint16_t VID = identity::firmware::VENDOR;
        }
    }
}

#endif // __PLATFORM_DEFINES_HPP__
