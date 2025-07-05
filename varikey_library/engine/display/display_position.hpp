// SPDX-FileCopyrightText: 2024 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: Display position definitions
// SPDX-FileType: SOURCE

#pragma once

#include <cstdint>

namespace engine::display
{
    struct Position
    {
        uint8_t line;
        uint8_t column;
    };
}
