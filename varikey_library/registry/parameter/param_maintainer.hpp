// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: Maintainer parameter configuration
// SPDX-FileType: SOURCE

#pragma once

#include "parameter.hpp"

namespace registry::parameter::maintainer
{
	struct maintainer_t
	{
		uint16_t protocol : 2;
		uint16_t hardware : 4;
		uint16_t identifier : 10;
	} __attribute__((packed));

	static const size_t SIZE = sizeof(maintainer_t);

	union register_t
	{
		uint8_t byte[SIZE];
		uint16_t word;

		maintainer_t value;

		void initialize(void);

		void deserialize(uint8_t const *const);
		void serialize(uint8_t **) const;
	} __attribute__((packed));

	extern register_t g_register;

}
