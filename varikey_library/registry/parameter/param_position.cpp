// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: Position parameter implementation
// SPDX-FileType: SOURCE

#include <stdlib.h>
#include <string.h>

#include "identity_settings.hpp"
#include "macros.hpp"
#include "param_position.hpp"

namespace registry::parameter::position
{
    register_t g_register = {.byte = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff}};

    void register_t::initialize(void)
    {
        value.latitude = identity::Settings::MAGIC_LATITUDE;
        value.longitude = identity::Settings::MAGIC_LONGITUDE;
    }

    void register_t::deserialize(uint8_t const *const _space)
    {

        memcpy(byte, _space, sizeof(register_t));
    }

    void register_t::serialize(uint8_t **_ptr) const
    {

        memcpy(*_ptr, byte, sizeof(register_t));
        (*_ptr) += sizeof(register_t);
    }
}