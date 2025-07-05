// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: Demo backlight configuration
// SPDX-FileType: SOURCE

#pragma once

#include "backlight_color.hpp"
#include "backlight_mode.hpp"

namespace engine::backlight
{
    struct BacklightDemo
    {
        static const PROGRAM DEFAULT_MODE = PROGRAM::TURBO;
        static const uint16_t DEFAULT_MOUNT_TIMEOUT = 15000;
        static constexpr Color MOUNTED_BACKLIGHT_LEFT = {.rgb = {.r = 0x00, .g = 0x0f, .b = 0x0f}};
        static constexpr Color MOUNTED_BACKLIGHT_RIGHT = {.rgb = {.r = 0x00, .g = 0x0e, .b = 0x1f}};
        static const uint16_t BLINK_ALERT_TIMEOUT = 250;
        static const uint16_t BLINK_MOUNT_TIMEOUT = 1000;
        static const uint16_t BLINK_SUSPEND_TIMEOUT = 2500;
    };
}
