// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: Mapping parameter configuration
// SPDX-FileType: SOURCE

#pragma once

#include "parameter.hpp"

namespace registry::parameter::mapping
{
	struct keycode_t
	{
		uint8_t modifier;
		uint8_t code;
	} __attribute__((packed));

	union item_t
	{
		uint8_t byte[1 + sizeof(keycode_t)];
		struct
		{
			uint8_t index;
			keycode_t value;
		} item;

		void deserialize(uint8_t const *const);
		void serialize(uint8_t **) const;
	} __attribute__((packed));

	static const size_t SIZE = 24;

	struct register_t
	{
		union
		{
			uint8_t byte[sizeof(keycode_t) * SIZE];
			keycode_t value[SIZE];
		};

		void initialize(void);

		void deserialize(uint8_t const *const);
		void serialize(uint8_t **) const;
	} __attribute__((packed));

	extern register_t g_register;
}
