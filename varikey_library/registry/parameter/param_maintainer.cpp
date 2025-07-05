// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: Maintainer parameter implementation
// SPDX-FileType: SOURCE

#include <stddef.h>
#include <stdlib.h>

#include "identity_settings.hpp"
#include "macros.hpp"
#include "param_maintainer.hpp"
#include "parameter.hpp"

namespace registry::parameter::maintainer
{
    register_t g_register = {.byte = {0x00, 0x00}};

    void register_t::initialize(void)
    {
        value.identifier = identity::Settings::IDENTIFIER_DEFAULT;
        value.hardware = identity::Settings::HW_REVISION_DEFAULT;
        value.protocol = identity::Settings::FW_REVISION_DEFAULT;
    }

    void register_t::deserialize(uint8_t const *const _space)
    {

        const uint8_t *ptr = _space;
        word = deserialize_word(&ptr);
    }

    void register_t::serialize(uint8_t **_ptr) const
    {

        serialize_word(static_cast<const uint16_t>(word), _ptr);
    }
}