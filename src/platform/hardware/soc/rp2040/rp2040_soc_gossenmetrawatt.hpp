/**
 * \file rp2040_soc_gossenmetrawatt.hpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#ifndef __PLATFORM_SOC_RP2040_GOSSENMETRAWATT_HPP__
#define __PLATFORM_SOC_RP2040_GOSSENMETRAWATT_HPP__

#include "rp2040_soc.hpp"

namespace platform
{
    namespace soc
    {
        struct RP2040Gossenmetrawatt : public RP2040
        {
            static const uint8_t DEBUG_PIN_1 = 2;
            static const uint8_t DEBUG_PIN_2 = 3;
            static const uint8_t DEBUG_PIN_3 = 4;
            static const uint8_t DEBUG_PIN_4 = 5;
        };
    }
}

#endif /* __PLATFORM_SOC_RP2040_GOSSENMETRAWATT_HPP__ */
