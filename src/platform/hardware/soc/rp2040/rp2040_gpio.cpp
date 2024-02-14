/**
 * \file rp2040_gpio.cpp
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

/**
    \brief Handle internal gpio sensor

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#include <hardware/gpio.h>
#include <pico/stdlib.h>

#include "rp2040_gpio.hpp"
#include "soc_type.hpp"

namespace platform
{
    namespace soc
    {
        driver::soc::gpio::callback_t gpio_handler = nullptr;

        typedef enum
        {
            UNDEFINED,
            ENABLED
        } status_t;

        static status_t status = UNDEFINED;

        void gpio_callback(uint _gpio, uint32_t _events)
        {
            if (gpio_handler == nullptr)
                return;

            uint8_t identifier = 0xff;
            if (_gpio == platform::driver::SoC::DEBUG_PIN_1)
            {
                identifier = static_cast<uint8_t>(driver::soc::gpio::IDENTIFIER::GPIO0);
            }
            else if (_gpio == platform::driver::SoC::DEBUG_PIN_2)
            {
                identifier = static_cast<uint8_t>(driver::soc::gpio::IDENTIFIER::GPIO1);
            }
            else if (_gpio == platform::driver::SoC::DEBUG_PIN_3)
            {
                identifier = static_cast<uint8_t>(driver::soc::gpio::IDENTIFIER::GPIO2);
            }
            else if (_gpio == platform::driver::SoC::DEBUG_PIN_4)
            {
                identifier = static_cast<uint8_t>(driver::soc::gpio::IDENTIFIER::GPIO3);
            }

            if (_events & 0x01)
            {
                /* low level */
                gpio_handler(identifier, false);
            }
            else if (_events & 0x02)
            {
                /* high level */
                gpio_handler(identifier, true);
            }
            else if (_events & 0x04)
            {
                /* fall edge */
                gpio_handler(identifier, false);
            }
            else if (_events & 0x08)
            {
                /* rise edge */
                gpio_handler(identifier, true);
            }
        }

        /**
         * \brief Initialize ADC and internal gpio sensor
         */
        void RP2040Gpio::initialize(void)
        {
            assert(status == UNDEFINED);
            status = ENABLED;

            gpio_init(platform::driver::SoC::DEBUG_PIN_1);
            gpio_init(platform::driver::SoC::DEBUG_PIN_2);
            gpio_init(platform::driver::SoC::DEBUG_PIN_3);
            gpio_init(platform::driver::SoC::DEBUG_PIN_4);

            gpio_set_dir(platform::driver::SoC::DEBUG_PIN_1, GPIO_OUT);
            gpio_set_dir(platform::driver::SoC::DEBUG_PIN_2, GPIO_OUT);
            gpio_set_dir(platform::driver::SoC::DEBUG_PIN_3, GPIO_OUT);
            gpio_set_dir(platform::driver::SoC::DEBUG_PIN_4, GPIO_OUT);
        }

        void RP2040Gpio::shutdown()
        {
            assert(status == ENABLED);
            status = UNDEFINED;

            /* todo: restore default state */
        }

        void RP2040Gpio::enable_event(driver::soc::gpio::callback_t _callback)
        {
            assert(status == ENABLED);

            gpio_handler = _callback;
            gpio_set_irq_enabled_with_callback(platform::driver::SoC::DEBUG_PIN_1, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, &gpio_callback);
            gpio_set_irq_enabled_with_callback(platform::driver::SoC::DEBUG_PIN_2, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, &gpio_callback);
            gpio_set_irq_enabled_with_callback(platform::driver::SoC::DEBUG_PIN_3, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, &gpio_callback);
            gpio_set_irq_enabled_with_callback(platform::driver::SoC::DEBUG_PIN_4, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, &gpio_callback);
        }

        void RP2040Gpio::disable_event(void)
        {
            assert(status == ENABLED);

            gpio_set_irq_enabled(platform::driver::SoC::DEBUG_PIN_1, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, false);
            gpio_set_irq_enabled(platform::driver::SoC::DEBUG_PIN_2, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, false);
            gpio_set_irq_enabled(platform::driver::SoC::DEBUG_PIN_3, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, false);
            gpio_set_irq_enabled(platform::driver::SoC::DEBUG_PIN_4, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, false);
            gpio_handler = nullptr;
        }

        const driver::soc::gpio::DIRECTION RP2040Gpio::get_direction(const driver::soc::gpio::IDENTIFIER _identifier) const
        {
            driver::soc::gpio::DIRECTION direction = driver::soc::gpio::DIRECTION::UNDEFINED;
            switch (_identifier)
            {
            case driver::soc::gpio::IDENTIFIER::GPIO0:
                direction = gpio_get_dir(platform::driver::SoC::DEBUG_PIN_1) == GPIO_OUT ? driver::soc::gpio::DIRECTION::OUTPUT : driver::soc::gpio::DIRECTION::INPUT;
                break;
            case driver::soc::gpio::IDENTIFIER::GPIO1:
                direction = gpio_get_dir(platform::driver::SoC::DEBUG_PIN_2) == GPIO_OUT ? driver::soc::gpio::DIRECTION::OUTPUT : driver::soc::gpio::DIRECTION::INPUT;
                break;
            case driver::soc::gpio::IDENTIFIER::GPIO2:
                direction = gpio_get_dir(platform::driver::SoC::DEBUG_PIN_3) == GPIO_OUT ? driver::soc::gpio::DIRECTION::OUTPUT : driver::soc::gpio::DIRECTION::INPUT;
                break;
            case driver::soc::gpio::IDENTIFIER::GPIO3:
                direction = gpio_get_dir(platform::driver::SoC::DEBUG_PIN_4) == GPIO_OUT ? driver::soc::gpio::DIRECTION::OUTPUT : driver::soc::gpio::DIRECTION::INPUT;
                break;
            default:
                break;
            }
            return direction;
        }

        const void RP2040Gpio::set_direction(const driver::soc::gpio::IDENTIFIER _identifier, const driver::soc::gpio::DIRECTION _direction)
        {
            switch (_identifier)
            {
            case driver::soc::gpio::IDENTIFIER::GPIO0:
                gpio_set_dir(platform::driver::SoC::DEBUG_PIN_1, _direction == driver::soc::gpio::DIRECTION::INPUT ? GPIO_IN : GPIO_OUT);
                break;
            case driver::soc::gpio::IDENTIFIER::GPIO1:
                gpio_set_dir(platform::driver::SoC::DEBUG_PIN_2, _direction == driver::soc::gpio::DIRECTION::INPUT ? GPIO_IN : GPIO_OUT);
                break;
            case driver::soc::gpio::IDENTIFIER::GPIO2:
                gpio_set_dir(platform::driver::SoC::DEBUG_PIN_3, _direction == driver::soc::gpio::DIRECTION::INPUT ? GPIO_IN : GPIO_OUT);
                break;
            case driver::soc::gpio::IDENTIFIER::GPIO3:
                gpio_set_dir(platform::driver::SoC::DEBUG_PIN_4, _direction == driver::soc::gpio::DIRECTION::INPUT ? GPIO_IN : GPIO_OUT);
                break;
            default:
                break;
            }
        }

        const void RP2040Gpio::set_pulls(const driver::soc::gpio::IDENTIFIER _identifier,
                                                   const bool _up, const bool _down)
        {
            switch (_identifier)
            {
            case driver::soc::gpio::IDENTIFIER::GPIO0:
                gpio_set_pulls(platform::driver::SoC::DEBUG_PIN_1, _up, _down);
                break;
            case driver::soc::gpio::IDENTIFIER::GPIO1:
                gpio_set_pulls(platform::driver::SoC::DEBUG_PIN_2, _up, _down);
                break;
            case driver::soc::gpio::IDENTIFIER::GPIO2:
                gpio_set_pulls(platform::driver::SoC::DEBUG_PIN_3, _up, _down);
                break;
            case driver::soc::gpio::IDENTIFIER::GPIO3:
                gpio_set_pulls(platform::driver::SoC::DEBUG_PIN_4, _up, _down);
                break;
            default:
                break;
            }
        }

        const driver::soc::gpio::VALUE RP2040Gpio::get_value(const driver::soc::gpio::IDENTIFIER _identifier) const
        {
            driver::soc::gpio::VALUE value = driver::soc::gpio::VALUE::UNDEFINED;
            switch (_identifier)
            {
            case driver::soc::gpio::IDENTIFIER::GPIO0:
                value = (gpio_get(platform::driver::SoC::DEBUG_PIN_1) == 0) ? driver::soc::gpio::VALUE::LOW : driver::soc::gpio::VALUE::HIGH;
                break;
            case driver::soc::gpio::IDENTIFIER::GPIO1:
                value = (gpio_get(platform::driver::SoC::DEBUG_PIN_2) == 0) ? driver::soc::gpio::VALUE::LOW : driver::soc::gpio::VALUE::HIGH;
                break;
            case driver::soc::gpio::IDENTIFIER::GPIO2:
                value = (gpio_get(platform::driver::SoC::DEBUG_PIN_3) == 0) ? driver::soc::gpio::VALUE::LOW : driver::soc::gpio::VALUE::HIGH;
                break;
            case driver::soc::gpio::IDENTIFIER::GPIO3:
                value = (gpio_get(platform::driver::SoC::DEBUG_PIN_4) == 0) ? driver::soc::gpio::VALUE::LOW : driver::soc::gpio::VALUE::HIGH;
                break;
            default:
                break;
            }
            return value;
        }

        const void RP2040Gpio::set_value(const driver::soc::gpio::IDENTIFIER _identifier, const driver::soc::gpio::VALUE _value) const
        {
            switch (_identifier)
            {
            case driver::soc::gpio::IDENTIFIER::GPIO0:
                gpio_put(platform::driver::SoC::DEBUG_PIN_1, _value == driver::soc::gpio::VALUE::LOW ? true : false);
                break;
            case driver::soc::gpio::IDENTIFIER::GPIO1:
                gpio_put(platform::driver::SoC::DEBUG_PIN_2, _value == driver::soc::gpio::VALUE::LOW ? true : false);
                break;
            case driver::soc::gpio::IDENTIFIER::GPIO2:
                gpio_put(platform::driver::SoC::DEBUG_PIN_3, _value == driver::soc::gpio::VALUE::LOW ? true : false);
                break;
            case driver::soc::gpio::IDENTIFIER::GPIO3:
                gpio_put(platform::driver::SoC::DEBUG_PIN_4, _value == driver::soc::gpio::VALUE::LOW ? true : false);
                break;
            default:
                break;
            }
        }
    }
}
