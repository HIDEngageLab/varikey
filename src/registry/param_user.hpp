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
			};

			/** \brief Global user register parameter */
			extern register_t g_register;

			extern void initialize(void);

			extern void deserialize(uint8_t const *const _chunk);
			extern void serialize(uint8_t *const _space);
		}
	}
}

#endif /* __PARAM_USER_HPP__ */
