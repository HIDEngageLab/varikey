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
            void register_t::initialize(void)
            {
                value.mode = engine::BacklightSetting::DEFAULT_MODE;
                value.left = engine::BacklightSetting::MOUNTED_BACKLIGHT_LEFT;
                value.right = engine::BacklightSetting::MOUNTED_BACKLIGHT_RIGHT;
                value.timeout = engine::BacklightSetting::DEFAULT_MOUNT_TIMEOUT;
            }

            /**
                \brief Deserialize parameter value
            */
            void register_t::deserialize(uint8_t const *const _space)
            {
                /* ATTENTION: NO CHECKS */
                memcpy(byte, _space, sizeof(register_t));
            }

            /**
                \brief Serialize parameter value
            */
            void register_t::serialize(uint8_t *const _space) const
            {
                /* ATTENTION: NO CHECKS */
                memcpy(_space, byte, sizeof(register_t));
            }
        }
    }
}