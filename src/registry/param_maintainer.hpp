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

/** \brief Maintainer parameter structure */
typedef union param_maintainer
{
	uint8_t byte;
	struct param_maintainer_struct
	{
		uint8_t value : 4;
		uint8_t hardware : 2;
		uint8_t protocol : 2;
	} maintainer;
} param_maintainer_t;

extern param_maintainer_t g_maintainer;

extern void param_maintainer_init(void);

extern void param_maintainer_deserialize(uint8_t const *const _space);
extern void param_maintainer_serialize(uint8_t *const _space);

#endif /* __PARAM_MAINTAINER_HPP__ */
