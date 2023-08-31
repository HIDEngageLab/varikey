/**
 * \file random.c
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 *
 */
/**
    \brief Random number and sequences generator

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#include <pico/stdlib.h>
#include <stdlib.h>

#include "checksum.h"
#include "macros.h"
#include "random.h"
#include "temperature.h"

typedef enum
{
    UNDEFINED,
    READY,
} state_t;

static state_t state = UNDEFINED;

/**
    \brief random generator initialization
*/
extern void random_init(void)
{
    assert(state == UNDEFINED); // random generator not initialized
    state = READY;

    /* calculate seed (paranoid) */
    const uint8_t result = temperature_create_random_byte() & 0x0f;
    uint16_t seed = result;

    for (uint8_t i = 0; i < result; ++i)
    {
        uint8_t byte = temperature_create_random_byte();
        seed = checksum_crc_byte(byte, seed);
    }

    srand(seed);
}

/**
    \brief Create random sequence
*/
extern void random_create_sequence(chunk_t *const _sequence)
{
    assert(state == READY);    // random sequence, generator uninitialized
    assert(_sequence != NULL); // random sequence parameter is null

    /* calculate sequence item */
    uint8_t *ptr = _sequence->space;
    uint8_t len = _sequence->size & ~0x01;

    for (uint8_t i = 0; i < len; i += 2)
    {
        uint16_t tmp = rand();
        *ptr++ = HIBYTE(tmp);
        *ptr++ = LOBYTE(tmp);
    }

    if (_sequence->size & 0x01)
    {
        uint16_t tmp = rand();
        *ptr++ = HIBYTE(tmp);
    }
}
