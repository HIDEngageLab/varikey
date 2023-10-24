/**
 * \file rp2040_watchdog.cpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#include <hardware/watchdog.h>
#include <pico/time.h>

#include "rp2040_watchdog.hpp"

namespace platform
{
    namespace soc
    {

        void RP2040Watchdog::start()
        {
            watchdog_enable(5000, true);
        }

        void RP2040Watchdog::update()
        {
            watchdog_update();
        }

        void RP2040Watchdog::reboot()
        {
            sleep_ms(200);
            watchdog_enable(0, false);
            while (true)
                ;
        }
    }
}
