/**
 * \file checksum.hpp
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

/**
	\brief CRC16 calculator

	\attention Depends on chunk data type

	\internal
	\author Roman Koch, koch.roman@gmail.com
*/

#ifndef __PULP_CHECKSUM_HPP__
#define __PULP_CHECKSUM_HPP__

#include "chunk.h"

extern uint16_t checksum_sum(chunk_t const *const _chunk, uint16_t const _initial);
extern uint16_t checksum_crc(chunk_t const *const _chunk, uint16_t const _initial);
extern uint16_t checksum_crc_reflected(chunk_t const *_chunk, uint16_t const _initial);

extern uint16_t checksum_crc_byte(uint8_t const _byte, uint16_t const _result);
extern uint16_t checksum_crc_postprocess(uint16_t const _crc);

extern uint32_t checksum_hash(chunk_t const *const _chunk);

void checksum_test(void);

#endif /* __PULP_CHECKSUM_HPP__ */
