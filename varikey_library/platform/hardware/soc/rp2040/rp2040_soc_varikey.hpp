/**
 * \file rp2040_soc_varikey.hpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#ifndef __PLATFORM_SOC_RP2040_VARIKEY_HPP__
#define __PLATFORM_SOC_RP2040_VARIKEY_HPP__

#include "rp2040_soc.hpp"

namespace platform
{
    namespace soc
    {
        struct RP2040Varikey : public RP2040
        {
            static const uint8_t DEBUG_PIN_1 = 6;
            static const uint8_t DEBUG_PIN_2 = 7;
            static const uint8_t DEBUG_PIN_3 = 8;
            static const uint8_t DEBUG_PIN_4 = 9;
        };
    }
}

#endif /* __PLATFORM_SOC_RP2040_VARIKEY_HPP__ */
