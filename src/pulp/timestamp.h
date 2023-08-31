/**
 * \file timestamp.h
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 *
 */
/**
	\brief Timestamp

	\internal
	\author Roman Koch, koch.roman@gmail.com
*/

#ifndef __PULP_TIMESTAMP_H__
#define __PULP_TIMESTAMP_H__

#include <stdint.h>

extern void timestamp_reset(void);
extern uint64_t timestamp(void);

#endif /* __PULP_TIMESTAMP_H__ */
