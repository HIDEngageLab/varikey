/**
 * \file engine_gpio.cpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#include "engine_gpio.hpp"
#include "board_assembly.hpp"
#include "engine_event_handler.hpp"

namespace engine
{
    namespace gpio
    {
        /**
         * \brief Module local GPIO interrupt handler
         *
         * \param _identifier
         * \param _level
         */
        void gpio_callback(uint8_t _identifier, bool _level)
        {
            IDENTIFIER identifier{IDENTIFIER::UNDEFINED};
            VALUE level = VALUE::UNDEFINED;
            switch (_identifier)
            {
            case 0:
                identifier = IDENTIFIER::GPIO0;
                break;
            case 1:
                identifier = IDENTIFIER::GPIO1;
                break;
            case 2:
                identifier = IDENTIFIER::GPIO2;
                break;
            case 3:
                identifier = IDENTIFIER::GPIO3;
                break;
            default:
                break;
            }
            if (_level)
            {
                level = VALUE::HIGH;
            }
            else
            {
                level = VALUE::LOW;
            }

            static uint64_t timestamp = platform::board::assembly.soc.get_stopwatch();
            const uint64_t current = platform::board::assembly.soc.get_stopwatch();
            uint64_t us_diff = current - timestamp;
            if (us_diff > engine::parameter::keypad::g_register.value.click_ms / 2 * 1000)
            {
                us_diff = 0;
                timestamp = platform::board::assembly.soc.get_stopwatch();
            }
            else
            {
                timestamp = current;
            }

            engine::handler::push_gpio_event(identifier, level,
                                             static_cast<const uint32_t>(us_diff & 0xffffffff));
        }

        extern void set_direction(const IDENTIFIER _identifier, DIRECTION _direction)
        {
            platform::board::assembly.soc.set_gpio_direction(_identifier, _direction);
        }

        extern const platform::board::DIRECTION get_direction(const IDENTIFIER _value)
        {
            return platform::board::assembly.soc.get_gpio_direction(_value);
        }

        extern void set_value(const IDENTIFIER _identifier, const bool _value)
        {
            platform::board::assembly.soc.set_value(_identifier, _value);
        }

        extern const platform::board::VALUE get_value(const IDENTIFIER _identifier)
        {
            return platform::board::assembly.soc.get_value(_identifier);
        }

        extern void enable_event(const bool _value)
        {
            platform::board::assembly.soc.enable_gpio_event(gpio_callback, _value);
        }
    }
}