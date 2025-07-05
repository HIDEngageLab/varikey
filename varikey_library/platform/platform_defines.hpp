// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: Platform-specific definitions and configurations
// SPDX-FileType: SOURCE

#pragma once

#include <cstdint>

#include "revision.h"

namespace platform
{
    struct Undefined
    {
    };

    namespace defines
    {
        enum class IDENTIFIER
        {
            GMCI_1_0 = 2,
            VARIKEY_1_0 = 1,
            VARIKEY_2_3 = 3,
        };

        namespace usb
        {
            static const uint16_t PID_MASK = 0xffe0;
            static const uint16_t PID = (identity::firmware::IDENTIFIER << 5) & PID_MASK;
            static const uint16_t VID = identity::firmware::VENDOR;
        }
    }
}
