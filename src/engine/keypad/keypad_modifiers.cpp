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
        enum MODIFIER
        {
            KEY_MOD_LCTRL = 0x01,
            KEY_MOD_LSHIFT = 0x02,
            KEY_MOD_LALT = 0x04,
            KEY_MOD_LMETA = 0x08,
            KEY_MOD_RCTRL = 0x10,
            KEY_MOD_RSHIFT = 0x20,
            KEY_MOD_RALT = 0x40,
            KEY_MOD_RMETA = 0x80,
        };

        uint8_t modifier;

        static void add_modifier_mask(const MODIFIER _mask) { modifier |= _mask; }
        static void reset_modifier_mask(const MODIFIER _mask) { modifier &= ~_mask; }

        /**
         * \brief 
         * 
         * \param _enable 
         */
        extern void enable_shift(const bool _enable)
        {
            if (_enable)
                add_modifier_mask(MODIFIER::KEY_MOD_LSHIFT);
            else
                reset_modifier_mask(MODIFIER::KEY_MOD_LSHIFT);
        }

        extern void enable_alt(const bool _enable)
        {
            if (_enable)
                add_modifier_mask(MODIFIER::KEY_MOD_LALT);
            else
                reset_modifier_mask(MODIFIER::KEY_MOD_LALT);
        }

        extern void enable_ctrl(const bool _enable)
        {
            if (_enable)
                add_modifier_mask(MODIFIER::KEY_MOD_LCTRL);
            else
                reset_modifier_mask(MODIFIER::KEY_MOD_LCTRL);
        }

        extern const uint8_t get_modifier(void)
        {
            return modifier;
        }

    }
}