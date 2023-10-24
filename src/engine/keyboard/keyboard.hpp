/**
 * \file keyboard.hpp
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#ifndef __HID_KEYBOARD_HPP__
#define __HID_KEYBOARD_HPP__

#include "keypad_event.hpp"

extern void keyboard_perform(void);
extern void keyboard_handle_event(engine::keypad::event_t const _event);

#endif // __HID_KEYBOARD_HPP__