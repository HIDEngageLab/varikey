// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: Hardware rp2040 soc varikey 15sbla functionality
// SPDX-FileType: SOURCE

#pragma once

#include "rp2040_soc.hpp"

namespace platform::soc
{
    struct RP2040Varikey15SBLA : public RP2040
    {
        static const uint8_t DEBUG_PIN_1 = 12;
        static const uint8_t DEBUG_PIN_2 = 14;
        static const uint8_t DEBUG_PIN_3 = 15;
        static const uint8_t DEBUG_PIN_4 = 16;
    };
}
