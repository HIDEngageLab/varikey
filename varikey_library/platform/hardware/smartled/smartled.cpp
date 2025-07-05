// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: Hardware smartled ws2812 functionality
// SPDX-FileType: SOURCE

#include <cstdio>
#include <cstdlib>
#include <vector>

#include <hardware/clocks.h>
#include <hardware/pio.h>
#include <pico/assert.h>
#include <pico/stdlib.h>
#include <pico/time.h>

#include "macros.hpp"
#include "smartled.hpp"
#include "smartled_type.hpp"
#include "ws2812.pio.h"

namespace platform::hardware::smartled
{
    const float LUM_R = 1.400;
    const float LUM_G = 0.700;
    const float LUM_B = 0.400;

    const float LUM_R_FACTOR = 1.400;
    const float LUM_G_FACTOR = 0.700;
    const float LUM_B_FACTOR = 0.400;

    namespace
    {
        constexpr int sm0 = 0;
        constexpr int sm1 = 1;
    }

    void FrontChannel::initialize()
    {
        PIO pio = pio0;
        uint offset = pio_add_program(pio, &ws2812_program);
        ws2812_program_init(pio, sm0, offset, Frontlight::PIO_PIN, 800000, false);
        pio_sm_clear_fifos(pio, sm0);

        const Color colors[Frontlight::LED_COUNT] = {0};
        set_led_sequence<Frontlight::Mapper>(colors);
        sleep_ms(500);
    }

    void FrontChannel::shutdown()
    {
        const Color colors[Frontlight::LED_COUNT] = {0};
        set_led_sequence<Frontlight::Mapper>(colors);
        sleep_ms(500);
    }

    void FrontChannel::put_pixel(uint8_t r, uint8_t g, uint8_t b)
    {
        uint32_t color = ((uint32_t)(r) << 8) |
                         ((uint32_t)(g) << 16) |
                         (uint32_t)(b);
        pio_sm_put_blocking(pio0, sm0, color << 8u);
    }

    void BackChannel::initialize()
    {
        PIO pio = pio0;
        uint offset = pio_add_program(pio, &ws2812_program);
        ws2812_program_init(pio, sm1, offset, Backlight::PIO_PIN, 800000, false);
        pio_sm_clear_fifos(pio, sm1);

        const Color colors[Backlight::LED_COUNT] = {0};
        set_led_sequence<Backlight::Mapper>(colors);
        sleep_ms(500);
    }

    void BackChannel::shutdown()
    {
        const Color colors[Backlight::LED_COUNT] = {0};
        set_led_sequence<Backlight::Mapper>(colors);
        sleep_ms(500);
    }

    void BackChannel::put_pixel(uint8_t r, uint8_t g, uint8_t b)
    {
        uint32_t color = ((uint32_t)(r) << 8) |
                         ((uint32_t)(g) << 16) |
                         (uint32_t)(b);
        pio_sm_put_blocking(pio0, sm1, color << 8u);
    }
}
