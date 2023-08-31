/**
 * \file timestamp.c
 * \author Koch, Roman (koch.roman@googlemail.com)
 * \brief
 * \version 0.1
 * @date 2023-03-28
 *
 * @copyright Copyright (c) 2023
 *
 */
/**
	\brief Timestamp

	\internal
	\author Roman Koch, koch.roman@googlemail.com
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
