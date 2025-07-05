// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: User parameter configuration
// SPDX-FileType: SOURCE

#pragma once

#include "parameter.hpp"

namespace registry::parameter::user
{
	static const size_t SIZE = 2;

	struct register_t
	{
		uint8_t value[SIZE];

		void initialize(void);

		void deserialize(uint8_t const *const);
		void serialize(uint8_t **) const;
	} __attribute__((packed));


	extern register_t g_register;
}
