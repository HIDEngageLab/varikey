/**
 * \file keypad.h
 * \author Koch, Roman (koch.roman@googlemail.com)
 * \brief
 * \version 0.1
 * @date 2023-03-28
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef __PLATFORM_KEYPAD_H__
#define __PLATFORM_KEYPAD_H__

#include <pico/stdlib.h>
#include <stdint.h>

extern void keypad_callback(uint gpio, uint32_t events);
extern bool keypad_perform(void);

#endif // __PLATFORM_KEYPAD_H__
