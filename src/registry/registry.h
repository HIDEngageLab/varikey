/**
 * \file registry.h
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 *
 */
/**
	\brief Node configuration

	Depends on node parameter.

	\internal
	\author Roman Koch, koch.roman@gmail.com
*/

#ifndef __REGISTRY_H__
#define __REGISTRY_H__

#include "macros.h"

extern void registry_init(void);
extern void registry_shutdown(void);

extern result_t registry_is_ready(void);

#endif /* __REGISTRY_H__ */
