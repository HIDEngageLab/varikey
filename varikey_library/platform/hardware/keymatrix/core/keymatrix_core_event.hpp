/**
 * \file keymatrix_adp5585_event.hpp
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <stdint.h>

namespace platform::hardware::pico
{
    namespace event
    {
        enum class IDENTIFIER : uint8_t
        {
            UNDEFINED = 0,
            R1_C1 = 1,
            R1_C2 = 2,
            R1_C3 = 3,
            R1_C4 = 4,
            R1_C5 = 5,
            R2_C1 = 6,
            R2_C2 = 7,
            R2_C3 = 8,
            R2_C4 = 9,
            R2_C5 = 10,
            R3_C1 = 11,
            R3_C2 = 12,
            R3_C3 = 13,
            R3_C4 = 14,
            R3_C5 = 15,
        };

        enum class STATE : uint8_t
        {
            RELEASE = 0,
            PRESS = 1,
        };
    }

    struct event_t
    {
        event::IDENTIFIER identifier;
        event::STATE state;
    };
}
