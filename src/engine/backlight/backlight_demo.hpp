/**
 * \file backlight_demo.hpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#ifndef __ENGINE_BACKLIGHT_DEMO_HPP__
#define __ENGINE_BACKLIGHT_DEMO_HPP__

#include "backlight_color.hpp"
#include "backlight_mode.hpp"

namespace engine
{
    namespace backlight
    {
        struct BacklightDemo
        {
            static const MODE DEFAULT_MODE = MODE::TURBO;
            static const uint16_t DEFAULT_MOUNT_TIMEOUT = 15000;
            static constexpr backlight::color_t MOUNTED_BACKLIGHT_LEFT = {.rgb = {.r = 0x00, .g = 0x0f, .b = 0x0f}};
            static constexpr backlight::color_t MOUNTED_BACKLIGHT_RIGHT = {.rgb = {.r = 0x00, .g = 0x0e, .b = 0x1f}};
        };

    }
}

#define EMBEDDED_KEYBOARD

#endif // __ENGINE_BACKLIGHT_DEMO_HPP__
