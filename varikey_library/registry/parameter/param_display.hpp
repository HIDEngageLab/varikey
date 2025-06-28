/**
 * \file param_display.hpp
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

#ifndef __PARAM_DISPLAY_HPP__
#define __PARAM_DISPLAY_HPP__

#include "macros.hpp"
#include "parameter.hpp"

namespace registry
{
    namespace parameter
    {
        namespace display
        {
            /** \brief Node wheel details */
            struct display_t
            {
                ability_t rotate : 1;
                ability_t inverse : 1;
                ability_t slides : 1;
                uint8_t reserved : 5;
            } __attribute__((packed));

            static const size_t SIZE = sizeof(display_t);

            /**
                \brief Display parameter
            */
            union register_t
            {
                uint8_t byte[SIZE];
                display_t value;

                void initialize(void);

                void deserialize(uint8_t const *const);
                void serialize(uint8_t **) const;
            } __attribute__((packed));

            extern register_t g_register;
        }
    }
}

#endif /* __PARAM_DISPLAY_HPP__ */
