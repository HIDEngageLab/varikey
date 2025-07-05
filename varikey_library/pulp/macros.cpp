// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: Common utility macros implementation
// SPDX-FileType: SOURCE

#include <stdint.h>

#include "macros.hpp"

extern void serialize_word(uint16_t const _value, uint8_t **const _ptr)
{

    *(*_ptr)++ = (uint8_t)HIBYTE(_value);
    *(*_ptr)++ = (uint8_t)LOBYTE(_value);
}

extern uint16_t deserialize_word(uint8_t const **const _ptr)
{

    uint8_t byte1 = *(*_ptr)++;
    uint8_t byte2 = *(*_ptr)++;
    return (uint16_t)SETWORD(byte1, byte2);
}

extern void serialize_long(uint32_t const _value, uint8_t **const _ptr)
{

    *(*_ptr)++ = (uint8_t)HIBYTE(HIWORD(_value));
    *(*_ptr)++ = (uint8_t)LOBYTE(HIWORD(_value));
    *(*_ptr)++ = (uint8_t)HIBYTE(LOWORD(_value));
    *(*_ptr)++ = (uint8_t)LOBYTE(LOWORD(_value));
}

extern uint32_t deserialize_long(uint8_t const **const _ptr)
{

    uint8_t byte1 = *(*_ptr)++;
    uint8_t byte2 = *(*_ptr)++;
    uint8_t byte3 = *(*_ptr)++;
    uint8_t byte4 = *(*_ptr)++;
    return (uint32_t)SETLONG(SETWORD(byte1, byte2), SETWORD(byte3, byte4));
}

extern void serialize_float(float const _value, uint8_t **const _ptr)
{

    uint8_t const *const array = ((uint8_t const *)&_value);
    *(*_ptr)++ = array[0];
    *(*_ptr)++ = array[1];
    *(*_ptr)++ = array[2];
    *(*_ptr)++ = array[3];
}

extern float deserialize_float(uint8_t const **const _ptr)
{

    uint8_t array[4];
    array[0] = *(*_ptr)++;
    array[1] = *(*_ptr)++;
    array[2] = *(*_ptr)++;
    array[3] = *(*_ptr)++;
    return *(float *)(array);
}
