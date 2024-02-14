/**
 * \file param_features.cpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

/**
    \brief Parameter "features"

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#include <stddef.h>
#include <stdlib.h>

#include "macros.hpp"
#include "param_features.hpp"
#include "parameter.hpp"

namespace registry
{
    namespace parameter
    {
        namespace features
        {

            register_t g_register = {0xff, 0xff};

            /**
                \brief Initialize features field with default values
            */
            extern void initialize(void)
            {
                g_register.features.autostart = ENABLE;
                g_register.features.display = ENABLE;
                g_register.features.keypad = ENABLE;
                g_register.features.wakeup = DISABLE;
            }

            /**
                \brief Set features level parameter value
            */
            extern void deserialize(uint8_t const *const _space)
            {
                /* ATTENTION: NO CHECKS */
                g_register.byte[0] = _space[0];
                g_register.byte[1] = _space[1];
            }

            /**
                \brief Serialize parameter value
            */
            extern void serialize(uint8_t *const _space)
            {
                /* ATTENTION: NO CHECKS */
                _space[0] = g_register.byte[0];
                _space[1] = g_register.byte[1];
            }
        }
    }
}