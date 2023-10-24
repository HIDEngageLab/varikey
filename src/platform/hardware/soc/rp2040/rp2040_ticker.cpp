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

#define USE_TEST_PIN

namespace platform
{
    namespace soc
    {
        struct repeating_timer timer;

        ticker_handler_t ticker_handler = nullptr;

        static bool timer_callback(struct repeating_timer *const _timer);

        /**
            \brief Init ticker.
        */
        void RP2040Ticker::initialize(void)
        {
#if defined(USE_TEST_PIN)
            /* ticker pin */
            gpio_init(platform::driver::SoC::DEBUG_PIN_4);
            gpio_set_dir(platform::driver::SoC::DEBUG_PIN_4, GPIO_OUT);

            /* application activity pin */
            gpio_init(platform::driver::SoC::DEBUG_PIN_3);
            gpio_set_dir(platform::driver::SoC::DEBUG_PIN_3, GPIO_OUT);
#endif
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
        void RP2040Ticker::start(ticker_handler_t _callback)
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
#if defined(USE_TEST_PIN)
            static int pin_state = 0;
            if (pin_state == 1)
            {
                pin_state = 0;
            }
            else
            {
                pin_state = 1;
            }
            gpio_put(platform::driver::SoC::DEBUG_PIN_4, pin_state);
#endif
            if (ticker_handler != nullptr)
            {
                static bool execution_flag = false;
                if (!execution_flag)
                {
                    execution_flag = true;

#if defined(USE_TEST_PIN)
                    gpio_put(platform::driver::SoC::DEBUG_PIN_3, 1);
#endif
                    ticker_handler();
#if defined(USE_TEST_PIN)
                    gpio_put(platform::driver::SoC::DEBUG_PIN_3, 0);
#endif
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
