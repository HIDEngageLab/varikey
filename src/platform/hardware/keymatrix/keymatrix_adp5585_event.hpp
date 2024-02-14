/**
 * \file keymatrix_adp5585_event.hpp
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#ifndef __PLATFORM_KEYMATRIX_ADP5585_EVENT_HPP__
#define __PLATFORM_KEYMATRIX_ADP5585_EVENT_HPP__

#include <stdint.h>

namespace platform
{
    namespace hardware
    {
        namespace adp5585
        {
            namespace event
            {

                enum class IDENTIFIER : uint8_t
                {
                    UNDEFINED = 0,
                    R0_C0 = 1,
                    R0_C1 = 2,
                    R0_C2 = 3,
                    R0_C3 = 4,
                    R0_C4 = 5,
                    R1_C0 = 6,
                    R1_C1 = 7,
                    R1_C2 = 8,
                    R1_C3 = 9,
                    R1_C4 = 10,
                    R2_C0 = 11,
                    R2_C1 = 12,
                    R2_C2 = 13,
                    R2_C3 = 14,
                    R2_C4 = 15,
                    R3_C0 = 16,
                    R3_C1 = 17,
                    R3_C2 = 18,
                    R3_C3 = 19,
                    R3_C4 = 20,
                    R4_C0 = 21,
                    R4_C1 = 22,
                    R4_C2 = 23,
                    R4_C3 = 24,
                    R4_C4 = 25,
                    R5_C0 = 26,
                    R5_C1 = 27,
                    R5_C2 = 28,
                    R5_C3 = 29,
                    R5_C4 = 30,
                    R0_GND = 31,
                    R1_GND = 32,
                    R2_GND = 33,
                    R3_GND = 34,
                    R4_GND = 35,
                    R5_GND = 36,
                    R0_GPI_1 = 37,
                    R1_GPI_2 = 38,
                    R2_GPI_3 = 39,
                    R3_GPI_4 = 40,
                    R4_GPI_5 = 41,
                    R5_GPI_6 = 42,
                    C0_GPI_7 = 43,
                    C1_GPI_8 = 44,
                    C2_GPI_9 = 45,
                    C3_GPI_10 = 46,
                    C4_GPI_11 = 47,
                    LOGIC = 48,
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
    }
}

#endif // __PLATFORM_KEYMATRIX_ADP5585_EVENT_HPP__
