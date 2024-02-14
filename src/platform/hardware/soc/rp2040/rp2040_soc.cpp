/**
 * \file rp2040_soc.cpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#include <stdint.h>

#include <hardware/gpio.h>
#include <hardware/i2c.h>
#include <hardware/spi.h>
#include <pico/assert.h>
#include <pico/binary_info.h>
#include <pico/stdlib.h>

#include "chunk.h"
#include "rp2040_soc.hpp"

namespace platform
{
    namespace soc
    {
        static absolute_time_t time_reference;

        RP2040::RP2040() : stopwatch(time_reference) {}

        void RP2040::initialize()
        {
            gpio.initialize();
            temperature.initialize();
            ticker.initialize();
            stopwatch.initialize();
            watchdog.initialize();
            watchdog.start();
        }

        void RP2040::shutdown()
        {
            watchdog.shutdown();
            gpio.shutdown();
            temperature.shutdown();
            ticker.shutdown();
            stopwatch.shutdown();

            watchdog.reboot();
        }

        const driver::soc::gpio::DIRECTION RP2040::get_gpio_direction(const driver::soc::gpio::IDENTIFIER _identifier) const
        {
            driver::soc::gpio::DIRECTION direction = driver::soc::gpio::DIRECTION::UNDEFINED;
            switch (_identifier)
            {
            case driver::soc::gpio::IDENTIFIER::GPIO0:
                direction = gpio.get_direction(platform::driver::soc::gpio::IDENTIFIER::GPIO0);
                break;
            case driver::soc::gpio::IDENTIFIER::GPIO1:
                direction = gpio.get_direction(platform::driver::soc::gpio::IDENTIFIER::GPIO1);
                break;
            case driver::soc::gpio::IDENTIFIER::GPIO2:
                direction = gpio.get_direction(platform::driver::soc::gpio::IDENTIFIER::GPIO2);
                break;
            case driver::soc::gpio::IDENTIFIER::GPIO3:
                direction = gpio.get_direction(platform::driver::soc::gpio::IDENTIFIER::GPIO3);
                break;
            default:
                break;
            }
            return direction;
        }

        void RP2040::set_gpio_direction(const driver::soc::gpio::IDENTIFIER _identifier,
                                        driver::soc::gpio::DIRECTION _direction)
        {
            auto set_direction = [&](const platform::driver::soc::gpio::IDENTIFIER _identifier)
            {
                if (_direction == driver::soc::gpio::DIRECTION::INPUT)
                {
                    gpio.set_pulls(_identifier, true, false);
                }
                else
                {
                    gpio.set_pulls(_identifier, false, false);
                }
                gpio.set_direction(_identifier, _direction);
            };

            switch (_identifier)
            {
            case driver::soc::gpio::IDENTIFIER::GPIO0:
                set_direction(platform::driver::soc::gpio::IDENTIFIER::GPIO0);
                break;
            case driver::soc::gpio::IDENTIFIER::GPIO1:
                set_direction(platform::driver::soc::gpio::IDENTIFIER::GPIO1);
                break;
            case driver::soc::gpio::IDENTIFIER::GPIO2:
                set_direction(platform::driver::soc::gpio::IDENTIFIER::GPIO2);
                break;
            case driver::soc::gpio::IDENTIFIER::GPIO3:
                set_direction(platform::driver::soc::gpio::IDENTIFIER::GPIO3);
                break;
            default:
                break;
            }
        }

        void RP2040::enable_gpio_event(driver::soc::gpio::callback_t _callback,
                                       const bool _value)
        {
            if (_value)
            {
                gpio.enable_event(_callback);
            }
            else
            {
                gpio.disable_event();
            }
        }

        const driver::soc::gpio::VALUE RP2040::get_value(const driver::soc::gpio::IDENTIFIER _identifier)
        {

            auto set_direction = [&](const platform::driver::soc::gpio::IDENTIFIER _identifier) -> driver::soc::gpio::VALUE
            {
                driver::soc::gpio::VALUE value = driver::soc::gpio::VALUE::UNDEFINED;
                driver::soc::gpio::DIRECTION direction = gpio.get_direction(_identifier);
                if (direction != driver::soc::gpio::DIRECTION::UNDEFINED)
                {
                    value = gpio.get_value(_identifier);
                }
                return value;
            };

            driver::soc::gpio::VALUE value = driver::soc::gpio::VALUE::UNDEFINED;
            switch (_identifier)
            {
            case driver::soc::gpio::IDENTIFIER::GPIO0:
                break;
            case driver::soc::gpio::IDENTIFIER::GPIO1:
                break;
            case driver::soc::gpio::IDENTIFIER::GPIO2:
                break;
            case driver::soc::gpio::IDENTIFIER::GPIO3:
                break;
            default:
                break;
            }
            return value;
        }

        void RP2040::set_value(const driver::soc::gpio::IDENTIFIER _identifier, const bool _value)
        {
            switch (_identifier)
            {
            case driver::soc::gpio::IDENTIFIER::GPIO0:
                break;
            case driver::soc::gpio::IDENTIFIER::GPIO1:
                break;
            case driver::soc::gpio::IDENTIFIER::GPIO2:
                break;
            case driver::soc::gpio::IDENTIFIER::GPIO3:
                break;
            default:
                break;
            }
        }

        void RP2040::perform()
        {
            watchdog.update();
        }

        static bool scan_over_i2c(chunk_t *const _result);

        void RP2040::i2c_scan(void)
        {
            uint8_t devices_space[3];
            chunk_t devices = {devices_space, 3};
            while (!scan_over_i2c(&devices))
                ;
        }

        static bool scan_over_i2c(chunk_t *const _result)
        {
            bool found_flag = false;
            uint8_t result_address = 0;
            for (size_t i = 0; i < _result->size; ++i)
            {
                _result->space[i] = 0;
            }

            for (uint8_t addr = 0; addr < (1 << 7); ++addr)
            {
                // Skip over any reserved addresses.
                int ret;
                if ((addr & 0x78) == 0 || (addr & 0x78) == 0x78)
                {
                    ret = PICO_ERROR_GENERIC;
                }
                else
                {
                    uint8_t buffer;
                    ret = i2c_read_blocking(i2c_default, addr, &buffer, 1, false);
                    if (ret > 0)
                    {
                        found_flag = true;
                        if (result_address < _result->size)
                        {
                            _result->space[result_address++] = addr;
                        }
                    }
                }
            }

            return found_flag;
        }
    }
}