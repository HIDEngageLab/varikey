// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: Hardware rp2040 temperature functionality
// SPDX-FileType: SOURCE

#pragma once

#include <stdint.h>

#include "component_interface.hpp"

namespace platform::soc
{
	struct RP2040Temperature : public pulp::ComponentInterface
	{
		virtual ~RP2040Temperature() {}

		virtual void initialize(void);
		virtual void shutdown();

		const uint16_t get_raw_value(void) const;
		const float get_value(void) const;
	};
}
