/**
 * \file backlight_10bwdb.hpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#ifndef __ENGINE_BACKLIGHT_10BWDB_HPP__
#define __ENGINE_BACKLIGHT_10BWDB_HPP__

#include "backlight_color.hpp"
#include "backlight_mode.hpp"

namespace engine
{
    namespace backlight
    {
        struct Backlight10BWDB
        {
            static const MODE DEFAULT_MODE = MODE::TURBO;
            static const uint64_t DEFAULT_MOUNT_TIMEOUT = 15000;
            static constexpr backlight::color_t MOUNTED_BACKLIGHT_LEFT = {.rgb = {.r = 0x00, .g = 0x0f, .b = 0x00}};
            static constexpr backlight::color_t MOUNTED_BACKLIGHT_RIGHT = {.rgb = {.r = 0x00, .g = 0x0e, .b = 0x00}};
            static const uint16_t BLINK_ALERT_TIMEOUT = 250;
            static const uint16_t BLINK_MOUNT_TIMEOUT = 1000;
            static const uint16_t BLINK_SUSPEND_TIMEOUT = 2500;
        };
    }
}

#endif // __ENGINE_BACKLIGHT_10BWDB_HPP__
