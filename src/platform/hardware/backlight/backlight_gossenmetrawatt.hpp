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
        struct BacklightGossenmetrawatt : public BacklightWs2812
        {
            static const unsigned int BACKLIGHT_PIN = 20;
        };
    }
}

#endif /* __PLATFORM_BACKLIGHT_GOSSENMETRAWATT_HPP__ */
