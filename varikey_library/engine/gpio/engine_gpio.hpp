// SPDX-FileCopyrightText: 2024 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: engine gpio module
// SPDX-FileType: SOURCE

#pragma once

#include "board_defines.hpp"

namespace engine::gpio
{
    using IDENTIFIER = platform::board::IDENTIFIER;
    using DIRECTION = platform::board::DIRECTION;
    using VALUE = platform::board::VALUE;

    extern void set_direction(const IDENTIFIER, DIRECTION);
    extern const DIRECTION get_direction(const IDENTIFIER);
    extern void set_value(const IDENTIFIER, const bool);
    extern const VALUE get_value(const IDENTIFIER);
    extern void enable_event(const bool);
}
