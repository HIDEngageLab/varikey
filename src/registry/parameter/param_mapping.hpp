/**
 * \file param_mapping.hpp
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

/**
	\brief Configuration parameter keypad mapping

	\internal
	\author Roman Koch, koch.roman@gmail.com
*/

#ifndef __PARAM_MAPPING_HPP__
#define __PARAM_MAPPING_HPP__

#include "parameter.hpp"

namespace registry
{
	namespace parameter
	{
		namespace mapping
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

			/**
				\brief Serial number parameter

				Auto generated (read only) parameter with an unique serial number
			*/
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

			/** \brief Global serial number parameter */
			extern register_t g_register;
		}
	}
}

#endif /* __PARAM_MAPPING_HPP__ */
