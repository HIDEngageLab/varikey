/**
 * \file param_display.cpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

/**
    \brief Parameter "wheel"

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#include <stdlib.h>
#include <string.h>

#include "macros.hpp"
#include "param_display.hpp"

namespace registry
{
    namespace parameter
    {
        namespace display
        {

            register_t g_register = {0xff};

            /**
                \brief initialize field with default values
            */
            extern void initialize(void)
            {
                g_register.display.inverse = DISABLE;
                g_register.display.rotate = DISABLE;
                g_register.display.slides = ENABLE;
            }

            /**
                \brief Deserialize wheel parameter value
            */
            extern void deserialize(uint8_t const *const _space)
            {
                /* ATTENTION: NO CHECKS */
                g_register.byte[0] = _space[0];
            }

            /**
                \brief Serialize wheel parameter value
            */
            extern void serialize(uint8_t *const _space)
            {
                /* ATTENTION: NO CHECKS */
                _space[0] = g_register.byte[0];
            }
        }
    }
}