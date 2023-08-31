/**
 * \file storage_interface.h
 * \author Koch, Roman (koch.roman@googlemail.com)
 * \brief
 * \version 0.1
 * @date 2023-03-28
 *
 * @copyright Copyright (c) 2023
 *
 */
/**
	\brief Storage database

	Very special database for node data.

	\internal
	\author Roman Koch, koch.roman@googlemail.com
*/

#ifndef __STORAGE_INTERFACE_H__
#define __STORAGE_INTERFACE_H__

#include "hil_event.h"
#include "types.h"

/**
	\brief Storage result type
*/
typedef enum
{
	STORAGE_SUCCESS = SUCCESS,
	STORAGE_FAILURE = FAILURE,
	STORAGE_OVERSIZE = 0x02,
	STORAGE_NOT_FOUND = 0x03,
	STORAGE_FULL = 0x04,
	STORAGE_BUSY = 0x05,
	STORAGE_EMPTY = 0x06,
} storage_result_t;

/**
	\brief Storage data exchange structure
*/
typedef struct storage_transport_struct
{
	hil_event_t event;
	uint_fast16_t index;
	uint_fast16_t max;
} storage_transport_t;

extern storage_result_t storage_store_start(storage_transport_t *const _data);
extern storage_result_t storage_store_continue(storage_transport_t *const _data);
extern storage_result_t storage_load_start(storage_transport_t *const _data);
extern storage_result_t storage_load_continue(storage_transport_t *const _data);
extern storage_result_t storage_stop(void);
extern storage_result_t storage_erase(void);

#endif /* __STORAGE_INTERFACE_H__ */
