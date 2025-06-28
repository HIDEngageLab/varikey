#pragma once

#include <cstdint>

#include <pico/multicore.h>
#include <pico/stdlib.h>

#include <pico/util/queue.h>

namespace keymatrix
{
    struct KeyEvent
    {
        enum Type
        {
            PRESS,
            RELEASE
        } type;

        uint8_t row;
        uint8_t col;

        KeyEvent() = default;
        KeyEvent(Type t, uint8_t r, uint8_t c)
            : type(t), row(r), col(c) {}
    };

    void init_queue();
    bool push_event(KeyEvent::Type type, uint8_t row, uint8_t col);
    bool push_event(const KeyEvent &event);
    bool has_event(void);
    bool pop_event(KeyEvent &event);
}