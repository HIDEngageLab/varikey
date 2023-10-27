/**
 * \file keypad_adp5585.cpp
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

#include "keypad.hpp"
#include "keypad_event.hpp"

#include "adp5585.hpp"
#include "keypad_adp5585.hpp"
#include "keypad_adp5585_event.hpp"
#include "keypad_type.hpp"

namespace platform
{
    namespace hardware
    {
        int called_state = 0;

        static void keypad_callback(uint gpio, uint32_t events);

        void KeypadApd5585::initialize()
        {
            gpio_init(platform::hardware::Keypad::AD5585_RST);
            gpio_set_dir(platform::hardware::Keypad::AD5585_RST, GPIO_OUT);
            gpio_put(platform::hardware::Keypad::AD5585_RST, 1);

            gpio_set_function(platform::hardware::Keypad::PICO_I2C_SDA, GPIO_FUNC_I2C);
            gpio_set_function(platform::hardware::Keypad::PICO_I2C_SCL, GPIO_FUNC_I2C);

            gpio_pull_up(platform::hardware::Keypad::PICO_I2C_SDA);
            gpio_pull_up(platform::hardware::Keypad::PICO_I2C_SCL);

            i2c_init(i2c_default, platform::hardware::Keypad::PICO_I2C_SPEED);

            gpio_set_dir(platform::hardware::Keypad::AD5585_INT, GPIO_IN);
            gpio_set_pulls(platform::hardware::Keypad::AD5585_INT, true, false);
            gpio_set_irq_enabled_with_callback(platform::hardware::Keypad::AD5585_INT, GPIO_IRQ_EDGE_FALL, true, &keypad_callback);

            gpio_put(platform::hardware::Keypad::AD5585_RST, 1);
            platform_adp5585_init(platform::hardware::Keypad::AD5585_I2C_ADDRESS);
        }

        void KeypadApd5585::shutdown()
        {
            gpio_put(platform::hardware::Keypad::AD5585_RST, 0);
            gpio_put(platform::hardware::Keypad::AD5585_INT, 0);
            gpio_set_irq_enabled(platform::hardware::Keypad::AD5585_INT, GPIO_IRQ_EDGE_FALL, false);
            gpio_set_irq_enabled(platform::hardware::Keypad::AD5585_INT, GPIO_IRQ_EDGE_FALL, false);
        }

        bool KeypadApd5585::perform(void)
        {
            if (called_state > 0)
            {
                called_state--;
                while (platform::hardware::platform_adp5585_has_event())
                {
                    uint8_t state;
                    uint8_t identifier;
                    platform::hardware::platform_adp5585_get_event(&state, &identifier);

                    engine::keypad::event::STATE event_state = engine::keypad::event::STATE::UNDEFINED;
                    switch (static_cast<adp5585::EVENT_STATE>(state))
                    {
                    case adp5585::EVENT_STATE::PRESS:
                        event_state = engine::keypad::event::STATE::PRESS;
                        break;

                    case adp5585::EVENT_STATE::RELEASE:
                        event_state = engine::keypad::event::STATE::RELEASE;
                        break;

                    default:
                        break;
                    }

                    engine::keypad::event::IDENTIFIER event_identifier = engine::keypad::event::IDENTIFIER::UNDEFINED;
                    switch (static_cast<adp5585::EVENT_IDENTIFIER>(identifier))
                    {

                        /*
                        KEYPAD_R0_C0 = 1,
                            KEYPAD_R1_C0 = 6,
                            KEYPAD_R2_C0 = 11,
                            KEYPAD_R3_C0 = 16,
                            KEYPAD_R4_C0 = 21,
                            KEYPAD_R0_C1 = 2,
                            KEYPAD_R1_C1 = 7,
                            KEYPAD_R2_C1 = 12,
                            KEYPAD_R3_C1 = 17,
                            KEYPAD_R4_C1 = 22,
                            KEYPAD_A = 46,
                            KEYPAD_B = 47,
                            KEYPAD_C = 45,
                        */

                    case adp5585::EVENT_IDENTIFIER::UNDEFINED:
                        break;
                    case adp5585::EVENT_IDENTIFIER::R0_C0:
                        event_identifier = engine::keypad::event::IDENTIFIER::KEY_1;
                        break;
                    case adp5585::EVENT_IDENTIFIER::R0_C1:
                        event_identifier = engine::keypad::event::IDENTIFIER::KEY_6;
                        break;
                    case adp5585::EVENT_IDENTIFIER::R0_C2:
                        break;
                    case adp5585::EVENT_IDENTIFIER::R0_C3:
                        break;
                    case adp5585::EVENT_IDENTIFIER::R0_C4:
                        break;
                    case adp5585::EVENT_IDENTIFIER::R1_C0:
                        event_identifier = engine::keypad::event::IDENTIFIER::KEY_2;
                        break;
                    case adp5585::EVENT_IDENTIFIER::R1_C1:
                        event_identifier = engine::keypad::event::IDENTIFIER::KEY_7;
                        break;
                    case adp5585::EVENT_IDENTIFIER::R1_C2:
                        break;
                    case adp5585::EVENT_IDENTIFIER::R1_C3:
                        break;
                    case adp5585::EVENT_IDENTIFIER::R1_C4:
                        break;
                    case adp5585::EVENT_IDENTIFIER::R2_C0:
                        event_identifier = engine::keypad::event::IDENTIFIER::KEY_3;
                        break;
                    case adp5585::EVENT_IDENTIFIER::R2_C1:
                        event_identifier = engine::keypad::event::IDENTIFIER::KEY_8;
                        break;
                    case adp5585::EVENT_IDENTIFIER::R2_C2:
                        break;
                    case adp5585::EVENT_IDENTIFIER::R2_C3:
                        break;
                    case adp5585::EVENT_IDENTIFIER::R2_C4:
                        break;
                    case adp5585::EVENT_IDENTIFIER::R3_C0:
                        event_identifier = engine::keypad::event::IDENTIFIER::KEY_4;
                        break;
                    case adp5585::EVENT_IDENTIFIER::R3_C1:
                        event_identifier = engine::keypad::event::IDENTIFIER::KEY_9;
                        break;
                    case adp5585::EVENT_IDENTIFIER::R3_C2:
                        break;
                    case adp5585::EVENT_IDENTIFIER::R3_C3:
                        break;
                    case adp5585::EVENT_IDENTIFIER::R3_C4:
                        break;
                    case adp5585::EVENT_IDENTIFIER::R4_C0:
                        event_identifier = engine::keypad::event::IDENTIFIER::KEY_5;
                        break;
                    case adp5585::EVENT_IDENTIFIER::R4_C1:
                        event_identifier = engine::keypad::event::IDENTIFIER::KEY_10;
                        break;
                    case adp5585::EVENT_IDENTIFIER::R4_C2:
                        break;
                    case adp5585::EVENT_IDENTIFIER::R4_C3:
                        break;
                    case adp5585::EVENT_IDENTIFIER::R4_C4:
                        break;
                    case adp5585::EVENT_IDENTIFIER::R5_C0:
                        break;
                    case adp5585::EVENT_IDENTIFIER::R5_C1:
                        break;
                    case adp5585::EVENT_IDENTIFIER::R5_C2:
                        break;
                    case adp5585::EVENT_IDENTIFIER::R5_C3:
                        break;
                    case adp5585::EVENT_IDENTIFIER::R5_C4:
                        break;
                    case adp5585::EVENT_IDENTIFIER::R0_GND:
                        event_identifier = engine::keypad::event::IDENTIFIER::KEY_1;
                        break;
                    case adp5585::EVENT_IDENTIFIER::R1_GND:
                        event_identifier = engine::keypad::event::IDENTIFIER::KEY_2;
                        break;
                    case adp5585::EVENT_IDENTIFIER::R2_GND:
                        event_identifier = engine::keypad::event::IDENTIFIER::KEY_3;
                        break;
                    case adp5585::EVENT_IDENTIFIER::R3_GND:
                        event_identifier = engine::keypad::event::IDENTIFIER::KEY_4;
                        break;
                    case adp5585::EVENT_IDENTIFIER::R4_GND:
                        event_identifier = engine::keypad::event::IDENTIFIER::KEY_5;
                        break;
                    case adp5585::EVENT_IDENTIFIER::R5_GND:
                        break;
                    case adp5585::EVENT_IDENTIFIER::R0_GPI_1:
                        break;
                    case adp5585::EVENT_IDENTIFIER::R1_GPI_2:
                        break;
                    case adp5585::EVENT_IDENTIFIER::R2_GPI_3:
                        break;
                    case adp5585::EVENT_IDENTIFIER::R3_GPI_4:
                        break;
                    case adp5585::EVENT_IDENTIFIER::R4_GPI_5:
                        break;
                    case adp5585::EVENT_IDENTIFIER::R5_GPI_6:
                        break;
                    case adp5585::EVENT_IDENTIFIER::C0_GPI_7:
                        break;
                    case adp5585::EVENT_IDENTIFIER::C1_GPI_8:
                        break;
                    case adp5585::EVENT_IDENTIFIER::C2_GPI_9:
                        event_identifier = engine::keypad::event::IDENTIFIER::WHEEL_PRESS;
                        break;
                    case adp5585::EVENT_IDENTIFIER::C3_GPI_10:
                        event_identifier = engine::keypad::event::IDENTIFIER::WHEEL_LEFT;
                        break;
                    case adp5585::EVENT_IDENTIFIER::C4_GPI_11:
                        event_identifier = engine::keypad::event::IDENTIFIER::WHEEL_RIGHT;
                        break;
                    case adp5585::EVENT_IDENTIFIER::LOGIC:
                        break;
                    default:
                        break;
                    }

                    engine::keypad::event_t keypad_event = {
                        event_state,
                        event_identifier,
                    };
                    keypad_handle_event(keypad_event);
                }

                return true;
            }
            else
            {
                called_state = 0;
            }

            return false;
        }

        static void keypad_callback(uint gpio, uint32_t events)
        {
            (void)events;
            (void)gpio;
            called_state++;
        }

    }
}