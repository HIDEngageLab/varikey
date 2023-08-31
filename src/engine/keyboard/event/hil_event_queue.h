/**
 * \file hil_event_queue.h
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 *
 */
/**
    \brief Adaper hardware event queue

    Event queue only for storable user interaction events.

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#ifndef _COMPOSED_HID_HIL_EVENT_QUEUE_H_
#define _COMPOSED_HID_HIL_EVENT_QUEUE_H_

#include <stdint.h>

#include "chunk.h"
#include "hil_event.h"

extern void hil_event_queue_init(void);

extern size_t hil_event_queue_is_empty(void);

extern size_t hil_event_queue_push(hil_event_timed_t const *const _event);
extern size_t hil_event_queue_pop(hil_event_timed_t *const _event);
extern size_t hil_event_queue_peek(const size_t _cursor, hil_event_timed_t *const _event);

#endif /* _COMPOSED_HID_HIL_EVENT_QUEUE_H_ */
