/**
 * \file rp2040_stopwatch.cpp
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

/**
	\brief Stopwatch

	\internal
	\author Roman Koch, koch.roman@gmail.com
*/

#include <hardware/irq.h>
#include <hardware/timer.h>
#include <pico/stdlib.h>

#include "rp2040_stopwatch.hpp"

namespace platform
{
	namespace soc
	{
		/**
		 * \brief Construct a new RP2040Stopwatch::RP2040Stopwatch object
		 *
		 */
		RP2040Stopwatch::RP2040Stopwatch(absolute_time_t &_reference) : time_reference(_reference)
		{
			time_reference = get_absolute_time();
		}

		/**
			\brief Reset
		 */
		void RP2040Stopwatch::restart(void)
		{
			time_reference = get_absolute_time();
		}

		/**
			\brief Time stamp

			\return uint64_t time value
		 */
		const uint64_t RP2040Stopwatch::get_value(void) const
		{
			absolute_time_t absolute_time = get_absolute_time();

			if (to_us_since_boot(time_reference) == 0)
			{
				update_us_since_boot(&time_reference, to_us_since_boot(absolute_time));
				return 0;
			}
			return absolute_time_diff_us(time_reference, absolute_time);
		}
	}
}
