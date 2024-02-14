/**
 * \file rp2040_soc.hpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#ifndef __PLATFORM_SOC_RP2040_HPP__
#define __PLATFORM_SOC_RP2040_HPP__

#include <stdint.h>

#include "component_interface.hpp"
#include "gpio_defines.hpp"
#include "rp2040_gpio.hpp"
#include "rp2040_stopwatch.hpp"
#include "rp2040_temperature.hpp"
#include "rp2040_ticker.hpp"
#include "rp2040_watchdog.hpp"

namespace platform
{
    namespace soc
    {
        struct RP2040 : public pulp::ComponentInterface
        {
            RP2040();
            virtual ~RP2040() {}

            virtual void initialize();
            virtual void shutdown();

            const float get_temperature(void) const { return temperature.get_value(); }
            const uint16_t get_temperature_raw(void) const { return temperature.get_raw_value(); }

            void ticker_start(ticker_handler_t _handler) { ticker.start(_handler); }
            void ticker_stop(void) { ticker.stop(); }

            const uint64_t get_stopwatch(void) const { return stopwatch.get_value(); }

            const driver::soc::gpio::DIRECTION get_gpio_direction(const driver::soc::gpio::IDENTIFIER) const;
            void set_gpio_direction(const driver::soc::gpio::IDENTIFIER, driver::soc::gpio::DIRECTION);
            void enable_gpio_event(driver::soc::gpio::callback_t, const bool);
            const driver::soc::gpio::VALUE get_value(const driver::soc::gpio::IDENTIFIER);
            void set_value(const driver::soc::gpio::IDENTIFIER, const bool);

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
}

#endif // __PLATFORM_SOC_RP2040_HPP__
