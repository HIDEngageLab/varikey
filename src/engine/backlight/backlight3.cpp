/**
 * \file backlight.cpp
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#include <stdio.h>

#include <pico/assert.h>
#include <pico/time.h>

#include "backlight3.hpp"
#include "backlight_color.hpp"
#include "backlight_type.hpp"

#include "board.hpp"

typedef enum
{
    UNDEFINED = 0,
    INITIALIZED
} status_t;

typedef struct
{
    float value;
    float increment;
} color_change_t;

typedef struct
{
    color_t curent;
    color_change_t value;
    color_t next;
} led_t;

typedef struct
{
    led_t left;
    color_t middle;
    led_t right;
    status_t status;
    backlight_mode_t mode;
    backlight_mode_t next_mode;
    uint64_t next_delay_ms;
} backlight_t;

typedef struct
{
    color_t left;
    color_t right;
} program_t;

backlight_t backlight = {0};

const program_t program[6] = {
    {.left = {.rgb = {0x00, 0xff, 0x00, 0x00}}, .right = {.rgb = {0x00, 0x00, 0xff, 0x00}}},
    {.left = {.rgb = {0x00, 0xff, 0xff, 0x00}}, .right = {.rgb = {0x00, 0x00, 0xff, 0xff}}},
    {.left = {.rgb = {0x00, 0x00, 0xff, 0x00}}, .right = {.rgb = {0x00, 0x00, 0x00, 0xff}}},
    {.left = {.rgb = {0x00, 0x00, 0xff, 0xff}}, .right = {.rgb = {0x00, 0xff, 0x00, 0xff}}},
    {.left = {.rgb = {0x00, 0x00, 0x00, 0xff}}, .right = {.rgb = {0x00, 0xff, 0x00, 0x00}}},
    {.left = {.rgb = {0x00, 0xff, 0x00, 0xff}}, .right = {.rgb = {0x00, 0xff, 0xff, 0x00}}},
};

int const BLINK_NOT_MOUNTED = 250;
int const BLINK_MOUNTED = 1000;
int const BLINK_SUSPENDED = 2500;

static void perform_step(const int _delay);
static void program_switch();

extern void backlight_init(void)
{
    backlight.status = INITIALIZED;
}

extern void backlight_mode(const backlight_mode_t _mode, const uint64_t _delay_ms)
{
    assert(backlight.status == INITIALIZED);
    backlight.next_mode = _mode;
    backlight.next_delay_ms = _delay_ms;
}

extern void backlight_perform(void)
{
    assert(backlight.status == INITIALIZED);

    if (backlight.mode != backlight.next_mode)
    {
        static absolute_time_t timestamp = {0};
        absolute_time_t current_time = get_absolute_time();

        const uint64_t us_diff = to_us_since_boot(current_time) - to_us_since_boot(timestamp);
        if (us_diff > backlight.next_delay_ms * 1000)
        {
            backlight.mode = backlight.next_mode;
        }
    }

    switch (backlight.mode)
    {
    case BACKLIGHT_PROGRAM_MEDIUM:
        perform_step(100);
        program_switch();
        break;
    case BACKLIGHT_PROGRAM_SLOW:
        perform_step(500);
        program_switch();
        break;
    case BACKLIGHT_PROGRAM_TURBO:
        perform_step(10);
        program_switch();
        break;
    case BACKLIGHT_NOT_MOUNTED:
        if (backlight.right.curent.rgb.r == 0x0f &&
            backlight.right.curent.rgb.g == 0 &&
            backlight.right.curent.rgb.b == 0)
        {
            backlight_set_left(0, 0, 0);
            backlight_set_right(0, 0, 0);
        }
        else
        {
            backlight_set_left(0x0f, 0, 0);
            backlight_set_right(0x0f, 0, 0);
        }
        perform_step(BLINK_NOT_MOUNTED);
        break;
    case BACKLIGHT_MOUNTED:
        if (backlight.right.curent.rgb.r == 0 &&
            backlight.right.curent.rgb.g == 0x0f &&
            backlight.right.curent.rgb.b == 0)
        {
            backlight_set_left(0, 0x0e, 0);
            backlight_set_right(0, 0x0e, 0);
        }
        else
        {
            backlight_set_left(0, 0x0f, 0);
            backlight_set_right(0, 0x0f, 0);
        }
        perform_step(BLINK_MOUNTED);
        break;
    case BACKLIGHT_SUSPENDED:
        if (backlight.right.curent.rgb.r == 0x0f &&
            backlight.right.curent.rgb.g == 0x0f &&
            backlight.right.curent.rgb.b == 0)
        {
            backlight_set_left(0, 0, 0);
            backlight_set_right(0, 0, 0);
        }
        else
        {
            backlight_set_left(0x0f, 0x0f, 0);
            backlight_set_right(0x0f, 0x0f, 0);
        }
        perform_step(BLINK_SUSPENDED);
        break;
    case BACKLIGHT_CONST:
        if (backlight.left.next.value != backlight.left.curent.value &&
            backlight.right.next.value != backlight.right.curent.value)
        {
            perform_step(10);
        }
        break;
    case BACKLIGHT_OFF:
        if (backlight.left.next.value != backlight.left.curent.value &&
            backlight.right.next.value != backlight.right.curent.value)
        {
            backlight_set_left(0, 0, 0);
            backlight_set_right(0, 0, 0);
            perform_step(500);
        }
        break;
    default:
        break;
    }
}

extern void backlight_set_left(const uint8_t r, const uint8_t g, const uint8_t b)
{
    assert(backlight.status == INITIALIZED);

    backlight.left.next.rgb.r = r;
    backlight.left.next.rgb.g = g;
    backlight.left.next.rgb.b = b;
    backlight.left.value.increment = 0;
}

extern void backlight_set_right(const uint8_t r, const uint8_t g, const uint8_t b)
{
    assert(backlight.status == INITIALIZED);

    backlight.right.next.rgb.r = r;
    backlight.right.next.rgb.g = g;
    backlight.right.next.rgb.b = b;
    backlight.right.value.increment = 0;
}

extern void backlight_morph_left(const uint8_t r, const uint8_t g, const uint8_t b)
{
    assert(backlight.status == INITIALIZED);

    backlight.left.next.rgb.r = r;
    backlight.left.next.rgb.g = g;
    backlight.left.next.rgb.b = b;
    backlight.left.value.increment = 1;
}

extern void backlight_morph_right(const uint8_t r, const uint8_t g, const uint8_t b)
{
    assert(backlight.status == INITIALIZED);

    backlight.right.next.rgb.r = r;
    backlight.right.next.rgb.g = g;
    backlight.right.next.rgb.b = b;
    backlight.right.value.increment = 1;
}

static void perform_step(const int _delay)
{
    static absolute_time_t timestamp = {0};
    absolute_time_t current_time = get_absolute_time();

    const uint64_t us_diff = to_us_since_boot(current_time) - to_us_since_boot(timestamp);
    if (us_diff < static_cast<uint64_t>(_delay) * 1000)
    {
        return;
    }
    timestamp = current_time;

    const int color_inc = 1;

    bool left_changed = false;
    if (backlight.left.next.value != backlight.left.curent.value)
    {
        left_changed = true;
        if (backlight.left.value.increment == 0)
        {
            backlight.left.curent.value = backlight.left.next.value;
        }
        else
        {
            if (backlight.left.curent.rgb.r < backlight.left.next.rgb.r)
            {
                backlight.left.curent.rgb.r = (backlight.left.curent.rgb.r < backlight.left.next.rgb.r) ? backlight.left.curent.rgb.r + color_inc : backlight.left.next.rgb.r;
            }
            else if (backlight.left.curent.rgb.r > backlight.left.next.rgb.r)
            {
                backlight.left.curent.rgb.r = (backlight.left.curent.rgb.r > backlight.left.next.rgb.r) ? backlight.left.curent.rgb.r - color_inc : backlight.left.next.rgb.r;
            }
            else
            {
                backlight.left.curent.rgb.r = backlight.left.next.rgb.r;
            }

            if (backlight.left.curent.rgb.g < backlight.left.next.rgb.g)
            {
                backlight.left.curent.rgb.g = (backlight.left.curent.rgb.g < backlight.left.next.rgb.g) ? backlight.left.curent.rgb.g + color_inc : backlight.left.next.rgb.g;
            }
            else if (backlight.left.curent.rgb.g > backlight.left.next.rgb.g)
            {
                backlight.left.curent.rgb.g = (backlight.left.curent.rgb.g > backlight.left.next.rgb.g) ? backlight.left.curent.rgb.g - color_inc : backlight.left.next.rgb.g;
            }
            else
            {
                backlight.left.curent.rgb.g = backlight.left.next.rgb.g;
            }

            if (backlight.left.curent.rgb.b < backlight.left.next.rgb.b)
            {
                backlight.left.curent.rgb.b = (backlight.left.curent.rgb.b < backlight.left.next.rgb.b) ? backlight.left.curent.rgb.b + color_inc : backlight.left.next.rgb.b;
            }
            else if (backlight.left.curent.rgb.b < backlight.left.next.rgb.b)
            {
                backlight.left.curent.rgb.b = (backlight.left.curent.rgb.b > backlight.left.next.rgb.b) ? backlight.left.curent.rgb.b - color_inc : backlight.left.next.rgb.b;
            }
            else
            {
                backlight.left.curent.rgb.b = backlight.left.next.rgb.b;
            }

            if (backlight.left.curent.rgb.r == backlight.left.next.rgb.r &&
                backlight.left.curent.rgb.g == backlight.left.next.rgb.g &&
                backlight.left.curent.rgb.b == backlight.left.next.rgb.b)
            {
                backlight.left.value.increment = 0;
            }
        }
    }

    bool right_changed = false;
    if (backlight.right.next.value != backlight.right.curent.value)
    {
        right_changed = true;
        if (backlight.right.value.increment == 0)
        {
            backlight.right.curent.value = backlight.right.next.value;
        }
        else
        {
            if (backlight.right.curent.rgb.r < backlight.right.next.rgb.r)
            {
                backlight.right.curent.rgb.r = (backlight.right.curent.rgb.r < backlight.right.next.rgb.r) ? backlight.right.curent.rgb.r + color_inc : backlight.right.next.rgb.r;
            }
            else if (backlight.right.curent.rgb.r > backlight.right.next.rgb.r)
            {
                backlight.right.curent.rgb.r = (backlight.right.curent.rgb.r > backlight.right.next.rgb.r) ? backlight.right.curent.rgb.r - color_inc : backlight.right.next.rgb.r;
            }
            else
            {
                backlight.right.curent.rgb.r = backlight.right.next.rgb.r;
            }

            if (backlight.right.curent.rgb.g < backlight.right.next.rgb.g)
            {
                backlight.right.curent.rgb.g = (backlight.right.curent.rgb.g < backlight.right.next.rgb.g) ? backlight.right.curent.rgb.g + color_inc : backlight.right.next.rgb.g;
            }
            else if (backlight.right.curent.rgb.g > backlight.right.next.rgb.g)
            {
                backlight.right.curent.rgb.g = (backlight.right.curent.rgb.g > backlight.right.next.rgb.g) ? backlight.right.curent.rgb.g - color_inc : backlight.right.next.rgb.g;
            }
            else
            {
                backlight.right.curent.rgb.g = backlight.right.next.rgb.g;
            }

            if (backlight.right.curent.rgb.b < backlight.right.next.rgb.b)
            {
                backlight.right.curent.rgb.b = (backlight.right.curent.rgb.b < backlight.right.next.rgb.b) ? backlight.right.curent.rgb.b + color_inc : backlight.right.next.rgb.b;
            }
            else if (backlight.right.curent.rgb.b < backlight.right.next.rgb.b)
            {
                backlight.right.curent.rgb.b = (backlight.right.curent.rgb.b > backlight.right.next.rgb.b) ? backlight.right.curent.rgb.b - color_inc : backlight.right.next.rgb.b;
            }
            else
            {
                backlight.right.curent.rgb.b = backlight.right.next.rgb.b;
            }

            if (backlight.right.curent.rgb.r == backlight.right.next.rgb.r &&
                backlight.right.curent.rgb.g == backlight.right.next.rgb.g &&
                backlight.right.curent.rgb.b == backlight.right.next.rgb.b)
            {
                backlight.right.value.increment = 0;
            }
        }
    }

    if (left_changed || right_changed)
    {
        backlight.middle.rgb.r = (backlight.left.curent.rgb.r + backlight.right.curent.rgb.r) / 2;
        backlight.middle.rgb.g = (backlight.left.curent.rgb.g + backlight.right.curent.rgb.g) / 2;
        backlight.middle.rgb.b = (backlight.left.curent.rgb.b + backlight.right.curent.rgb.b) / 2;

        board.backlight.put_value(backlight.left.curent);
        board.backlight.put_value(backlight.middle);
        board.backlight.put_value(backlight.right.curent);
    }
}

static void program_switch()
{
    static int program_id = 0;
    const int program_size = sizeof(program) / sizeof(program_t);

    if (backlight.left.next.value == backlight.left.curent.value &&
        backlight.right.next.value == backlight.right.curent.value)
    {
        backlight_morph_left(program[program_id].left.rgb.r, program[program_id].left.rgb.g, program[program_id].left.rgb.b);
        backlight_morph_right(program[program_id].right.rgb.r, program[program_id].right.rgb.g, program[program_id].right.rgb.b);

        program_id = ((program_id + 1) < program_size) ? program_id + 1 : 0;
    }
}
