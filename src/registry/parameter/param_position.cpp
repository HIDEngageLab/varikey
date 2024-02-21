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

#include "identity_settings.hpp"
#include "macros.hpp"
#include "param_position.hpp"

namespace registry
{
    namespace parameter
    {
        namespace position
        {
            register_t g_register = {{0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff}};

            /**
                \brief initialize field with default values

                magic values ;)
            */
            void register_t::initialize(void)
            {
                value.latitude = identity::Settings::MAGIC_LATITUDE;
                value.longitude = identity::Settings::MAGIC_LONGITUDE;
            }

            /**
                \brief Deserialize position parameter value
            */
            void register_t::deserialize(uint8_t const *const _space)
            {
                /* ATTENTION: NO CHECKS */
                memcpy(byte, _space, sizeof(register_t));
            }

            /**
                \brief Serialize position parameter value
            */
            void register_t::serialize(uint8_t *const _space) const
            {
                /* ATTENTION: NO CHECKS */
                memcpy(_space, byte, sizeof(register_t));
            }
        }
    }
}