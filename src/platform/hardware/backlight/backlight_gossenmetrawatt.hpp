/**
 * \file backlight_gossenmetrawatt.hpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#ifndef __PLATFORM_BACKLIGHT_GOSSENMETRAWATT_HPP__
#define __PLATFORM_BACKLIGHT_GOSSENMETRAWATT_HPP__

#include "backlight_ws2812.hpp"

namespace platform
{
    namespace hardware
    {
        namespace backlight
        {
            struct GMCI1 : public BacklightWs2812
            {
                static const unsigned int BACKLIGHT_PIN = 20;

                static const backlight::INDEX first = backlight::FIRST;
                static const backlight::INDEX second = backlight::THIRD;
                static const backlight::INDEX third = backlight::SECOND;
            };
        }
    }
}

#endif /* __PLATFORM_BACKLIGHT_GOSSENMETRAWATT_HPP__ */
