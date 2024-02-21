/**
 * \file param_position.hpp
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

/**
    \brief Parameter "position"

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#ifndef __PARAM_POSITION_HPP__
#define __PARAM_POSITION_HPP__

#include "parameter.hpp"

namespace registry
{
    namespace parameter
    {
        namespace position
        {
            static const size_t SIZE = sizeof(float) * 2;
            /**
                \brief Position parameter

                Parameter with two float values for latitude and longitude.
            */
            union register_t
            {
                uint8_t byte[SIZE];
                /** \brief Node position details */
                struct __attribute__((packed)) coordinates_t
                {
                    float latitude;
                    float longitude;
                } value;

                void initialize(void);

                void deserialize(uint8_t const *const _space);
                void serialize(uint8_t *const _space) const;
            };

            extern register_t g_register;

        }
    }
}

#endif /* __PARAM_POSITION_HPP__ */
