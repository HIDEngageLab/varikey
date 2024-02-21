/**
 * \file param_maintainer.hpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

/**
	\brief Parameter "maintainer"

	\internal
	\author Roman Koch, koch.roman@gmail.com
*/

#ifndef __PARAM_MAINTAINER_HPP__
#define __PARAM_MAINTAINER_HPP__

#include "parameter.hpp"

namespace registry
{
	namespace parameter
	{
		namespace maintainer
		{
			static const size_t SIZE = sizeof(uint16_t) * 1;

			/** \brief Maintainer parameter structure */
			union register_t
			{
				uint8_t byte[2];
				uint16_t word;
				struct __attribute__((packed)) maintainer_t
				{
					uint16_t protocol : 2;
					uint16_t hardware : 4;
					uint16_t identifier : 12;
				} value;

				void initialize(void);

				void deserialize(uint8_t const *const _space);
				void serialize(uint8_t *const _space) const;
			};

			extern register_t g_register;

		}
	}
}

#endif /* __PARAM_MAINTAINER_HPP__ */
