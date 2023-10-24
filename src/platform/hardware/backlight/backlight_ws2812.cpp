/**
 * \file backlight_ws2812.cpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#include <pico/assert.h>
#include <pico/time.h>

#include "backlight_ws2812.hpp"
#include "ws2812.hpp"

namespace platform
{
    namespace hardware
    {
        void BacklightWs2812::initialize()
        {
            ws2812_init();

            ws2812_put_pixel(0, 0, 0);
            ws2812_put_pixel(0, 0, 0);
            ws2812_put_pixel(0, 0, 0);
            sleep_ms(500);
        }

        void BacklightWs2812::shutdown()
        {
            ws2812_put_pixel(0, 0, 0);
            ws2812_put_pixel(0, 0, 0);
            ws2812_put_pixel(0, 0, 0);
            sleep_ms(500);
        }

        void BacklightWs2812::put_value(const color_t &_value)
        {
            ws2812_put_pixel(_value.rgb.r, _value.rgb.g, _value.rgb.b);
        }
    }
}
