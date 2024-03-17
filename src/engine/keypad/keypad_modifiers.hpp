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
}

#endif /* __ENGINE_KEYPAD_MODIFIERS_HPP__ */