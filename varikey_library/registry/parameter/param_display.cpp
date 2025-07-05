// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: Display parameter implementation
// SPDX-FileType: SOURCE

#include <stdlib.h>
#include <string.h>

#include "macros.hpp"
#include "param_display.hpp"

namespace registry::parameter::display
{

    register_t g_register = {.byte = {0xff}};

    void register_t::initialize(void)
    {
        value.inverse = DISABLE;
        value.rotate = DISABLE;
        value.slides = ENABLE;
    }

    void register_t::deserialize(uint8_t const *const _space)
    {

        byte[0] = _space[0];
    }

    void register_t::serialize(uint8_t **_ptr) const
    {

        *(*_ptr)++ = byte[0];
    }
}