// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: Features parameter implementation
// SPDX-FileType: SOURCE

#include <stddef.h>
#include <stdlib.h>

#include "macros.hpp"
#include "param_features.hpp"
#include "parameter.hpp"

namespace registry::parameter::features
{
    register_t g_register = {.byte = {0xff, 0xff}};

    void register_t::initialize(void)
    {
        value.autostart = ENABLE;
        value.display = ENABLE;
        value.keypad = ENABLE;
        value.wakeup = DISABLE;
    }

    void register_t::deserialize(uint8_t const *const _space)
    {

        byte[0] = _space[0];
        byte[1] = _space[1];
    }

    void register_t::serialize(uint8_t **_ptr) const
    {

        *(*_ptr)++ = byte[0];
        *(*_ptr)++ = byte[1];
    }
}