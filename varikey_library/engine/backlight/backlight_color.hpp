// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: Demo backlight configuration
// SPDX-FileType: SOURCE

#pragma once

#include "smartled_color.hpp"

namespace engine::backlight
{
    using Color = platform::hardware::smartled::Color;

    static const Color BLACK_COLOR{.rgb = {.r = 0, .g = 0, .b = 0}};
    static const Color ALERT_COLOR{.rgb = {.r = 0x3f, .g = 0, .b = 0}};
    static const Color SUSPEND_COLOR{.rgb = {.r = 0x1f, .g = 0x1f, .b = 0}};

    static const Color GLIMMER_COLOR{.rgb = {.r = 0x0a, .g = 0x0a, .b = 0x0a}};
}
