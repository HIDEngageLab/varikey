/**
 * \file keyboard.h
 * \author Koch, Roman (koch.roman@googlemail.com)
 * \brief
 * \version 0.1
 * @date 2023-03-28
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef __HID_KEYBOARD_H__
#define __HID_KEYBOARD_H__

#include "keypad_event.h"

extern void keyboard_perform(void);
extern void keyboard_handle_event(keypad_event_t const _event);

#endif // __HID_KEYBOARD_H__