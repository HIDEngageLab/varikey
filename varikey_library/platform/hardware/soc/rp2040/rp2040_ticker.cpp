// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: Hardware rp2040 ticker functionality
// SPDX-FileType: SOURCE

#include <cstdio>
#include <pico/stdlib.h>
#include <pico/time.h>

#include "macros.hpp"
#include "rp2040_ticker.hpp"
#include "soc_type.hpp"

namespace platform::soc
{
    struct repeating_timer timer;

    platform::board::ticker_handler_t ticker_handler = nullptr;

    static bool timer_callback(struct repeating_timer *const _timer);

    void RP2040Ticker::initialize(void)
    {
    }

    void RP2040Ticker::shutdown(void)
    {
    }

    void RP2040Ticker::delay_ms(uint32_t value)
    {
        sleep_ms(value);
    }

    void RP2040Ticker::start(platform::board::ticker_handler_t _callback)
    {
        ticker_handler = _callback;
        add_repeating_timer_ms(TICKER_DELAY,
                               platform::soc::timer_callback, NULL,
                               &platform::soc::timer);
    }

    void RP2040Ticker::stop(void)
    {
        cancel_repeating_timer(&platform::soc::timer);
    }

    static bool timer_callback(struct repeating_timer *const _timer)
    {
        if (ticker_handler != nullptr)
        {
            static bool execution_flag = false;
            if (!execution_flag)
            {
                execution_flag = true;
                ticker_handler();
                execution_flag = false;
            }
            else
            {
                printf("drop ticker handler execution\n");
            }
        }
        return true;
    }
}
