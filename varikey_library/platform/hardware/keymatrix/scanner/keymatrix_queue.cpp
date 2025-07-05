// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: Hardware keymatrix queue functionality
// SPDX-FileType: SOURCE

#include "keymatrix_queue.hpp"

constexpr size_t KEY_EVENT_QUEUE_SIZE = 64;

queue_t event_queue;

namespace keymatrix
{
    void init_queue()
    {
        queue_init(&event_queue, sizeof(KeyEvent), KEY_EVENT_QUEUE_SIZE); // bis zu 32 Events
    }

    bool push_event(KeyEvent::Type type, uint8_t row, uint8_t col)
    {
        KeyEvent evt = {type, row, col};
        return queue_try_add(&event_queue, &evt);
    }

    bool push_event(const KeyEvent &event)
    {
        return queue_try_add(&event_queue, &event);
    }

    bool has_event(void)
    {
        return queue_get_level(&event_queue) > 0;
    }

    bool pop_event(KeyEvent &event)
    {
        return queue_try_remove(&event_queue, &event);
    }
}
