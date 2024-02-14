/**
 * \file keymatrix_adp5585.cpp
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

#include "hid_report.hpp"
#include "keypad.hpp"

#include "adp5585.hpp"
#include "keymatrix_adp5585.hpp"
#include "keymatrix_adp5585_event.hpp"
#include "keymatrix_adp5585_handler_type.hpp"
#include "keymatrix_adp5585_type.hpp"

namespace platform
{
    namespace hardware
    {
        int called_state = 0;

        static platform::hardware::KeyHandler key_handler;
        static void keymatrix_callback(uint gpio, uint32_t events);

        void KeymatrixApd5585::initialize()
        {
            gpio_init(platform::hardware::Keymatrix::AD5585_RST);
            gpio_set_dir(platform::hardware::Keymatrix::AD5585_RST, GPIO_OUT);
            gpio_put(platform::hardware::Keymatrix::AD5585_RST, 0);

            gpio_set_function(platform::hardware::Keymatrix::PICO_I2C_SDA, GPIO_FUNC_I2C);
            gpio_set_function(platform::hardware::Keymatrix::PICO_I2C_SCL, GPIO_FUNC_I2C);

            gpio_pull_up(platform::hardware::Keymatrix::PICO_I2C_SDA);
            gpio_pull_up(platform::hardware::Keymatrix::PICO_I2C_SCL);

            i2c_init(i2c_default, platform::hardware::Keymatrix::PICO_I2C_SPEED);

            gpio_set_dir(platform::hardware::Keymatrix::AD5585_INT, GPIO_IN);
            gpio_set_pulls(platform::hardware::Keymatrix::AD5585_INT, true, false);
            gpio_set_irq_enabled_with_callback(platform::hardware::Keymatrix::AD5585_INT, GPIO_IRQ_EDGE_FALL, true, &keymatrix_callback);

            gpio_put(platform::hardware::Keymatrix::AD5585_RST, 1);
            platform_adp5585_init(platform::hardware::Keymatrix::AD5585_I2C_ADDRESS);
        }

        void KeymatrixApd5585::shutdown()
        {
            gpio_put(platform::hardware::Keymatrix::AD5585_RST, 0);
            gpio_put(platform::hardware::Keymatrix::AD5585_INT, 0);
            gpio_set_irq_enabled(platform::hardware::Keymatrix::AD5585_INT, GPIO_IRQ_EDGE_FALL, false);
            gpio_set_irq_enabled(platform::hardware::Keymatrix::AD5585_INT, GPIO_IRQ_EDGE_FALL, false);
        }

        bool KeymatrixApd5585::perform(void)
        {
            if (called_state > 0)
            {
                called_state--;
                while (platform::hardware::platform_adp5585_has_event())
                {
                    uint8_t state;
                    uint8_t identifier;
                    platform::hardware::platform_adp5585_get_event(&state, &identifier);

                    adp5585::event_t event = {
                        .identifier = static_cast<adp5585::event::IDENTIFIER>(identifier),
                        .state = static_cast<adp5585::event::STATE>(state),
                    };

                    key_handler.event_handler(event);
                }

                return true;
            }
            else
            {
                called_state = 0;
            }

            return false;
        }

        static void keymatrix_callback(uint gpio, uint32_t events)
        {
            (void)events;
            (void)gpio;
            called_state++;
        }
    }
}