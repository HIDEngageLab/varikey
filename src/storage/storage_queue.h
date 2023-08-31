/**
 * \file storage_queue.h
 * \author Koch, Roman (koch.roman@googlemail.com)
 * \brief
 *
 * @copyright Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 *
 */
/**
    \brief Storage item

    \internal
    \author Roman Koch, koch.roman@googlemail.com
*/

#ifndef __STORAGE_QUEUE_H__
#define __STORAGE_QUEUE_H__

#include "chunk.h"
#include "hil_event.h"
#include "macros.h"

typedef struct storage_transport_struct storage_transport_t;

extern void storage_init(void);

extern uint32_t storage_get_used_memory(void);
extern float storage_get_free_memory_progress(void);

extern result_t storage_enqueue(storage_transport_t const *const _data);
extern result_t storage_dequeue(storage_transport_t *const _data);

extern result_t storage_select_all(void);
extern result_t storage_get_selected(storage_transport_t *const _data);

#endif /* __STORAGE_QUEUE_H__ */
