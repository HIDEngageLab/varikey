// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: Hardware rp2040 soc varikey functionality
// SPDX-FileType: SOURCE

#pragma once

#include "rp2040_soc.hpp"

namespace platform::soc
{
    struct RP2040Varikey : public RP2040
    {
        static const uint8_t DEBUG_PIN_1 = 6;
        static const uint8_t DEBUG_PIN_2 = 7;
        static const uint8_t DEBUG_PIN_3 = 8;
        static const uint8_t DEBUG_PIN_4 = 9;
    };
}
