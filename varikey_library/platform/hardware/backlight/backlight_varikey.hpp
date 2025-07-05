// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: Hardware backlight varikey functionality
// SPDX-FileType: SOURCE

#pragma once

#include "backlight_ws2812.hpp"

namespace platform::hardware::backlight
{
    struct VarikeyPrototype : public BacklightWs2812
    {
        static const unsigned int BACKLIGHT_PIN = 22;

        static const backlight::INDEX first = backlight::FIRST;
        static const backlight::INDEX second = backlight::SECOND;
        static const backlight::INDEX third = backlight::THIRD;
    };
}
