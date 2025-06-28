/**
 * \file backlight_varikey.hpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#ifndef __PLATFORM_BACKLIGHT_VARIKEY_HPP__
#define __PLATFORM_BACKLIGHT_VARIKEY_HPP__

#include "backlight_ws2812.hpp"

namespace platform
{
    namespace hardware
    {
        namespace backlight
        {
            struct VarikeyPrototype : public BacklightWs2812
            {
                static const unsigned int BACKLIGHT_PIN = 22;

                static const backlight::INDEX first = backlight::FIRST;
                static const backlight::INDEX second = backlight::SECOND;
                static const backlight::INDEX third = backlight::THIRD;
            };
        }
    }
}

#endif /* __PLATFORM_BACKLIGHT_VARIKEY_HPP__ */
