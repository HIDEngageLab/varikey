/**
 * \file ticker.c
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 *
 */
/**
    \brief Ticker

    Create a repeating timer that calls timer callback.

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#include <pico/stdlib.h>
#include <pico/time.h>

#include "engine.h"
#include "macros.h"
#include "ticker.h"

#define USE_TEST_PIN

#if defined(USE_TEST_PIN)
const uint TEST_PIN = 19;
#endif

struct repeating_timer timer;

static bool timer_callback(struct repeating_timer *const _timer);

/**
    \brief Init ticker.
*/
extern void ticker_init(void)
{
#if defined(USE_TEST_PIN)
    gpio_init(TEST_PIN);
    gpio_set_dir(TEST_PIN, GPIO_OUT);
#endif
}

/**
    \brief Start a repeating timer that calls timer callback.
*/
extern void ticker_start(void)
{
    add_repeating_timer_ms(TICKER_DELAY, timer_callback, NULL, &timer);
}

extern void ticker_stop(void)
{
    cancel_repeating_timer(&timer);
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
    gpio_put(TEST_PIN, pin_state);
#endif
    engine_tick();
    return true;
}
