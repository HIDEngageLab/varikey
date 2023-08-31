/**
 * \file keypad.h
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * @copyright Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 *
 */

#ifndef __PLATFORM_KEYPAD_H__
#define __PLATFORM_KEYPAD_H__

#include <pico/stdlib.h>
#include <stdint.h>

extern void keypad_callback(uint gpio, uint32_t events);
extern bool keypad_perform(void);

#endif // __PLATFORM_KEYPAD_H__
