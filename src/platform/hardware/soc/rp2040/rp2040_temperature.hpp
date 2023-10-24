/**
 * \file rp2040_temperature.hpp
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 *
 */

/**
	\brief Handle internal temperature sensor

	\internal
	\author Roman Koch, koch.roman@gmail.com
*/

#ifndef __PLATFORM_SOC_RP2040_TEMPERATURE_HPP__
#define __PLATFORM_SOC_RP2040_TEMPERATURE_HPP__

#include <stdint.h>

#include "component_interface.hpp"

namespace platform
{
	namespace soc
	{
		struct RP2040Temperature : public pulp::ComponentInterface
		{
			virtual ~RP2040Temperature() {}

			virtual void initialize(void);
			virtual void shutdown();

			uint16_t get_raw_value(void);
			float get_value(void);
		};
	}
}

#endif /* __PLATFORM_SOC_RP2040_TEMPERATURE_HPP__ */
