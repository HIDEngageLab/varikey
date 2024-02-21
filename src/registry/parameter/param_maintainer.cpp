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
            register_t g_register = {0};

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
                word = SETWORD(_space[0], _space[1]);
            }

            /**
                \brief Serialize  parameter value
            */
            void register_t::serialize(uint8_t *const _space) const
            {
                /* ATTENTION: NO CHECKS */
                _space[0] = HIBYTE(word);
                _space[1] = LOBYTE(word);
            }
        }
    }
}