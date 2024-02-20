/**
 * \file board_defines.hpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <cstdint>

namespace platform
{
    namespace board
    {
        typedef void (*ticker_handler_t)(void);
        typedef void (*callback_t)(const uint8_t, bool);

        enum class IDENTIFIER : uint8_t
        {
            GPIO0 = 0x5a,
            GPIO1 = 0x5b,
            GPIO2 = 0x5c,
            GPIO3 = 0x5d,

            UNDEFINED = 0xff,
        };

        enum class DIRECTION : uint8_t
        {
            INPUT = 0x00,
            OUTPUT = 0x01,

            UNDEFINED = 0xff,
        };
        enum class VALUE : uint8_t
        {
            LOW = 0x00,
            HIGH = 0x01,

            UNDEFINED = 0xff,
        };
    }
}