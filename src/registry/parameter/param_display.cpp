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
                \brief Initialize field with default values
            */
            void register_t::initialize(void)
            {
                value.inverse = DISABLE;
                value.rotate = DISABLE;
                value.slides = ENABLE;
            }

            /**
                \brief Deserialize parameter value
            */
            void register_t::deserialize(uint8_t const *const _space)
            {
                /* ATTENTION: NO CHECKS */
                byte[0] = _space[0];
            }

            /**
                \brief Serialize parameter value
            */
            void register_t::serialize(uint8_t **_ptr) const
            {
                /* ATTENTION: NO CHECKS */
                *(*_ptr)++ = byte[0];
            }
        }
    }
}