/**
 * \file param_serial_number.cpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

/**
    \brief Configuration parameter serial number

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#include <stdlib.h>
#include <string.h>

#include "macros.hpp"
#include "param_serial_number.hpp"
#include "parameter.hpp"
#include "random.hpp"

namespace registry
{
    namespace parameter
    {
        namespace serial_number
        {

            uint32_t g_unique_key = INVALID_VALUE;
            register_t g_register = {{0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff}};

            /**
                \brief Initialize with default values
            */
            void register_t::initialize(void)
            {
                chunk_t chunk = {value, SIZE};
                random_create_sequence(&chunk);
            }

            /**
                \brief Deserialize parameter value from chunk
            */
            void register_t::deserialize(uint8_t const *_space)
            {
                /* ATTENTION: NO CHECKS */
                memcpy(value, _space, SIZE);
            }

            /**
                \brief Serialize parameter value to chunk
            */
            void register_t::serialize(uint8_t *_space) const
            {
                /* ATTENTION: NO CHECKS */
                memcpy(_space, value, SIZE);
            }
        }
    }
}