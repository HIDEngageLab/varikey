/**
 * \file display_oled_128x32.cpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#include <hardware/gpio.h>
#include <hardware/i2c.h>
#include <hardware/spi.h>
#include <pico/assert.h>
#include <pico/binary_info.h>
#include <pico/stdlib.h>

#include "display_font.hpp"
#include "display_image.hpp"
#include "display_oled_128x32.hpp"
#include "display_type.hpp"
#include "ssd1306.hpp"

namespace platform
{
    namespace hardware
    {
        void DisplayOLED128x32::initialize()
        {
            spi_init(spi_default, platform::hardware::Display::PICO_SPI_SPEED);
            gpio_set_function(platform::hardware::Display::PICO_SPI_SCK, GPIO_FUNC_SPI);
            gpio_set_function(platform::hardware::Display::PICO_SPI_TX, GPIO_FUNC_SPI);

            // Chip select is active-low, so we'll initialise it to a driven-high state
            gpio_init(platform::hardware::Display::PICO_SPI_CS);
            gpio_set_dir(platform::hardware::Display::PICO_SPI_CS, GPIO_OUT);
            gpio_put(platform::hardware::Display::PICO_SPI_CS, 1);

            gpio_init(platform::hardware::Display::DISPLAY_RESET);
            gpio_set_dir(platform::hardware::Display::DISPLAY_RESET, GPIO_OUT);
            gpio_put(platform::hardware::Display::DISPLAY_RESET, 1);

            gpio_init(platform::hardware::Display::DISPLAY_CMD_SEL);
            gpio_set_dir(platform::hardware::Display::DISPLAY_CMD_SEL, GPIO_OUT);
            gpio_put(platform::hardware::Display::DISPLAY_CMD_SEL, 0);

            ssd1306::initialize(platform::hardware::Display::DISPLAY_CMD_SEL,
                                platform::hardware::Display::PICO_SPI_CS);
            ssd1306::clean();
        }

        void DisplayOLED128x32::shutdown()
        {
            gpio_put(platform::hardware::Display::DISPLAY_RESET, 1);
            ssd1306::clean();
        }

        void DisplayOLED128x32::symbol(uint8_t const line_start, uint8_t const line_end,
                                       uint8_t const column_start, uint8_t const column_end,
                                       uint8_t const *const data, size_t const len)
        {
            ssd1306::symbol(line_start, line_end,
                            column_start, column_end,
                            data, len);
        }

        void DisplayOLED128x32::clean()
        {
            platform::hardware::ssd1306::clean();
        }

        void DisplayOLED128x32::set_invert()
        {
            platform::hardware::ssd1306::set_inverse();
        }

        void DisplayOLED128x32::set_normal()
        {
            platform::hardware::ssd1306::set_normal();
        }
    }
}
