/**
 * \file param_backlight.cpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

/**
    \brief Parameter "vref"

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#include <stdlib.h>
#include <string.h>

#include "backlight_settings.hpp"
#include "macros.hpp"
#include "param_backlight.hpp"

namespace registry
{
    namespace parameter
    {
        namespace backlight
        {
            register_t g_register = {{0xff,
                                      0xff, 0xff, 0xff,
                                      0xff, 0xff, 0xff,
                                      0xff, 0xff}};

            /**
                \brief initialize field with default values
            */
            extern void initialize(void)
            {
                g_register.param_backlight.mode = engine::BacklightSetting::DEFAULT_MODE;
                g_register.param_backlight.left = engine::BacklightSetting::MOUNTED_BACKLIGHT_LEFT;
                g_register.param_backlight.right = engine::BacklightSetting::MOUNTED_BACKLIGHT_RIGHT;
                g_register.param_backlight.timeout = engine::BacklightSetting::DEFAULT_MOUNT_TIMEOUT;
            }

            /**
                \brief Deserialize vref parameter value
            */
            extern void deserialize(uint8_t const *const _space)
            {
                /* ATTENTION: NO CHECKS */
                memcpy(g_register.byte, _space, sizeof(register_t));
            }

            /**
                \brief Serialize vref parameter value
            */
            extern void serialize(uint8_t *const _space)
            {
                /* ATTENTION: NO CHECKS */
                memcpy(_space, g_register.byte, sizeof(register_t));
            }
        }
    }
}