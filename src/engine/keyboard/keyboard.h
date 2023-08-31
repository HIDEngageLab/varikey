/**
 * \file keyboard.h
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * @copyright Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 *
 */

#ifndef __HID_KEYBOARD_H__
#define __HID_KEYBOARD_H__

#include "keypad_event.h"

extern void keyboard_perform(void);
extern void keyboard_handle_event(keypad_event_t const _event);

#endif // __HID_KEYBOARD_H__