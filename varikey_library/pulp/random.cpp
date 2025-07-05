// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: Random number generation implementation
// SPDX-FileType: SOURCE

#include <assert.h>
#include <stdlib.h>

#include "board_assembly.hpp"
#include "checksum.hpp"
#include "macros.hpp"
#include "random.hpp"

typedef enum
{
    UNDEFINED,
    READY,
} state_t;

static state_t state = UNDEFINED;

static uint8_t create_random(const uint16_t _value);


extern void random_init(void)
{
    assert(state == UNDEFINED); // random generator not initialized
    state = READY;

    
    const uint16_t value = platform::board::assembly.soc.get_temperature_raw();
    const uint8_t result = 1 + (create_random(value) & 0x0f);
    uint16_t seed = result;

    for (uint8_t i = 0; i < result; ++i)
    {
        const uint16_t value = platform::board::assembly.soc.get_temperature_raw();
        uint8_t byte = create_random(value);
        seed = checksum_crc_byte(byte, seed);
    }

    srand(seed);
}


extern void random_create_sequence(chunk_t *const _sequence)
{
    assert(state == READY);    // random sequence, generator uninitialized
    assert(_sequence != NULL); // random sequence parameter is null

    
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


uint8_t create_random(const uint16_t _value)
{
    assert(state == READY);
    uint8_t result = 0;
    uint8_t mask = 1;

    for (int i = 0; i < 11; ++i)
    {
        uint16_t tmp = _value;

        if (tmp & mask)
        {
            result |= mask;
        }
        else
        {
            result &= ~mask;
        }

        if (mask == 0x80)
        {
            mask = 1;
        }
        else
        {
            mask <<= 1;
        }
    }

    return result;
}
