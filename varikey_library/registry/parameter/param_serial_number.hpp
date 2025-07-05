// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: Serial number parameter configuration
// SPDX-FileType: SOURCE

#pragma once

#include "parameter.hpp"

namespace registry::parameter::serial_number
{
	static const uint32_t INVALID_VALUE = 0xffffffff;
	static const size_t SIZE = 12;

	struct register_t
	{
		uint8_t value[SIZE];

		void initialize(void);

		void deserialize(uint8_t const *const);
		void serialize(uint8_t **) const;
	} __attribute__((packed));

	extern register_t g_register;

	extern uint32_t g_unique_key;
}
