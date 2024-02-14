/**
 * \file rp2040_stopwatch.hpp
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

#ifndef __PULP_STOPWATCH_HPP__
#define __PULP_STOPWATCH_HPP__

#include <stdint.h>

#include <pico/time.h>

#include "component_interface.hpp"

namespace platform
{
	namespace soc
	{
		struct RP2040Stopwatch : public pulp::ComponentInterface
		{
			RP2040Stopwatch(absolute_time_t &);
			virtual ~RP2040Stopwatch() {}

			virtual void initialize() {}
			virtual void shutdown() {}

			void restart(void);
			const uint64_t get_value(void) const;

		protected:
			absolute_time_t &time_reference;
		};
	}
}

#endif /* __PULP_STOPWATCH_HPP__ */
