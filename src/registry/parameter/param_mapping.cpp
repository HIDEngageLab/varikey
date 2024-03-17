/**
 * \file param_mapping.cpp
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

#include "chunk.h"
#include "macros.hpp"
#include "param_mapping.hpp"
#include "parameter.hpp"

namespace registry
{
    namespace parameter
    {
        namespace mapping
        {
            register_t g_register = {.modifier = {0xff, 0xff, 0xff, 0xff, 0xff,
                                                  0xff, 0xff, 0xff, 0xff, 0xff,
                                                  0xff, 0xff, 0xff,
                                                  0xff, 0xff, 0xff,
                                                  0xff, 0xff, 0xff, 0xff,
                                                  0xff, 0xff, 0xff, 0xff},
                                     .value = {0xff, 0xff, 0xff, 0xff, 0xff,
                                               0xff, 0xff, 0xff, 0xff, 0xff,
                                               0xff, 0xff, 0xff,
                                               0xff, 0xff, 0xff,
                                               0xff, 0xff, 0xff, 0xff,
                                               0xff, 0xff, 0xff, 0xff}};

            /**
                \brief Initialize with default values
            */
            void register_t::initialize(void) {}

            /**
                \brief Deserialize parameter value from chunk
            */
            void register_t::deserialize(uint8_t const *const _space)
            {
                /* ATTENTION: NO CHECKS */
                memcpy(value, _space, SIZE);
            }

            /**
                \brief Serialize parameter value to chunk
            */
            void register_t::serialize(uint8_t **_ptr) const
            {
                /* ATTENTION: NO CHECKS */
                memcpy(*_ptr, value, SIZE);
                (*_ptr) += SIZE;
            }
        }
    }
}