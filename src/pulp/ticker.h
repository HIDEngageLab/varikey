/**
 * \file ticker.h
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * @copyright Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 *
 */
/**
    \brief HIL ticker

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#ifndef __PULP_TICKER_H__
#define __PULP_TICKER_H__

#include <hardware/timer.h>

/**
    \name HCI interface

    If the delay is > 0 then this is the delay between the previous callback ending and the next starting.
    If the delay is negative (see below) then the next call to the callback will be exactly TICKER_DELAY ms
    after the start of the call to the last callback.
    Negative delay so means we will call timer callback, and call it again
    TICKER_DELAY ms later regardless of how long the callback took to execute.
*/
/* @{ */
#define TICKER_DELAY (-50)
/* @} */

extern void ticker_init(void);
extern void ticker_start(void);
extern void ticker_stop(void);

#endif /* __PULP_TICKER_H__ */
