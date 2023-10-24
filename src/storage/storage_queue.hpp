/**
 * \file storage_queue.hpp
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 *
 */
/**
    \brief Storage item

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#ifndef __STORAGE_QUEUE_HPP__
#define __STORAGE_QUEUE_HPP__

#include "chunk.h"
#include "macros.hpp"

typedef struct storage_transport_struct storage_transport_t;

extern void storage_init(void);

extern uint32_t storage_get_used_memory(void);
extern float storage_get_free_memory_progress(void);

extern result_t storage_enqueue(storage_transport_t const *const _data);
extern result_t storage_dequeue(storage_transport_t *const _data);

extern result_t storage_select_all(void);
extern result_t storage_get_selected(storage_transport_t *const _data);

#endif /* __STORAGE_QUEUE_HPP__ */
