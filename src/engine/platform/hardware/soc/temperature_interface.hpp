/**
 * \file temperature_interface.hpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#ifndef __PLATFORM_TEMPERATURE_INTERFACE_HPP__
#define __PLATFORM_TEMPERATURE_INTERFACE_HPP__

namespace platform
{
	namespace driver
	{
		struct TemperatureInterface
		{
			virtual ~TemperatureInterface() {}
			virtual const int get() const = 0;
		};
	}
}

#endif /* __PLATFORM_TEMPERATURE_INTERFACE_HPP__ */
