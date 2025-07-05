// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: Hardware rp2040 watchdog functionality
// SPDX-FileType: SOURCE

#include <hardware/watchdog.h>
#include <pico/time.h>

#include "rp2040_watchdog.hpp"

namespace platform::soc
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
