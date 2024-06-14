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

//#include "backlight_settings.hpp"
#include "macros.hpp"
#include "param_backlight.hpp"

namespace engine
{
    namespace parameter
    {
        namespace backlight
        {
            register_t g_register = {.byte = {0xff,
                                              0xff, 0xff, 0xff,
                                              0xff, 0xff, 0xff,
                                              0xff, 0xff}};

            /**
                \brief initialize field with default values
            */
            void register_t::initialize(void)
            {
                //value.program = engine::BacklightSetting::DEFAULT_MODE;
                //value.left = engine::BacklightSetting::MOUNTED_BACKLIGHT_LEFT;
                //value.right = engine::BacklightSetting::MOUNTED_BACKLIGHT_RIGHT;
                //value.timeout = engine::BacklightSetting::DEFAULT_MOUNT_TIMEOUT;
            }

            /**
                \brief Deserialize parameter value
            */
            void register_t::deserialize(uint8_t const *const _space)
            {
                /* ATTENTION: NO CHECKS */
                const uint8_t *ptr = _space;
                value.program = static_cast<engine::backlight::PROGRAM>(*ptr++);
                value.left.rgb.r = *ptr++;
                value.left.rgb.g = *ptr++;
                value.left.rgb.b = *ptr++;
                value.right.rgb.r = *ptr++;
                value.right.rgb.g = *ptr++;
                value.right.rgb.b = *ptr++;
                value.timeout = deserialize_word(&ptr);
            }

            /**
                \brief Serialize parameter value
            */
            void register_t::serialize(uint8_t **_ptr) const
            {
                /* ATTENTION: NO CHECKS */
                *(*_ptr)++ = (uint8_t)value.program;
                *(*_ptr)++ = (uint8_t)value.left.rgb.r;
                *(*_ptr)++ = (uint8_t)value.left.rgb.g;
                *(*_ptr)++ = (uint8_t)value.left.rgb.b;
                *(*_ptr)++ = (uint8_t)value.right.rgb.r;
                *(*_ptr)++ = (uint8_t)value.right.rgb.g;
                *(*_ptr)++ = (uint8_t)value.right.rgb.b;
                serialize_word(value.timeout, _ptr);
            }
        }
    }
}