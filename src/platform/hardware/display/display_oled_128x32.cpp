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

            // Make the SPI pins available to picotool
            bi_decl(bi_2pins_with_func(platform::hardware::Display::PICO_SPI_TX,
                                       platform::hardware::Display::PICO_SPI_SCK,
                                       GPIO_FUNC_SPI));

            // Chip select is active-low, so we'll initialise it to a driven-high state
            gpio_init(platform::hardware::Display::PICO_SPI_CS);
            gpio_set_dir(platform::hardware::Display::PICO_SPI_CS, GPIO_OUT);
            gpio_put(platform::hardware::Display::PICO_SPI_CS, 1);

            // Make the CS pin available to picotool
            bi_decl(bi_1pin_with_name(platform::hardware::Display::PICO_SPI_CS, "SPI CS"));

            gpio_init(platform::hardware::Display::DISPLAY_RESET);
            gpio_set_dir(platform::hardware::Display::DISPLAY_RESET, GPIO_OUT);
            gpio_put(platform::hardware::Display::DISPLAY_RESET, 1);

            gpio_init(platform::hardware::Display::DISPLAY_CMD_SEL);
            gpio_set_dir(platform::hardware::Display::DISPLAY_CMD_SEL, GPIO_OUT);
            gpio_put(platform::hardware::Display::DISPLAY_CMD_SEL, 0);

            platform_ssd1306_init(platform::hardware::Display::DISPLAY_CMD_SEL);
            platform_ssd1306_clean();
        }

        void DisplayOLED128x32::shutdown()
        {
            gpio_put(platform::hardware::Display::DISPLAY_RESET, 1);
            platform_ssd1306_clean();
        }
    }
}
