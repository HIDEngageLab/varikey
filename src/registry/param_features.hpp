/**
 * \file param_features.hpp
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

#ifndef __PARAM_FEATURES_HPP__
#define __PARAM_FEATURES_HPP__

#include "macros.hpp"
#include "parameter.hpp"

namespace registry
{
    namespace parameter
    {
        namespace features
        {
            static const size_t SIZE = sizeof(uint16_t);
            /** \brief Features parameter */
            union register_t
            {
                uint8_t byte[SIZE];
                /** \brief Node features details */
                struct __attribute__((packed)) features_t
                {
                    ability_t autostart : 1;
                    ability_t display : 1;
                    ability_t keypad : 1;
                    ability_t wakeup : 1;
                    uint16_t reserved : 12;
                } features;
            };

            /** \brief Global parameter "features" */
            extern register_t g_register;

            extern void initialize(void);

            extern void deserialize(uint8_t const *const _space);
            extern void serialize(uint8_t *const _space);
        }
    }
}

#endif /* __PARAM_FEATURES_HPP__ */
