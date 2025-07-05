// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: Hardware rp2040 gpio functionality
// SPDX-FileType: SOURCE

#include <hardware/gpio.h>
#include <pico/stdlib.h>

#include "rp2040_gpio.hpp"
#include "soc_type.hpp"

namespace platform::soc
{
    platform::board::callback_t gpio_handler = nullptr;

    typedef enum
    {
        UNDEFINED,
        ENABLED
    } status_t;

    static status_t status = UNDEFINED;

    void gpio_callback(uint _gpio, uint32_t _events)
    {
        static bool pin_state[4] = {false, false, false};

        if (gpio_handler == nullptr)
            return;

        uint8_t identifier = 0xff;
        if (_gpio == platform::driver::SoC::DEBUG_PIN_1)
        {
            identifier = static_cast<uint8_t>(IDENTIFIER::GPIO0);
        }
        else if (_gpio == platform::driver::SoC::DEBUG_PIN_2)
        {
            identifier = static_cast<uint8_t>(IDENTIFIER::GPIO1);
        }
        else if (_gpio == platform::driver::SoC::DEBUG_PIN_3)
        {
            identifier = static_cast<uint8_t>(IDENTIFIER::GPIO2);
        }
        else if (_gpio == platform::driver::SoC::DEBUG_PIN_4)
        {
            identifier = static_cast<uint8_t>(IDENTIFIER::GPIO3);
        }

        bool state_changed = false;
        if (_events & 0x01)
        {
        }
        else if (_events & 0x02)
        {
        }
        else if (_events & 0x04)
        {

            if (pin_state[identifier] == true)
            {
                state_changed = true;
                pin_state[identifier] = false;
            }
        }
        else if (_events & 0x08)
        {

            if (pin_state[identifier] == false)
            {
                state_changed = true;
                pin_state[identifier] = true;
            }
        }

        if (state_changed)
        {
            state_changed = false;
            gpio_handler(identifier, pin_state[identifier]);
        }
    }

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
    }

    void RP2040Gpio::enable_event(platform::board::callback_t _callback)
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

    const DIRECTION RP2040Gpio::get_direction(const IDENTIFIER _identifier) const
    {
        DIRECTION direction = DIRECTION::UNDEFINED;
        switch (_identifier)
        {
        case IDENTIFIER::GPIO0:
            direction = gpio_get_dir(platform::driver::SoC::DEBUG_PIN_1) == GPIO_OUT ? DIRECTION::OUTPUT : DIRECTION::INPUT;
            break;
        case IDENTIFIER::GPIO1:
            direction = gpio_get_dir(platform::driver::SoC::DEBUG_PIN_2) == GPIO_OUT ? DIRECTION::OUTPUT : DIRECTION::INPUT;
            break;
        case IDENTIFIER::GPIO2:
            direction = gpio_get_dir(platform::driver::SoC::DEBUG_PIN_3) == GPIO_OUT ? DIRECTION::OUTPUT : DIRECTION::INPUT;
            break;
        case IDENTIFIER::GPIO3:
            direction = gpio_get_dir(platform::driver::SoC::DEBUG_PIN_4) == GPIO_OUT ? DIRECTION::OUTPUT : DIRECTION::INPUT;
            break;
        default:
            break;
        }
        return direction;
    }

    const void RP2040Gpio::set_direction(const IDENTIFIER _identifier, const DIRECTION _direction)
    {
        switch (_identifier)
        {
        case IDENTIFIER::GPIO0:
            gpio_set_dir(platform::driver::SoC::DEBUG_PIN_1, _direction == DIRECTION::INPUT ? GPIO_IN : GPIO_OUT);
            break;
        case IDENTIFIER::GPIO1:
            gpio_set_dir(platform::driver::SoC::DEBUG_PIN_2, _direction == DIRECTION::INPUT ? GPIO_IN : GPIO_OUT);
            break;
        case IDENTIFIER::GPIO2:
            gpio_set_dir(platform::driver::SoC::DEBUG_PIN_3, _direction == DIRECTION::INPUT ? GPIO_IN : GPIO_OUT);
            break;
        case IDENTIFIER::GPIO3:
            gpio_set_dir(platform::driver::SoC::DEBUG_PIN_4, _direction == DIRECTION::INPUT ? GPIO_IN : GPIO_OUT);
            break;
        default:
            break;
        }
    }

    const void RP2040Gpio::set_pulls(const IDENTIFIER _identifier,
                                     const bool _up, const bool _down)
    {
        switch (_identifier)
        {
        case IDENTIFIER::GPIO0:
            gpio_set_pulls(platform::driver::SoC::DEBUG_PIN_1, _up, _down);
            break;
        case IDENTIFIER::GPIO1:
            gpio_set_pulls(platform::driver::SoC::DEBUG_PIN_2, _up, _down);
            break;
        case IDENTIFIER::GPIO2:
            gpio_set_pulls(platform::driver::SoC::DEBUG_PIN_3, _up, _down);
            break;
        case IDENTIFIER::GPIO3:
            gpio_set_pulls(platform::driver::SoC::DEBUG_PIN_4, _up, _down);
            break;
        default:
            break;
        }
    }

    const VALUE RP2040Gpio::get_value(const IDENTIFIER _identifier) const
    {
        VALUE value = VALUE::UNDEFINED;
        switch (_identifier)
        {
        case IDENTIFIER::GPIO0:
            value = (gpio_get(platform::driver::SoC::DEBUG_PIN_1) == 0) ? VALUE::LOW : VALUE::HIGH;
            break;
        case IDENTIFIER::GPIO1:
            value = (gpio_get(platform::driver::SoC::DEBUG_PIN_2) == 0) ? VALUE::LOW : VALUE::HIGH;
            break;
        case IDENTIFIER::GPIO2:
            value = (gpio_get(platform::driver::SoC::DEBUG_PIN_3) == 0) ? VALUE::LOW : VALUE::HIGH;
            break;
        case IDENTIFIER::GPIO3:
            value = (gpio_get(platform::driver::SoC::DEBUG_PIN_4) == 0) ? VALUE::LOW : VALUE::HIGH;
            break;
        default:
            break;
        }
        return value;
    }

    const void RP2040Gpio::set_value(const IDENTIFIER _identifier, const VALUE _value) const
    {
        switch (_identifier)
        {
        case IDENTIFIER::GPIO0:
            gpio_put(platform::driver::SoC::DEBUG_PIN_1, _value == VALUE::HIGH ? true : false);
            break;
        case IDENTIFIER::GPIO1:
            gpio_put(platform::driver::SoC::DEBUG_PIN_2, _value == VALUE::HIGH ? true : false);
            break;
        case IDENTIFIER::GPIO2:
            gpio_put(platform::driver::SoC::DEBUG_PIN_3, _value == VALUE::HIGH ? true : false);
            break;
        case IDENTIFIER::GPIO3:
            gpio_put(platform::driver::SoC::DEBUG_PIN_4, _value == VALUE::HIGH ? true : false);
            break;
        default:
            break;
        }
    }
}
