/**
 * \file checksum.c
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 *
 */
/**
    \brief CRC16 calculator

    https://crccalc.com/
    CRC-16/XOPERATIONM
    Payload only

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#include "checksum.h"

/** \name Polynomial */
/* @{ */
#define CRC_IBM_GENERATOR 0x8005
#define CRC_DNP_GENERATOR 0x3d65
#define CRC_DECT_GENERATOR 0x0589
#define CRC_CCITT_GENERATOR 0x1021

#define CRC_POLYNOMIAL CRC_CCITT_GENERATOR
/* @} */

/** \name Initials */
/* @{ */
#define DEFAULT_INITIAL_VALUE 0xFFFF
#define DEFAULT_FINAL_XOR_VALUE 0x0000
#define CRC_XOR DEFAULT_FINAL_XOR_VALUE
/* @} */

static uint8_t reflect8(uint8_t const _byte);
static uint16_t reflect16(uint16_t const _word);
static uint32_t mix32(uint32_t const _hash);

/**
    \brief Calculate check sum value from byte chunk

    Chunk preparation for a chunk X over 10 bytes, start on byte 2:
        chunk_t Y = {&X.space[2], 10};
        uint16_t val = crc16_algorithm_sum(&Y);
*/
extern uint16_t checksum_sum(chunk_t const *const _chunk, uint16_t const _initial)
{
    uint16_t result = _initial;
    uint8_t *prt = _chunk->space;

    for (uint8_t i = 0; i < _chunk->size; ++i)
    {
        result += *prt++;
    }

    return result;
}

/**
    \brief Calculate CRC16 value from byte chunk
*/
extern uint16_t checksum_crc(chunk_t const *const _chunk, uint16_t const _initial)
{
    uint16_t result = _initial;
    uint8_t *ptr = _chunk->space;

    for (uint8_t i = 0; i < _chunk->size; ++i)
    {
        result = checksum_crc_byte(*ptr++, result);
    }

    return result ^ CRC_XOR;
}

/**
    \brief Calculate reflected CRC16 value from byte chunk
*/
extern uint16_t checksum_crc_reflected(chunk_t const *const _chunk, uint16_t const _initial)
{
    uint16_t result = _initial;
    uint8_t *ptr = _chunk->space;

    for (uint8_t i = 0; i < _chunk->size; ++i)
    {
        uint8_t byte = reflect8(*ptr++);
        result = checksum_crc_byte(byte, result);
    }

    result = reflect16(result);
    return result ^ CRC_XOR;
}

/**
    \brief CRC byte
*/
extern uint16_t checksum_crc_byte(uint8_t const _byte, uint16_t const _result)
{
    uint16_t tmp = (uint16_t)(_result ^ _byte << 8);

    for (uint8_t i = 0; i < 8; ++i)
    {
        if ((tmp & 0x8000) > 0)
        {
            tmp = (uint16_t)(tmp << 1 ^ CRC_POLYNOMIAL);
        }
        else
        {
            tmp = (uint16_t)(tmp << 1);
        }
    }

    return tmp;
}

/**
    \brief CRC post processing
*/
extern uint16_t checksum_crc_postprocess(uint16_t const _crc)
{
    uint16_t result = _crc;
    return result ^= CRC_XOR;
}

/**
    \brief Calculate a 32bit hash value from chunk
*/
extern uint32_t checksum_hash(chunk_t const *const _chunk)
{
    /* initialization */
    int n = _chunk->size;
    uint32_t hash = 0x79FEF6E8;
    int i = 0;

    /* process each block */
    while (i < n - 2)
    {
        /* combining step */
        hash += (uint32_t)(_chunk->space[i++]);
        hash += ((uint32_t)(_chunk->space[i++])) << 16;
        /* mixing step */
        hash = mix32(hash);
    }

    /* process partial block */
    if (i < n)
    {
        /* combining step */
        hash += (uint32_t)(_chunk->space[i++]);
        /* mixing step */
        hash = mix32(hash);
    }

    /* post-processing step */
    hash = mix32(mix32(hash));
    return hash;
}

/**
    \brief Calculate reflected byte CRC
*/
static uint8_t reflect8(uint8_t const _byte)
{
    uint8_t reflector = 1;
    uint8_t result = 0;

    for (uint8_t i = (uint8_t)(1 << 7); i != 0; i >>= 1)
    {
        if ((_byte & i) > 0)
        {
            result |= reflector;
        }

        reflector <<= 1;
    }

    return result;
}

/**
    \brief Calculate reflected word CRC
*/
static uint16_t reflect16(uint16_t const _word)
{
    uint16_t reflector = 1;
    uint16_t result = 0;

    for (uint16_t i = (uint16_t)(1 << 15); i != 0; i >>= 1)
    {
        if ((_word & i) > 0)
        {
            result |= reflector;
        }

        reflector <<= 1;
    }

    return result;
}

/**
    \brief helper to calculate 32bit value
*/
static uint32_t mix32(uint32_t const _hash)
{
    uint32_t _result = _hash;
    _result += _result << 11;
    _result ^= ~_result >> 5;
    _result -= _result << 13;
    return _result;
}

/**
    \brief CRC test
*/
void checksum_test(void)
{
#if defined(CHECKSUM_TEST)
    uint16_t bla = 0;
    uint8_t a[10] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a};
    chunk_t b = {a, 10};
    bla = checksum_crc(&b, 0);
#endif
}
