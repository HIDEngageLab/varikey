// SPDX-FileCopyrightText: 2024 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: Engine event handler interface
// SPDX-FileType: SOURCE

#pragma once

#include <queue>

#include "engine_event.hpp"

namespace engine::handler
{
    typedef std::queue<event_t> event_queue_t;

    extern bool is_hci_enabled();
    extern void set_hci_enabled(const bool);

    extern bool is_hid_enabled();
    extern void set_hid_enabled(const bool);

    extern void perform(void);

    extern void push_key_event(const engine::keypad::KEY_ID, const engine::keypad::STATE);
    extern void push_gpio_event(const platform::board::IDENTIFIER, const platform::board::VALUE, const uint32_t);
    extern void push_gadget_event(const payload::gadget::FUNCTION);

    extern event_queue_t event_queue;
}
