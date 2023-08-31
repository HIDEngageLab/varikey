/**
 * \file chunk.h
 * \author Koch, Roman (koch.roman@googlemail.com)
 * \brief
 * \version 0.1
 * @date 2023-03-28
 *
 * @copyright Copyright (c) 2023
 *
 */
/**
	\brief Byte chunk

	\internal
	\author Roman Koch, koch.roman@googlemail.com
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
