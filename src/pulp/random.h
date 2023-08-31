/**
 * \file random.h
 * \author Koch, Roman (koch.roman@googlemail.com)
 * \brief
 * \version 0.1
 * @date 2023-03-28
 *
 * @copyright Copyright (c) 2023
 *
 */
/**
	\brief Random number and sequences generator

	\internal
	\author Roman Koch, koch.roman@googlemail.com
*/

#ifndef __PULP_RANDOM_H__
#define __PULP_RANDOM_H__

#include "chunk.h"

extern void random_init(void);
extern void random_create_sequence(chunk_t *const _sequence);

#endif /* __PULP_RANDOM_H__ */
