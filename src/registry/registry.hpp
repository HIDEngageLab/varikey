/**
 * \file registry.hpp
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

/**
	\brief Node configuration

	Depends on node parameter.

	\internal
	\author Roman Koch, koch.roman@gmail.com
*/

#ifndef __REGISTRY_HPP__
#define __REGISTRY_HPP__

#include "macros.hpp"

#ifdef __cplusplus
extern "C"
{
#endif

	extern void registry_init(void);
	extern void registry_shutdown(void);

	extern result_t registry_is_ready(void);

#ifdef __cplusplus
}
#endif

#endif /* __REGISTRY_HPP__ */
