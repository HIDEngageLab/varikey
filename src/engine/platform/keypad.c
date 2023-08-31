/**
 * \file keypad.c
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 *
 */

#include <stdio.h>

#include "adp5585.h"
#include "keyboard.h"
#include "keypad.h"
#include "keypad_event.h"

int called_state = 0;

extern void keypad_callback(uint gpio, uint32_t events)
{
    (void)events;
    (void)gpio;
    called_state++;
}

extern bool keypad_perform(void)
{
    if (called_state > 0)
    {
        called_state--;
        while (platform_adp5585_has_event())
        {
            uint8_t state;
            uint8_t identifier;
            platform_adp5585_get_event(&state, &identifier);

            keypad_event_t keypad_event = {(keypad_event_state_t)state, (keypad_event_identifier_t)identifier};
            keyboard_handle_event(keypad_event);
        }

        return true;
    }
    else
    {
        called_state = 0;
    }

    return false;
}
