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

        void BacklightWs2812::set_backlight(const engine::backlight::color_t &_left, const engine::backlight::color_t &_right)
        {
            ws2812_put_pixel(_left.rgb.r, _left.rgb.g, _left.rgb.b);
            ws2812_put_pixel((_left.rgb.r + _right.rgb.r) / 2, (_left.rgb.g + _right.rgb.g) / 2, (_left.rgb.b + _right.rgb.b) / 2);
            ws2812_put_pixel(_right.rgb.r, _right.rgb.g, _right.rgb.b);
        }
    }
}
