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

            static const size_t SIZE = sizeof(MODE) +
                                       sizeof(color_t) +
                                       sizeof(color_t) +
                                       sizeof(uint16_t);

            /**
                \brief Vref parameter

                Backlight default configuration.
            */
            union register_t
            {
                uint8_t byte[SIZE];
                /** \brief Node backlight details */
                struct __attribute__((packed)) backlight_t
                {
                    MODE mode;
                    color_t left;
                    color_t right;
                    uint16_t timeout;
                } value;

                void initialize(void);

                void deserialize(uint8_t const *const);
                void serialize(uint8_t **) const;
            };

            extern register_t g_register;
        }
    }
}

#endif /* __PARAM_BACKLIGHT_HPP__ */
