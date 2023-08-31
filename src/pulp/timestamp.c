/**
 * \file timestamp.c
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * @copyright Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 *
 */
/**
	\brief Timestamp

	\internal
	\author Roman Koch, koch.roman@gmail.com
*/

#include <hardware/irq.h>
#include <hardware/timer.h>
#include <pico/stdlib.h>

#include "timestamp.h"

static absolute_time_t time_reference;

/**
	\brief Reset
 */
extern void timestamp_reset(void)
{
	time_reference = get_absolute_time();
}

/**
	\brief Time stamp

	\return uint64_t time value
 */
extern uint64_t timestamp(void)
{
	absolute_time_t absolute_time = get_absolute_time();

	if (to_us_since_boot(time_reference) == 0)
	{
		update_us_since_boot(&time_reference, to_us_since_boot(absolute_time));
		return 0;
	}
	return absolute_time_diff_us(time_reference, absolute_time);
}
