// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: Hardware rp2040 soc functionality
// SPDX-FileType: SOURCE

#pragma once

#include <stdint.h>

#include "board_defines.hpp"
#include "component_interface.hpp"
#include "rp2040_gpio.hpp"
#include "rp2040_stopwatch.hpp"
#include "rp2040_temperature.hpp"
#include "rp2040_ticker.hpp"
#include "rp2040_watchdog.hpp"

namespace platform::soc
{
    using DIRECTION = platform::board::DIRECTION;
    using IDENTIFIER = platform::board::IDENTIFIER;
    using VALUE = platform::board::VALUE;

    struct RP2040 : public pulp::ComponentInterface
    {
        RP2040();
        virtual ~RP2040() {}

        virtual void initialize();
        virtual void shutdown();

        const float get_temperature(void) const { return temperature.get_value(); }
        const uint16_t get_temperature_raw(void) const { return temperature.get_raw_value(); }

        void ticker_start(platform::board::ticker_handler_t _handler) { ticker.start(_handler); }
        void ticker_stop(void) { ticker.stop(); }

        const uint64_t get_stopwatch(void) const { return stopwatch.get_value(); }

        const DIRECTION get_gpio_direction(const IDENTIFIER) const;
        void set_gpio_direction(const IDENTIFIER, DIRECTION);
        void enable_gpio_event(platform::board::callback_t, const bool);
        const VALUE get_value(const IDENTIFIER);
        void set_value(const IDENTIFIER, const bool);

        void perform();

        void i2c_scan();

    protected:
        RP2040Temperature temperature;
        RP2040Ticker ticker;
        RP2040Stopwatch stopwatch;
        RP2040Watchdog watchdog;
        RP2040Gpio gpio;
    };
}
