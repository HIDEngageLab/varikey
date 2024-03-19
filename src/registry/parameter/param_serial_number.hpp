/**
 * \file param_serial_number.hpp
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

/**
	\brief Configuration parameter serial number

	\internal
	\author Roman Koch, koch.roman@gmail.com
*/

#ifndef __PARAM_SERIAL_NUMBER_HPP__
#define __PARAM_SERIAL_NUMBER_HPP__

#include "parameter.hpp"

namespace registry
{
	namespace parameter
	{
		namespace serial_number
		{
			static const uint32_t INVALID_VALUE = 0xffffffff;
			static const size_t SIZE = 12;

			/**
				\brief Serial number parameter

				Auto generated (read only) parameter with an unique serial number
			*/
			struct register_t
			{
				uint8_t value[SIZE];

				void initialize(void);

				void deserialize(uint8_t const *const);
				void serialize(uint8_t **) const;
			} __attribute__((packed));

			/** \brief Global serial number parameter */
			extern register_t g_register;

			/** \brief Global unique key parameter */
			extern uint32_t g_unique_key;
		}
	}
}

#endif /* __PARAM_SERIAL_NUMBER_HPP__ */
