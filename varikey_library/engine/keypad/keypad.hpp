// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: keypad module
// SPDX-FileType: SOURCE

#pragma once

#include "keypad_keycode.hpp"
#include "keypad_modifiers.hpp"

namespace engine::keypad
{
    extern void switch_key(const KEY_ID, const STATE);
    extern void press_key(const KEY_ID);
    extern void release_ley(const KEY_ID);

    extern void set_mapping(const TABLE);
    extern const TABLE get_mapping(void);

    extern void enable_nums(const bool);
    extern void enable_cups(const bool);
    extern void enable_scroll(const bool);

    extern void perform(const KEY_ID);
    extern void reset(void);

    extern const uint8_t id2int(const KEY_ID);
    extern const KEY_ID int2id(const uint8_t);
}
