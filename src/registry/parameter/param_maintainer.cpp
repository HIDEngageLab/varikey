/**
 * \file param_maintainer.cpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

/**
    \brief Parameter "maintainer"

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#include <stddef.h>
#include <stdlib.h>

#include "identity_settings.hpp"
#include "macros.hpp"
#include "param_maintainer.hpp"
#include "parameter.hpp"

namespace registry
{
    namespace parameter
    {
        namespace maintainer
        {
            register_t g_register = {.byte = {0x00, 0x00}};

            /**
                \brief Initialize field with default values
            */
            void register_t::initialize(void)
            {
                value.identifier = identity::Settings::IDENTIFIER_DEFAULT;
                value.hardware = identity::Settings::HW_REVISION_DEFAULT;
                value.protocol = identity::Settings::FW_REVISION_DEFAULT;
            }

            /**
                \brief Deserialize parameter value
            */
            void register_t::deserialize(uint8_t const *const _space)
            {
                /* ATTENTION: NO CHECKS */
                const uint8_t *ptr = _space;
                word = deserialize_word(&ptr);
            }

            /**
                \brief Serialize  parameter value
            */
            void register_t::serialize(uint8_t **_ptr) const
            {
                /* ATTENTION: NO CHECKS */
                serialize_word(static_cast<const uint16_t>(word), _ptr);
            }
        }
    }
}