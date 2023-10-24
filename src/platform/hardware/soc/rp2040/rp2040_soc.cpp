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
        void RP2040::initialize()
        {
            uart_init(uart0, 115200);

            temperature.initialize();
            ticker.initialize();
            timestamp.initialize();
            watchdog.initialize();
            watchdog.start();
        }

        void RP2040::shutdown()
        {
            watchdog.shutdown();
            temperature.shutdown();
            ticker.shutdown();
            timestamp.shutdown();

            watchdog.reboot();
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