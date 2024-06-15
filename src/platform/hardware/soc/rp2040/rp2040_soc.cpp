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
        }

        void RP2040::reboot()
        {
            watchdog.reboot();
        }

        void RP2040::bootsel()
        {
            watchdog.bootsel();
        }

        const DIRECTION RP2040::get_gpio_direction(const IDENTIFIER _identifier) const
        {
            DIRECTION direction = DIRECTION::UNDEFINED;
            switch (_identifier)
            {
            case IDENTIFIER::GPIO0:
                direction = gpio.get_direction(IDENTIFIER::GPIO0);
                break;
            case IDENTIFIER::GPIO1:
                direction = gpio.get_direction(IDENTIFIER::GPIO1);
                break;
            case IDENTIFIER::GPIO2:
                direction = gpio.get_direction(IDENTIFIER::GPIO2);
                break;
            case IDENTIFIER::GPIO3:
                direction = gpio.get_direction(IDENTIFIER::GPIO3);
                break;
            default:
                break;
            }
            return direction;
        }

        void RP2040::set_gpio_direction(const IDENTIFIER _identifier,
                                        DIRECTION _direction)
        {
            auto set_direction = [&](const IDENTIFIER _identifier)
            {
                if (_direction == DIRECTION::INPUT)
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
            case IDENTIFIER::GPIO0:
                set_direction(IDENTIFIER::GPIO0);
                break;
            case IDENTIFIER::GPIO1:
                set_direction(IDENTIFIER::GPIO1);
                break;
            case IDENTIFIER::GPIO2:
                set_direction(IDENTIFIER::GPIO2);
                break;
            case IDENTIFIER::GPIO3:
                set_direction(IDENTIFIER::GPIO3);
                break;
            default:
                break;
            }
        }

        void RP2040::enable_gpio_event(platform::board::callback_t _callback,
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

        const VALUE RP2040::get_value(const IDENTIFIER _identifier)
        {
            auto get_value = [&](const IDENTIFIER _identifier) -> VALUE
            {
                VALUE value = VALUE::UNDEFINED;
                DIRECTION direction = gpio.get_direction(_identifier);
                if (direction != DIRECTION::UNDEFINED)
                {
                    value = gpio.get_value(_identifier);
                }
                return value;
            };

            VALUE value = VALUE::UNDEFINED;
            switch (_identifier)
            {
            case IDENTIFIER::GPIO0:
                return get_value(IDENTIFIER::GPIO0);
                break;
            case IDENTIFIER::GPIO1:
                return get_value(IDENTIFIER::GPIO1);
                break;
            case IDENTIFIER::GPIO2:
                return get_value(IDENTIFIER::GPIO2);
                break;
            case IDENTIFIER::GPIO3:
                return get_value(IDENTIFIER::GPIO3);
                break;
            default:
                break;
            }
            return value;
        }

        void RP2040::set_value(const IDENTIFIER _identifier, const bool _value)
        {
            auto set_value = [&](const IDENTIFIER _identifier) -> void
            {
                DIRECTION direction = gpio.get_direction(_identifier);
                if (direction == DIRECTION::OUTPUT)
                {
                    if (_value)
                        gpio.set_value(_identifier, platform::soc::VALUE::HIGH);
                    else
                        gpio.set_value(_identifier, platform::soc::VALUE::LOW);
                }
            };

            set_value(_identifier);
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