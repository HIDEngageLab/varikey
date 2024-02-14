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
            static const size_t SIZE = sizeof(engine::backlight::MODE) +
                                       sizeof(engine::backlight::color_t) +
                                       sizeof(engine::backlight::color_t) +
                                       sizeof(uint16_t);

            /**
                \brief Vref parameter

                Parameter with two float values for latitude and longitude.
            */
            union register_t
            {
                uint8_t byte[SIZE];
                /** \brief Node backlight details */
                struct __attribute__((packed)) backlight_t
                {
                    engine::backlight::MODE mode;
                    engine::backlight::color_t left;
                    engine::backlight::color_t right;
                    uint16_t timeout;
                } param_backlight;
            };

            extern register_t g_register;

            extern void initialize(void);

            extern void deserialize(uint8_t const *const _space);
            extern void serialize(uint8_t *const _space);
        }
    }
}

#endif /* __PARAM_BACKLIGHT_HPP__ */
