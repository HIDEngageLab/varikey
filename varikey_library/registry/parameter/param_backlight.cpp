// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: Backlight parameter implementation
// SPDX-FileType: SOURCE

#include <stdlib.h>
#include <string.h>

#include "backlight_settings.hpp"
#include "macros.hpp"
#include "param_backlight.hpp"

namespace registry::parameter::backlight
{
    register_t g_register = {.byte = {0xff,
                                      0xff, 0xff, 0xff,
                                      0xff, 0xff, 0xff,
                                      0xff, 0xff}};

    void register_t::initialize(void)
    {
        value.program = engine::backlight::Settings::DEFAULT_MODE;
        value.left = engine::backlight::Settings::MOUNTED_BACKLIGHT_LEFT;
        value.right = engine::backlight::Settings::MOUNTED_BACKLIGHT_RIGHT;
        value.timeout = engine::backlight::Settings::DEFAULT_MOUNT_TIMEOUT;
    }

    void register_t::deserialize(uint8_t const *const _space)
    {

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

    void register_t::serialize(uint8_t **_ptr) const
    {

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