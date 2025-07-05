// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: Hardware rp2040 gpio functionality
// SPDX-FileType: SOURCE

#pragma once

#include <stdint.h>

#include "board_defines.hpp"
#include "component_interface.hpp"

namespace platform::soc
{
	using IDENTIFIER = platform::board::IDENTIFIER;
	using DIRECTION = platform::board::DIRECTION;
	using VALUE = platform::board::VALUE;

	struct RP2040Gpio : public pulp::ComponentInterface
	{
		virtual ~RP2040Gpio() {}

		virtual void initialize(void);
		virtual void shutdown();

		void enable_event(platform::board::callback_t);
		void disable_event(void);

		const DIRECTION get_direction(const IDENTIFIER) const;
		const void set_direction(const IDENTIFIER, const DIRECTION);

		const void set_pulls(const IDENTIFIER, const bool, const bool);

		const VALUE get_value(const IDENTIFIER) const;
		const void set_value(const IDENTIFIER, const VALUE) const;
	};
}
