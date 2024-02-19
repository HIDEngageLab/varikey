/**
 * \file engine_event_handler.hpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#ifndef __ENGINE_EVENT_QUEUE_HPP__
#define __ENGINE_EVENT_QUEUE_HPP__

#include <queue>

#include "engine_event.hpp"

namespace engine
{
    namespace handler
    {
        typedef std::queue<event_t> event_queue_t;

        extern bool is_hci_enabled();
        extern void set_hci_enabled(const bool);

        extern bool is_hid_enabled();
        extern void set_hid_enabled(const bool);

        extern void perform(void);

        extern void push_wheel_event(const payload::keycode::CONTROL, const engine::keypad::KEY_ID, const engine::keypad::STATE);
        extern void push_key_event(const engine::keypad::KEY_ID, const engine::keypad::STATE);
        extern void push_wheel_switch(const payload::keycode::CONTROL, const engine::keypad::KEY_ID, const engine::keypad::STATE);
        extern void push_joystick_event(const payload::keycode::CONTROL, const engine::keypad::KEY_ID, const engine::keypad::STATE);

        extern event_queue_t event_queue;
    }
}

#endif /* __ENGINE_EVENT_QUEUE_HPP__ */
