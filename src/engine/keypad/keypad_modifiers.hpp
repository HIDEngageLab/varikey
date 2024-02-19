/**
 * \file keypad_modifiers.hpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#ifndef __ENGINE_KEYPAD_MODIFIERS_HPP__
#define __ENGINE_KEYPAD_MODIFIERS_HPP__

#include <cstdint>

namespace engine
{
    namespace keypad
    {
        extern void enable_shift(const bool);
        extern void enable_alt(const bool);
        extern void enable_ctrl(const bool);

        extern const uint8_t get_modifier(void);
    }
}

#endif /* __ENGINE_KEYPAD_MODIFIERS_HPP__ */