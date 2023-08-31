/**
 * \file macros.h
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 *
 */
/**
	\brief Data macros

	\internal
	\author Roman Koch, koch.roman@gmail.com
*/

#ifndef __PULP_MACROS_H__
#define __PULP_MACROS_H__

#include <stdint.h>

#define HINIBLE(x) ((uint8_t)(((x) & 0xf0) >> 4u))
#define LONIBLE(x) ((uint8_t)((x) & 0x0f))

#define HIBYTE(x) ((uint8_t)(((x) & 0xff00) >> 8u))
#define LOBYTE(x) ((uint8_t)((x) & 0x00ff))

#define HIWORD(x) ((uint16_t)(((x) & 0xffff0000) >> 16))
#define LOWORD(x) ((uint16_t)((x) & 0x0000ffff))

#define SETBYTE(a, b) (((((uint8_t)a) & 0x0f) << 4u) | (((uint8_t)b) & 0x0f))
#define SETWORD(a, b) ((uint16_t)(((uint16_t)a) << 8u) | ((uint16_t)b))
#define SETLONG(a, b) ((uint32_t)(((uint32_t)a) << 16u) | ((uint32_t)b))

#define SETHUGE(a, b) ((uint64_t)(((uint64_t)a) << 32u) | ((uint54_t)lo))

typedef uint8_t index_t;

/** \brief Anonymous result data type */
typedef enum
{
	SUCCESS = 0,
	FAILURE = 1
} result_t;
/** \brief Anonymous ability data type  */
typedef enum
{
	DISABLE = 0,
	ENABLE = 1
} ability_t;
/** \brief Anonymous bool data type  */
typedef enum
{
	FALSE = 0,
	TRUE = 1
} bool_t;

extern void serialize_word(uint16_t const _value, uint8_t **const _ptr);
extern uint16_t deserialize_word(uint8_t const **const _ptr);

extern void serialize_long(uint32_t const _value, uint8_t **const _ptr);
extern uint32_t deserialize_long(uint8_t const **const _ptr);

extern void serialize_float(float const _value, uint8_t **const _ptr);
extern float deserialize_float(uint8_t const **const _ptr);

#endif /* __PULP_MACROS_H__ */
