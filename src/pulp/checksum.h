/**
 * \file checksum.h
 * \author Koch, Roman (koch.roman@googlemail.com)
 * \brief
 * \version 0.1
 * @date 2023-03-28
 *
 * @copyright Copyright (c) 2023
 *
 */
/**
	\brief CRC16 calculator

	\attention Depends on chunk data type

	\internal
	\author Roman Koch, koch.roman@googlemail.com
*/

#ifndef __PULP_CHECKSUM_H__
#define __PULP_CHECKSUM_H__

#include "chunk.h"

extern uint16_t checksum_sum(chunk_t const *const _chunk, uint16_t const _initial);
extern uint16_t checksum_crc(chunk_t const *const _chunk, uint16_t const _initial);
extern uint16_t checksum_crc_reflected(chunk_t const *_chunk, uint16_t const _initial);

extern uint16_t checksum_crc_byte(uint8_t const _byte, uint16_t const _result);
extern uint16_t checksum_crc_postprocess(uint16_t const _crc);

extern uint32_t checksum_hash(chunk_t const *const _chunk);

void checksum_test(void);

#endif /* __PULP_CHECKSUM_H__ */
