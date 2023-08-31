/**
 * \file registry.h
 * \author Koch, Roman (koch.roman@googlemail.com)
 * \brief
 * \version 0.1
 * @date 2023-03-28
 *
 * @copyright Copyright (c) 2023
 *
 */
/**
	\brief Node configuration

	Depends on node parameter.

	\internal
	\author Roman Koch, koch.roman@googlemail.com
*/

#ifndef __REGISTRY_H__
#define __REGISTRY_H__

#include "types.h"

extern void registry_init(void);
extern void registry_shutdown(void);

extern result_t registry_is_ready(void);

#endif /* __REGISTRY_H__ */
