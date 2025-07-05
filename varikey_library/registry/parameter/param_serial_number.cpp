// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: Serial number parameter implementation
// SPDX-FileType: SOURCE

#include <stdlib.h>
#include <string.h>

#include "macros.hpp"
#include "param_serial_number.hpp"
#include "parameter.hpp"
#include "random.hpp"

namespace registry::parameter::serial_number
{
    uint32_t g_unique_key = INVALID_VALUE;
    register_t g_register = {.value = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff}};

    void register_t::initialize(void)
    {
        chunk_t chunk = {value, SIZE};
        random_create_sequence(&chunk);
    }

    void register_t::deserialize(uint8_t const *const _space)
    {

        memcpy(value, _space, SIZE);
    }

    void register_t::serialize(uint8_t **_ptr) const
    {

        memcpy(*_ptr, value, SIZE);
        (*_ptr) += SIZE;
    }
}