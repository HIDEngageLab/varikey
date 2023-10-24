/**
 * \file hci_event_queue.hpp
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 *
 */
/**
    \brief Host controller interface event queue

    Event queue only for storable user interaction events.

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#ifndef __ENGINE_HCI_EVENT_QUEUE_HPP__
#define __ENGINE_HCI_EVENT_QUEUE_HPP__

#include <stdint.h>

#include "chunk.h"
#include "hci_event.hpp"

extern void hil_event_queue_init(void);

extern size_t hil_event_queue_is_empty(void);

extern size_t hil_event_queue_push(hci_event_timed_t const *const _event);
extern size_t hil_event_queue_pop(hci_event_timed_t *const _event);
extern size_t hil_event_queue_peek(const size_t _cursor, hci_event_timed_t *const _event);

#endif /* __ENGINE_HCI_EVENT_QUEUE_HPP__ */
