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

#include <cstdint>

#include "macros.hpp"

namespace engine
{
    namespace parameter
    {
        namespace features
        {
            /** \brief Node features details */
            struct features_t
            {
                ability_t autostart : 1;
                ability_t display : 1;
                ability_t keypad : 1;
                ability_t wakeup : 1;
                uint16_t reserved : 12;
            } __attribute__((packed));

            static const size_t SIZE = sizeof(features_t);

            /** \brief Features parameter */
            union register_t
            {
                uint8_t byte[SIZE];
                features_t value;

                void initialize(void);

                void deserialize(uint8_t const *const);
                void serialize(uint8_t **) const;
            } __attribute__((packed));

            /** \brief Global parameter "features" */
            extern register_t g_register;
        }
    }
}

#endif /* __PARAM_FEATURES_HPP__ */
