/**
 * \file rp2040_gpio.hpp
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 *
 */
/**
	\brief Handle gpio

	\internal
	\author Roman Koch, koch.roman@gmail.com
*/

#ifndef __PLATFORM_SOC_RP2040_GPIO_HPP__
#define __PLATFORM_SOC_RP2040_GPIO_HPP__

#include <stdint.h>

#include "component_interface.hpp"
#include "gpio_defines.hpp"

namespace platform
{
	namespace soc
	{
		struct RP2040Gpio : public pulp::ComponentInterface
		{
			virtual ~RP2040Gpio() {}

			virtual void initialize(void);
			virtual void shutdown();

			void enable_event(driver::soc::gpio::callback_t);
			void disable_event(void);

			const driver::soc::gpio::DIRECTION get_direction(const driver::soc::gpio::IDENTIFIER) const;
			const void set_direction(const driver::soc::gpio::IDENTIFIER, const driver::soc::gpio::DIRECTION);

			const void set_pulls(const driver::soc::gpio::IDENTIFIER, const bool, const bool);

			const driver::soc::gpio::VALUE get_value(const driver::soc::gpio::IDENTIFIER) const;
			const void set_value(const driver::soc::gpio::IDENTIFIER, const driver::soc::gpio::VALUE) const;
		};
	}
}

#endif /* __PLATFORM_SOC_RP2040_GPIO_HPP__ */
