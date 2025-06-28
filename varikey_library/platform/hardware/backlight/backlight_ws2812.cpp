/**
 * \file backlight_ws2812.cpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#include <pico/assert.h>
#include <pico/time.h>

#include "backlight_type.hpp"
#include "backlight_ws2812.hpp"
#include "ws2812.hpp"

namespace platform
{
    namespace hardware
    {
        namespace backlight
        {
            inline void set_three_colors(const engine::backlight::Color &_left,
                                         const engine::backlight::Color &_median,
                                         const engine::backlight::Color &_right)
            {
                ws2812::put_pixel(_left.rgb.r, _left.rgb.g, _left.rgb.b);
                ws2812::put_pixel(_median.rgb.r, _median.rgb.g, _median.rgb.b);
                ws2812::put_pixel(_right.rgb.r, _right.rgb.g, _right.rgb.b);
            }

            template <backlight::INDEX, backlight::INDEX, backlight::INDEX>
            void set_led_sequence(const engine::backlight::Color &_first,
                                  const engine::backlight::Color &_second,
                                  const engine::backlight::Color &_third)
            {
            }
            template <>
            void set_led_sequence<backlight::INDEX::FIRST,
                                  backlight::INDEX::SECOND,
                                  backlight::INDEX::THIRD>(const engine::backlight::Color &_first,
                                                           const engine::backlight::Color &_second,
                                                           const engine::backlight::Color &_third)
            {
                set_three_colors(_first, _second, _third);
            }
            template <>
            void set_led_sequence<backlight::INDEX::FIRST,
                                  backlight::INDEX::THIRD,
                                  backlight::INDEX::SECOND>(const engine::backlight::Color &_first,
                                                            const engine::backlight::Color &_second,
                                                            const engine::backlight::Color &_third)
            {
                set_three_colors(_first, _third, _second);
            }
            template <>
            void set_led_sequence<backlight::INDEX::SECOND,
                                  backlight::INDEX::FIRST,
                                  backlight::INDEX::THIRD>(const engine::backlight::Color &_first,
                                                           const engine::backlight::Color &_second,
                                                           const engine::backlight::Color &_third)
            {
                set_three_colors(_second, _first, _third);
            }
            template <>
            void set_led_sequence<backlight::INDEX::SECOND,
                                  backlight::INDEX::THIRD,
                                  backlight::INDEX::FIRST>(const engine::backlight::Color &_first,
                                                           const engine::backlight::Color &_second,
                                                           const engine::backlight::Color &_third)
            {
                set_three_colors(_second, _third, _first);
            }
            template <>
            void set_led_sequence<backlight::INDEX::THIRD,
                                  backlight::INDEX::FIRST,
                                  backlight::INDEX::SECOND>(const engine::backlight::Color &_first,
                                                            const engine::backlight::Color &_second,
                                                            const engine::backlight::Color &_third)
            {
                set_three_colors(_third, _first, _second);
            }
            template <>
            void set_led_sequence<backlight::INDEX::THIRD,
                                  backlight::INDEX::SECOND,
                                  backlight::INDEX::FIRST>(const engine::backlight::Color &_first,
                                                           const engine::backlight::Color &_second,
                                                           const engine::backlight::Color &_third)
            {
                set_three_colors(_third, _second, _first);
            }

            void BacklightWs2812::initialize()
            {
                ws2812::init();

                ws2812::put_pixel(0, 0, 0);
                ws2812::put_pixel(0, 0, 0);
                ws2812::put_pixel(0, 0, 0);

                sleep_ms(500);
            }

            void BacklightWs2812::shutdown()
            {
                ws2812::put_pixel(0, 0, 0);
                ws2812::put_pixel(0, 0, 0);
                ws2812::put_pixel(0, 0, 0);

                sleep_ms(500);
            }

            void BacklightWs2812::set_backlight(const engine::backlight::Color &_left,
                                                const engine::backlight::Color &_right)
            {
                const engine::backlight::Color median{.rgb = {.r = static_cast<const uint8_t>((_left.rgb.r + _right.rgb.r) >> 1),
                                                              .g = static_cast<const uint8_t>((_left.rgb.g + _right.rgb.g) >> 1),
                                                              .b = static_cast<const uint8_t>((_left.rgb.b + _right.rgb.b) >> 1)}};

                set_led_sequence<Backlight::first, Backlight::second, Backlight::third>(_left, median, _right);
            }
        }
    }
}
