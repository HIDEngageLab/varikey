// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: Component state definitions
// SPDX-FileType: SOURCE

#pragma once

#include <stdint.h>

namespace pulp
{
    enum class COMPONENT_STATE : uint8_t
    {
        IDLE = 0x00,
        ACTIVE = 0x01,
        PENDING = 0x02,
        UNDEFINED = 0xff,
    };
}
