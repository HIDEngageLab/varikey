/**
 * \file bytering.h
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 *
 */
/**
	\brief Byte ring

	\internal
	\author Roman Koch, koch.roman@gmail.com
*/

#ifndef __PULP_BYTERING_H__
#define __PULP_BYTERING_H__

#include "chunk.h"
#include <stdlib.h>

/** \brief Ring buffer structure */
typedef struct buffer_struct
{
	chunk_t chunk;
	size_t out;
	size_t in;
	size_t number_of_free_items;
} buffer_t;

extern void bytering_init(buffer_t *const buf, uint8_t *const _space, size_t const _size);
extern size_t bytering_write(buffer_t *const _buf, uint8_t const _value);
extern size_t bytering_read(buffer_t *const _buf, uint8_t *const _value);
extern size_t bytering_copy(buffer_t *const _from, buffer_t *const _to);

extern size_t bytering_peek(buffer_t *const _buf, const size_t _cursor, uint8_t *const _value);

#endif /* __PULP_BYTERING_H__ */
