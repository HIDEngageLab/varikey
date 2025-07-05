// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: Keypad parameter implementation
// SPDX-FileType: SOURCE

#include <stdlib.h>
#include <string.h>

#include "keypad_keycode_type.hpp"
#include "param_keypad.hpp"

namespace registry::parameter::keypad
{
    register_t g_register = {.byte = {0xff, 0xff, 0xff, 0xff}};

    void register_t::initialize(void)
    {
        value.click_ms = engine::Keycode::DEFAULT_CLICK_MS;
        value.push_ms = engine::Keycode::DEFAULT_PUSH_MS;
    }

    void register_t::deserialize(uint8_t const *const _space)
    {

        const uint8_t *ptr = _space;
        value.click_ms = deserialize_word(&ptr);
        value.push_ms = deserialize_word(&ptr);
    }

    void register_t::serialize(uint8_t **_ptr) const
    {

        serialize_word(value.click_ms, _ptr);
        serialize_word(value.push_ms, _ptr);
    }
}