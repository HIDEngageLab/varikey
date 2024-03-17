/**
 * \file keypad_modifiers.cpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#include "keypad_modifiers.hpp"

namespace engine
{
    namespace keypad
    {
        MODIFIER modifier;

        /**
         * \brief
         *
         * \param _enable
         */
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
}
