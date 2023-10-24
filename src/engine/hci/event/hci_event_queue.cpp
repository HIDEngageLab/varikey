/**
 * \file hci_event_queue.cpp
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */
/**
    \brief Host controller interface event queue

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#include <pico/sync.h>
#include <string.h>

#include "hci_event_queue.hpp"
#include "revision.h"

#define __DEBUG_EVENT_QUEUE

/** \brief HCI event item */
typedef struct hil_event_chunk_struct
{
    hci_event_timed_t *space;
    size_t size;
} hil_event_chunk_t;

/** \brief Ring buffer structure */
typedef struct hil_event_queue_struct
{
    hil_event_chunk_t chunk;
    size_t out;
    size_t in;
    size_t number_of_free_items;
} hil_event_queue_t;

/* \name Adapter hardware event queue defines */
/* @{ */
/* \brief Max number of event items in the event queue */
#define EVENT_CHUNK_SIZE 512
/* @} */

hci_event_timed_t event_space[EVENT_CHUNK_SIZE];
hil_event_chunk_t event_chunk = {event_space, EVENT_CHUNK_SIZE};

hil_event_queue_t queue;

mutex_t mutex;
#define ENTER() mutex_enter_blocking(&mutex)
// #define ENTER()
#define EXIT() mutex_exit(&mutex)
// #define EXIT()

/**
    \brief Initialize byte ring buffer
*/
extern void hil_event_queue_init(void)
{
    queue.chunk.space = event_space;
    queue.chunk.size = EVENT_CHUNK_SIZE;
    queue.number_of_free_items = EVENT_CHUNK_SIZE;
    queue.in = 0;
    queue.out = 0;

    mutex_init(&mutex);
}

extern size_t hil_event_queue_is_empty(void)
{
    ENTER();
    if ((queue.number_of_free_items == queue.chunk.size) && (queue.in == queue.out))
    {
        // buffer is empty
        EXIT();
        return 1;
    }
    EXIT();
    return 0;
}

/**
    \brief Store a byte in the buffer
*/
extern size_t hil_event_queue_push(hci_event_timed_t const *const _event)
{
    ENTER();
    if (queue.number_of_free_items == 0)
    {
        // buffer is full
        EXIT();
        return 0;
    }

    queue.number_of_free_items--;
    queue.chunk.space[queue.in++] = *_event;

    queue.in &= (queue.chunk.size - 1);
#ifdef DEBUG_EVENT_QUEUE
    size_t dist = (queue.in < queue.out) ? queue.out - queue.in : queue.in - queue.out;

    if ((dist > 0) && (queue.number_of_free_items == 0))
    {
        assert(false); // byte ring write free items number error
    }

#endif
    EXIT();
    return 1;
}

/**
    \brief Read a byte from buffer
*/
extern size_t hil_event_queue_pop(hci_event_timed_t *const _value)
{
    ENTER();
    if ((queue.number_of_free_items == queue.chunk.size) && (queue.in == queue.out))
    {
        // buffer is empty
        EXIT();
        return 0;
    }

    queue.number_of_free_items++;

    *_value = queue.chunk.space[queue.out++];

    queue.out &= (queue.chunk.size - 1);
#ifdef DEBUG_EVENT_QUEUE
    size_t dist = (queue.in < queue.out) ? queue.out - queue.in : queue.in - queue.out;

    if ((dist > 0) && (queue.number_of_free_items == 0))
    {
        // byte ring write free items number error
    }

#endif
    EXIT();
    return 1;
}

extern size_t hil_event_queue_peek(const size_t _cursor, hci_event_timed_t *const _value)
{
    ENTER();
    if ((queue.number_of_free_items == queue.chunk.size) && (queue.in == queue.out))
    {
        // buffer is empty
        EXIT();
        return 0;
    }

    // attention: position can be "over the border"
    size_t position = (queue.out + _cursor);
    // truncate position to the buffer size
    position &= (queue.chunk.size - 1);

    if (queue.in > queue.out)
    {
        // normal in-out order
        if (position >= queue.in)
        {
            EXIT();
            return 0;
        }
    }
    else
    {
        // inverse in-out order (chunk placed "over the border")
        if ((position >= queue.in) && (position < queue.out))
        {
            EXIT();
            return 0;
        }
    }

    *_value = queue.chunk.space[position];
    EXIT();
    return 1;
}
