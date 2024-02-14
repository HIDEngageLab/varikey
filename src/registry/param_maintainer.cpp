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

#include "macros.hpp"
#include "param_maintainer.hpp"
#include "parameter.hpp"

namespace registry
{
    namespace parameter
    {
        namespace maintainer
        {
            static const uint16_t IDENTIFIER_DEFAULT = 0x00;
            static const uint16_t HW_REVISION_DEFAULT = 0;
            static const uint16_t FW_REVISION_DEFAULT = 0;

            register_t g_register = {0};

            /**
                \brief Initialize field with default values
            */
            extern void initialize(void)
            {
                g_register.maintainer.protocol = FW_REVISION_DEFAULT;
                g_register.maintainer.hardware = HW_REVISION_DEFAULT;
                g_register.maintainer.identifier = IDENTIFIER_DEFAULT;
            }

            /**
                \brief Set maintainer parameter value
            */
            extern void deserialize(uint8_t const *const _space)
            {
                /* ATTENTION: NO CHECKS */
                g_register.word = SETWORD(_space[0], _space[1]);
            }

            /**
                \brief Serialize maintainer parameter value
            */
            extern void serialize(uint8_t *const _space)
            {
                /* ATTENTION: NO CHECKS */
                _space[0] = HIBYTE(g_register.word);
                _space[1] = LOBYTE(g_register.word);
            }
        }
    }
}