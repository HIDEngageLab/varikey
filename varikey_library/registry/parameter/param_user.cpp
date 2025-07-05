// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: User parameter implementation
// SPDX-FileType: SOURCE

#include <stddef.h>
#include <stdlib.h>

#include "macros.hpp"
#include "param_user.hpp"
#include "parameter.hpp"

namespace registry::parameter::user
{
    register_t g_register = {.value = {0xff, 0xff}};

    void register_t::initialize()
    {
        value[0] = 0xff;
        value[1] = 0xff;
    }

    void register_t::deserialize(uint8_t const *const _space)
    {

        value[0] = _space[0];
        value[1] = _space[1];
    }

    void register_t::serialize(uint8_t **_ptr) const
    {

        *(*_ptr)++ = value[0];
        *(*_ptr)++ = value[1];
    }
}