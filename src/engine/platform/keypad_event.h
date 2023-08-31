/**
 * \file keypad_event.h
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 *
 */

#ifndef __PLATFORM_KEYPAD_EVENT_H__
#define __PLATFORM_KEYPAD_EVENT_H__

typedef enum
{
    KEYPAD_UNDEFINED = 0,
    KEYPAD_R0_C0 = 1,
    KEYPAD_R1_C0 = 6,
    KEYPAD_R2_C0 = 11,
    KEYPAD_R3_C0 = 16,
    KEYPAD_R4_C0 = 21,
    KEYPAD_R0_C1 = 2,
    KEYPAD_R1_C1 = 7,
    KEYPAD_R2_C1 = 12,
    KEYPAD_R3_C1 = 17,
    KEYPAD_R4_C1 = 22,
    KEYPAD_A = 46,
    KEYPAD_B = 47,
    KEYPAD_C = 45,
} keypad_event_identifier_t;

typedef enum
{
    KEYPAD_STATE_RELEASE = 0,
    KEYPAD_STATE_PRESS = 1,
} keypad_event_state_t;

typedef struct
{
    keypad_event_state_t state;
    keypad_event_identifier_t identifier;
} keypad_event_t;

#endif // __PLATFORM_KEYPAD_EVENT_H__
