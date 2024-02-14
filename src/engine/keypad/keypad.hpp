/**
 * \file keypad.hpp
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#ifndef __ENGINE_KEYPAD_HPP__
#define __ENGINE_KEYPAD_HPP__

#include "keypad_keycode.hpp"

namespace engine
{
    namespace keypad
    {
        extern void push_key_event(const KEY_ID, const STATE);
        extern void set_mapping(const engine::keypad::TABLE);
        extern const engine::keypad::TABLE get_mapping(void);
        extern const uint8_t to_int(const engine::keypad::KEY_ID, const engine::keypad::TABLE);
        extern const engine::keypad::KEY_ID to_identifier(const uint8_t);
    }
}

#endif // __ENGINE_KEYPAD_HPP__