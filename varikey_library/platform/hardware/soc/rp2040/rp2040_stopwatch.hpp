// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: Hardware rp2040 stopwatch functionality
// SPDX-FileType: SOURCE

#pragma once

#include <stdint.h>

#include <pico/time.h>

#include "component_interface.hpp"

namespace platform::soc
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
