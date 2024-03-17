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
			static const size_t SIZE = 24;

			/**
				\brief Serial number parameter

				Auto generated (read only) parameter with an unique serial number
			*/
			struct register_t
			{
				uint8_t modifier[SIZE];
				uint8_t value[SIZE];

				void initialize(void);

				void deserialize(uint8_t const *const);
				void serialize(uint8_t **) const;
			};

			/** \brief Global serial number parameter */
			extern register_t g_register;
		}
	}
}

#endif /* __PARAM_MAPPING_HPP__ */
