// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: Hardware backlight GMCI functionality
// SPDX-FileType: SOURCE

#pragma once

#include "backlight_ws2812.hpp"

namespace platform::hardware::backlight
{
    struct GMCI1 : public BacklightWs2812
    {
        static const unsigned int BACKLIGHT_PIN = 20;

        static const backlight::INDEX first = backlight::FIRST;
        static const backlight::INDEX second = backlight::THIRD;
        static const backlight::INDEX third = backlight::SECOND;
    };
}
