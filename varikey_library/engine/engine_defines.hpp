// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: Engine definitions and constants
// SPDX-FileType: SOURCE

#pragma once

#include <cstdint>

namespace engine
{
    struct Undefined
    {
    };

    namespace defines
    {
        enum class Identifier
        {
            KEYPAD_DEMO = 1,
            KEYPAD_10BWDB = 2,
            KEYPAD_15SBLA = 3,
        };

        enum class STATE : uint8_t
        {
            ACTIVE = 0x01,
            IDLE = 0x00,
            PENDING = 0x03,
            SUSPEND = 0x02,

            UNDEFINED = 0xff,
        };
    }
}
