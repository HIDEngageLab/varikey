/**
 * \file guard_macros.h
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * @copyright Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 *
 */
/**
	\brief ISR guard

	\internal
	\author Roman Koch, koch.roman@gmail.com
*/

#ifndef __PULP_GUARD_MACROS_H__
#define __PULP_GUARD_MACROS_H__

#include <hardware/sync.h>

#define INT_GUARD_OPEN() uint32_t ints = save_and_disable_interrupts();
#define INT_GUARD_CLOSE() restore_interrupts(ints);

#endif /* __PULP_GUARD_MACROS_H__ */
