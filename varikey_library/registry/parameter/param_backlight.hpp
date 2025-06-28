/**
 * \file param_backlight.hpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

/**
    \brief Parameter "backlight"

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#ifndef __PARAM_BACKLIGHT_HPP__
#define __PARAM_BACKLIGHT_HPP__

#include "backlight3.hpp"
#include "backlight_color.hpp"
#include "parameter.hpp"

namespace registry
{
    namespace parameter
    {
        namespace backlight
        {
            using namespace engine::backlight;

            /** \brief Node backlight details */
            struct backlight_t
            {
                PROGRAM program;
                Color left;
                Color right;
                uint16_t timeout;
            } __attribute__((packed));

            static const size_t SIZE = sizeof(backlight_t);

            /**
                \brief Vref parameter

                Backlight default configuration.
            */
            union register_t
            {
                uint8_t byte[SIZE];
                backlight_t value;

                void initialize(void);

                void deserialize(uint8_t const *const);
                void serialize(uint8_t **) const;
            } __attribute__((packed));

            extern register_t g_register;
        }
    }
}

#endif /* __PARAM_BACKLIGHT_HPP__ */
