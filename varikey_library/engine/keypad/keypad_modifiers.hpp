// SPDX-FileCopyrightText: 2024 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: keypad modifiers module
// SPDX-FileType: SOURCE

#pragma once

#include <cstdint>

namespace engine::keypad
{
    union MODIFIER
    {
        uint8_t value;
        struct
        {
            uint8_t right_meta : 1;
            uint8_t right_alt : 1;
            uint8_t right_shift : 1;
            uint8_t right_ctrl : 1;
            uint8_t left_meta : 1;
            uint8_t left_alt : 1;
            uint8_t left_shift : 1;
            uint8_t left_ctrl : 1;
        };
    };

    extern void enable_shift(const bool);
    extern void enable_alt(const bool);
    extern void enable_ctrl(const bool);

    extern void set_modifier(const MODIFIER);
    extern const MODIFIER get_modifier(void);
}
