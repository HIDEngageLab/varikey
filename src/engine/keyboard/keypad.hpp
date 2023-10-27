/**
 * \file keypad.hpp
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#ifndef __ENGINE_KEYPAD_HPP__
#define __ENGINE_KEYPAD_HPP__

#include "keypad_event.hpp"

extern void keypad_perform(void);
extern void keypad_handle_event(engine::keypad::event_t const _event);

#endif // __ENGINE_KEYPAD_HPP__