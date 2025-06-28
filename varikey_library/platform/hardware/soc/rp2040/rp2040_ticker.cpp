/**
 * \file rp2040_ticker.cpp
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

/**
    \brief Ticker

    Create a repeating timer that calls timer callback.

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#include <cstdio>
#include <pico/stdlib.h>
#include <pico/time.h>

#include "macros.hpp"
#include "rp2040_ticker.hpp"
#include "soc_type.hpp"

namespace platform
{
    namespace soc
    {
        struct repeating_timer timer;

        platform::board::ticker_handler_t ticker_handler = nullptr;

        static bool timer_callback(struct repeating_timer *const _timer);

        /**
            \brief Init ticker.
        */
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

        /**
            \brief Start a repeating timer that calls timer callback.

            If the delay is > 0 then this is the delay between the previous callback ending and the next starting.
            If the delay is negative (see below) then the next call to the callback will be exactly TICKER_DELAY ms
            after the start of the call to the last callback.
        */
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
}
