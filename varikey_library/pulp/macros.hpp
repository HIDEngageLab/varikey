// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: Common utility macros
// SPDX-FileType: SOURCE

#pragma once

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

namespace common
{
	namespace result
	{
		enum VALUE
		{
			ERROR = 0x04,
			FAILURE = 0x01,
			SUCCESS = 0x00,
			UNKNOWN = 0x02,
			UNSUPPORTED = 0x03,

			CUSTOM = 0x80,

			UNDEFINED = 0xFF,
		};
	}
	namespace function
	{
		enum VALUE
		{
			CLEAN = 0x08,
			DISABLE = 0x03,
			ENABLE = 0x02,
			GET = 0x00,
			OFF = 0x07,
			ON = 0x06,
			SET = 0x01,
			START = 0x04,
			STOP = 0x05,

			CUSTOM = 0x80,

			UNDEFINED = 0xFF,
		};
	}
}

typedef enum
{
	DISABLE = 0,
	ENABLE = 1
} ability_t;

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
