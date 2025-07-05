// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: Mapping parameter implementation
// SPDX-FileType: SOURCE

#include <stdlib.h>
#include <string.h>

#include "chunk.h"
#include "macros.hpp"
#include "param_mapping.hpp"
#include "parameter.hpp"

namespace registry::parameter::mapping
{
    register_t g_register = {.byte = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                      0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                      0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                      0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                      0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                      0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff}};

    void item_t::deserialize(uint8_t const *const _space)
    {
        memcpy(byte, _space, sizeof(item_t));
    }

    void item_t::serialize(uint8_t **_ptr) const
    {
        memcpy(*_ptr, byte, sizeof(item_t));
        (*_ptr) += sizeof(item_t);
    }

    void register_t::initialize(void) {}

    void register_t::deserialize(uint8_t const *const _space)
    {

        memcpy(byte, _space, sizeof(keycode_t) * SIZE);
    }

    void register_t::serialize(uint8_t **_ptr) const
    {

        memcpy(*_ptr, byte, sizeof(keycode_t) * SIZE);
        (*_ptr) += sizeof(keycode_t) * SIZE;
    }
}