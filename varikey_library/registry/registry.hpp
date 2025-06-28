/**
 * \file registry.hpp
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

/**
	\brief Configuration parameter

	\internal
	\author Roman Koch, koch.roman@gmail.com
*/

#ifndef __REGISTRY_HPP__
#define __REGISTRY_HPP__

#include "macros.hpp"
#include "registry_defines.hpp"

namespace registry
{
	extern void initialize(void);
	extern void shutdown(void);

	extern result_t is_ready(void);
}

#endif /* __REGISTRY_HPP__ */
