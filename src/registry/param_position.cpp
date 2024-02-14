/**
 * \file param_position.cpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

/**
    \brief Parameter "position"

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#include <stdlib.h>
#include <string.h>

#include "macros.hpp"
#include "param_position.hpp"

namespace registry
{
    namespace parameter
    {
        namespace position
        {

            static constexpr float MAGIC_LATITUDE = 49.441607f;
            static constexpr float MAGIC_LONGITUDE = 11.053841f;

            register_t g_register = {{0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff}};

            /**
                \brief initialize field with default values

                magic values ;)
            */
            extern void initialize(void)
            {
                g_register.coordinates.latitude = MAGIC_LATITUDE;
                g_register.coordinates.longitude = MAGIC_LONGITUDE;
            }

            /**
                \brief Deserialize position parameter value
            */
            extern void deserialize(uint8_t const *const _space)
            {
                /* ATTENTION: NO CHECKS */
                memcpy(g_register.byte, _space, sizeof(register_t));
            }

            /**
                \brief Serialize position parameter value
            */
            extern void serialize(uint8_t *const _space)
            {
                /* ATTENTION: NO CHECKS */
                memcpy(_space, g_register.byte, sizeof(register_t));
            }
        }
    }
}