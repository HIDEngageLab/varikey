/**
 * \file chunk.h
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * @copyright Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 *
 */
/**
	\brief Byte chunk

	\internal
	\author Roman Koch, koch.roman@gmail.com
*/

#ifndef __PULP_CHUNK_H__
#define __PULP_CHUNK_H__

#include <stdint.h>
#include <stdlib.h>

/** \brief Chunk structure */
typedef struct chunk_struct
{
	uint8_t *space;
	size_t size;
} chunk_t;

#endif /* __PULP_CHUNK_H__ */
