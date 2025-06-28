/**
 * \file rp2040_soc_varikey.hpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "rp2040_soc.hpp"

namespace platform
{
    namespace soc
    {
        struct RP2040Varikey15SBLA : public RP2040
        {
            static const uint8_t DEBUG_PIN_1 = 12;
            static const uint8_t DEBUG_PIN_2 = 14;
            static const uint8_t DEBUG_PIN_3 = 15;
            static const uint8_t DEBUG_PIN_4 = 16;
        };
    }
}
