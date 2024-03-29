/**
 * \file backlight3.cpp
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#include <assert.h>
#include <stdio.h>

#include "backlight3.hpp"
#include "backlight_color.hpp"
#include "backlight_settings.hpp"
#include "board_assembly.hpp"

namespace engine
{
    namespace backlight
    {
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
            Color curent;
            color_change_t value;
            Color next;
        } led_t;

        typedef struct
        {
            led_t left;
            led_t right;
            status_t status;
            PROGRAM program;
            PROGRAM next_program;
            uint64_t next_delay_ms;
        } backlight_t;

        typedef struct
        {
            Color left;
            Color right;
        } program_t;

        backlight_t backlight = {0};

        const program_t program[6] = {
            {.left = {.rgb = {0xff, 0x00, 0x00}}, .right = {.rgb = {0x00, 0xff, 0x00}}},
            {.left = {.rgb = {0xff, 0xff, 0x00}}, .right = {.rgb = {0x00, 0xff, 0xff}}},
            {.left = {.rgb = {0x00, 0xff, 0x00}}, .right = {.rgb = {0x00, 0x00, 0xff}}},
            {.left = {.rgb = {0x00, 0xff, 0xff}}, .right = {.rgb = {0xff, 0x00, 0xff}}},
            {.left = {.rgb = {0x00, 0x00, 0xff}}, .right = {.rgb = {0xff, 0x00, 0x00}}},
            {.left = {.rgb = {0xff, 0x00, 0xff}}, .right = {.rgb = {0xff, 0xff, 0x00}}},
        };

        int const BLINK_ALERT = engine::BacklightSetting::BLINK_ALERT_TIMEOUT;
        int const BLINK_MOUNT = engine::BacklightSetting::BLINK_MOUNT_TIMEOUT;
        int const BLINK_SUSPEND = engine::BacklightSetting::BLINK_SUSPEND_TIMEOUT;

        static void perform_step(const int _delay);
        static void program_switch();

        extern void initialize(void)
        {
            backlight.status = INITIALIZED;
        }

        extern void set_program(const PROGRAM _mode, const uint64_t _delay_ms)
        {
            assert(backlight.status == INITIALIZED);
            backlight.next_program = _mode;
            backlight.next_delay_ms = _delay_ms;
        }

        extern void perform(void)
        {
            assert(backlight.status == INITIALIZED);

            if (backlight.program != backlight.next_program)
            {
                static uint64_t timestamp = platform::board::assembly.soc.get_stopwatch();
                const uint64_t us_diff = platform::board::assembly.soc.get_stopwatch() - timestamp;
                if (us_diff > backlight.next_delay_ms * 1000)
                {
                    backlight.program = backlight.next_program;
                }
            }

            switch (backlight.program)
            {
            case PROGRAM::MEDIUM:
                perform_step(100);
                program_switch();
                break;
            case PROGRAM::SLOW:
                perform_step(500);
                program_switch();
                break;
            case PROGRAM::TURBO:
                perform_step(10);
                program_switch();
                break;
            case PROGRAM::ALERT:
                if (backlight.right.curent == engine::backlight::ALERT_COLOR)
                {
                    set_left(engine::backlight::BLACK_COLOR);
                    set_right(engine::backlight::BLACK_COLOR);
                }
                else
                {
                    set_left(engine::backlight::ALERT_COLOR);
                    set_right(engine::backlight::ALERT_COLOR);
                }
                perform_step(BLINK_ALERT);
                break;
            case PROGRAM::MOUNT:
                if (backlight.right.curent == engine::BacklightSetting::MOUNTED_BACKLIGHT_RIGHT)
                {
                    set_left(engine::BacklightSetting::MOUNTED_BACKLIGHT_RIGHT);
                    set_right(engine::BacklightSetting::MOUNTED_BACKLIGHT_LEFT);
                }
                else
                {
                    set_left(engine::BacklightSetting::MOUNTED_BACKLIGHT_LEFT);
                    set_right(engine::BacklightSetting::MOUNTED_BACKLIGHT_RIGHT);
                }
                perform_step(BLINK_MOUNT);
                break;
            case PROGRAM::SUSPEND:
                if (backlight.right.curent == engine::backlight::SUSPEND_COLOR)
                {
                    set_left(engine::backlight::BLACK_COLOR);
                    set_right(engine::backlight::BLACK_COLOR);
                }
                else
                {
                    set_left(engine::backlight::SUSPEND_COLOR);
                    set_right(engine::backlight::SUSPEND_COLOR);
                }
                perform_step(BLINK_SUSPEND);
                break;
            case PROGRAM::CONST:
                if (!(backlight.left.next.value == backlight.left.curent.value &&
                      backlight.right.next.value == backlight.right.curent.value))
                {
                    perform_step(10);
                }
                break;
            case PROGRAM::OFF:
                if (!(backlight.left.next.value == backlight.left.curent.value &&
                      backlight.right.next.value == backlight.right.curent.value))
                {
                    set_left(engine::backlight::BLACK_COLOR);
                    set_right(engine::backlight::BLACK_COLOR);
                    perform_step(500);
                }
                break;
            default:
                break;
            }
        }

        extern void set_left(const uint8_t r, const uint8_t g, const uint8_t b)
        {
            assert(backlight.status == INITIALIZED);

            backlight.left.next.rgb.r = r;
            backlight.left.next.rgb.g = g;
            backlight.left.next.rgb.b = b;
            backlight.left.value.increment = 0;
        }

        extern void set_right(const uint8_t r, const uint8_t g, const uint8_t b)
        {
            assert(backlight.status == INITIALIZED);

            backlight.right.next.rgb.r = r;
            backlight.right.next.rgb.g = g;
            backlight.right.next.rgb.b = b;
            backlight.right.value.increment = 0;
        }

        extern void morph_left(const uint8_t r, const uint8_t g, const uint8_t b)
        {
            assert(backlight.status == INITIALIZED);

            backlight.left.next.rgb.r = r;
            backlight.left.next.rgb.g = g;
            backlight.left.next.rgb.b = b;
            backlight.left.value.increment = 1;
        }

        extern void morph_right(const uint8_t r, const uint8_t g, const uint8_t b)
        {
            assert(backlight.status == INITIALIZED);

            backlight.right.next.rgb.r = r;
            backlight.right.next.rgb.g = g;
            backlight.right.next.rgb.b = b;
            backlight.right.value.increment = 1;
        }

        static void perform_step(const int _delay)
        {
            static uint64_t timestamp = platform::board::assembly.soc.get_stopwatch();
            const uint64_t current_time = platform::board::assembly.soc.get_stopwatch();
            if ((current_time - timestamp) < static_cast<uint64_t>(_delay) * 1000)
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
                    backlight.left.curent.value[0] = backlight.left.next.value[0];
                    backlight.left.curent.value[1] = backlight.left.next.value[1];
                    backlight.left.curent.value[2] = backlight.left.next.value[2];
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
                    backlight.right.curent.value[0] = backlight.right.next.value[0];
                    backlight.right.curent.value[1] = backlight.right.next.value[1];
                    backlight.right.curent.value[2] = backlight.right.next.value[2];
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
                platform::board::assembly.backlight.set_backlight(backlight.left.curent, backlight.right.curent);
            }
        }

        static void program_switch()
        {
            static int program_id = 0;
            const int program_size = sizeof(program) / sizeof(program_t);

            if (backlight.left.next == backlight.left.curent && backlight.right.next == backlight.right.curent)
            {
                morph_left(program[program_id].left);
                morph_right(program[program_id].right);

                program_id = ((program_id + 1) < program_size) ? program_id + 1 : 0;
            }
        }
    }
}
