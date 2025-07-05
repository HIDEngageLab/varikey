// SPDX-FileCopyrightText: 2024 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: keypad modifiers module
// SPDX-FileType: SOURCE

#include "keypad_modifiers.hpp"

namespace engine::keypad
{
    MODIFIER modifier;

    extern void enable_shift(const bool _enable)
    {
        if (_enable)
            modifier.left_shift = 1;
        else
            modifier.left_shift = 0;
    }

    extern void enable_alt(const bool _enable)
    {
        if (_enable)
            modifier.left_alt = 1;
        else
            modifier.left_alt = 0;
    }

    extern void enable_ctrl(const bool _enable)
    {
        if (_enable)
            modifier.left_ctrl = 1;
        else
            modifier.left_ctrl = 0;
    }

    extern void set_modifier(const MODIFIER _modifier)
    {
        modifier = _modifier;
    }

    extern const MODIFIER get_modifier(void)
    {
        return modifier;
    }
}
