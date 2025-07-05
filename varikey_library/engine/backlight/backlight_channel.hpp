// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: Smart LED channel enumeration
// SPDX-FileType: SOURCE

#pragma once

#include <stdint.h>

namespace engine::backlight
{
    enum class CHANNEL : uint8_t
    {
        FRONTLIGHT = 0x00,
        BACKLIGHT = 0x01,
        UNDEFINED = 0xff,
    };
}
