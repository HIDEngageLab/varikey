/**
 * \file board_defines.hpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#pragma once

namespace platform
{
    namespace board
    {
        typedef void (*ticker_handler_t)(void);
        typedef void (*callback_t)(uint8_t, bool);

        enum class IDENTIFIER : uint8_t
        {
            GPIO0,
            GPIO1,
            GPIO2,
            GPIO3,
        };

        enum class DIRECTION : uint8_t
        {
            INPUT,
            OUTPUT,
            UNDEFINED = 0xff,
        };
        enum class VALUE : uint8_t
        {
            LOW,
            HIGH,
            UNDEFINED = 0xff,
        };
    }
}