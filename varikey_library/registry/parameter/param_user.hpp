/**
 * \file param_user.hpp
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

/**
	\brief Parameter "user register"

	\internal
	\author Roman Koch, koch.roman@gmail.com
*/

#ifndef __PARAM_USER_HPP__
#define __PARAM_USER_HPP__

#include "parameter.hpp"

namespace registry
{
	namespace parameter
	{
		namespace user
		{
			static const size_t SIZE = 2;

			/** \brief User register; ignored by firmware. */
			struct register_t
			{
				uint8_t value[SIZE];

				void initialize(void);

				void deserialize(uint8_t const *const);
				void serialize(uint8_t **) const;
			} __attribute__((packed));

			/** \brief Global user register parameter */
			extern register_t g_register;
		}
	}
}

#endif /* __PARAM_USER_HPP__ */
