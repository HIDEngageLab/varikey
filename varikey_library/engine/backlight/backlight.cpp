// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: Three-channel backlight implementation
// SPDX-FileType: SOURCE

#include <assert.h>
#include <stdio.h>

#include "backlight.hpp"
#include "backlight_color.hpp"
#include "board_assembly.hpp"
#include "smartled_color.hpp"

namespace engine::backlight
{
    void LightChannelControl::initialize(void)
    {
        backlight.status = INITIALIZED;
    }

    void LightChannelControl::set_program(const PROGRAM _mode, const uint64_t _delay_ms)
    {
        assert(backlight.status == INITIALIZED);
        backlight.next_program = _mode;
        backlight.next_delay_ms = _delay_ms;
    }

    void LightChannelControl::perform(void)
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
            if (backlight.right.current == engine::backlight::ALERT_COLOR)
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
            if (backlight.right.current == Settings::MOUNTED_BACKLIGHT_RIGHT)
            {
                set_left(Settings::MOUNTED_BACKLIGHT_RIGHT);
                set_right(Settings::MOUNTED_BACKLIGHT_LEFT);
            }
            else
            {
                set_left(Settings::MOUNTED_BACKLIGHT_LEFT);
                set_right(Settings::MOUNTED_BACKLIGHT_RIGHT);
            }
            perform_step(BLINK_MOUNT);
            break;
        case PROGRAM::SUSPEND:
            if (backlight.right.current == engine::backlight::SUSPEND_COLOR)
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
            if (!(backlight.left.next == backlight.left.current &&
                  backlight.right.next == backlight.right.current))
            {
                perform_step(10);
            }
            break;
        case PROGRAM::OFF:
            if (!(backlight.left.next == backlight.left.current &&
                  backlight.right.next == backlight.right.current))
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

    void LightChannelControl::set_left(const uint8_t r, const uint8_t g, const uint8_t b)
    {
        assert(backlight.status == INITIALIZED);

        backlight.left.next.rgb.r = r;
        backlight.left.next.rgb.g = g;
        backlight.left.next.rgb.b = b;
        backlight.left.value.increment = 0;
    }

    void LightChannelControl::set_right(const uint8_t r, const uint8_t g, const uint8_t b)
    {
        assert(backlight.status == INITIALIZED);

        backlight.right.next.rgb.r = r;
        backlight.right.next.rgb.g = g;
        backlight.right.next.rgb.b = b;
        backlight.right.value.increment = 0;
    }

    void LightChannelControl::morph_left(const uint8_t r, const uint8_t g, const uint8_t b)
    {
        assert(backlight.status == INITIALIZED);

        backlight.left.next.rgb.r = r;
        backlight.left.next.rgb.g = g;
        backlight.left.next.rgb.b = b;
        backlight.left.value.increment = 1;
    }

    void LightChannelControl::morph_right(const uint8_t r, const uint8_t g, const uint8_t b)
    {
        assert(backlight.status == INITIALIZED);

        backlight.right.next.rgb.r = r;
        backlight.right.next.rgb.g = g;
        backlight.right.next.rgb.b = b;
        backlight.right.value.increment = 1;
    }

    void LightChannelControl::set_smartled(const Color &_left, const Color &_right)
    {
        constexpr float brightness_front = 0.25f;
        constexpr float brightness_back = 0.25f;

        constexpr size_t backlight_count = platform::hardware::Backlight::LED_COUNT;
        static_assert(backlight_count >= 2, "Need at least two LEDs.");

        Color backlight_colors[backlight_count];

        for (size_t i = 0; i < backlight_count; ++i)
        {
            float t = static_cast<float>(i) / (backlight_count - 1); // t ∈ [0, 1]

            backlight_colors[i].rgb.r = static_cast<uint8_t>((_left.rgb.r + t * (_right.rgb.r - _left.rgb.r)) * brightness_back);
            backlight_colors[i].rgb.g = static_cast<uint8_t>((_left.rgb.g + t * (_right.rgb.g - _left.rgb.g)) * brightness_back);
            backlight_colors[i].rgb.b = static_cast<uint8_t>((_left.rgb.b + t * (_right.rgb.b - _left.rgb.b)) * brightness_back);
        }
        platform::board::assembly.backlight.set_led_sequence<platform::hardware::Backlight::Mapper>(backlight_colors);

        constexpr size_t frontlight_count = platform::hardware::Frontlight::LED_COUNT;
        static_assert(frontlight_count >= 2, "Need at least two LEDs.");

        Color frontlight_colors[frontlight_count];
        for (size_t i = 0; i < frontlight_count; ++i)
        {
            float t = static_cast<float>(i) / (frontlight_count - 1); // t ∈ [0, 1]

            frontlight_colors[i].rgb.r = static_cast<uint8_t>((_left.rgb.r + t * (_right.rgb.r - _left.rgb.r)) * brightness_front);
            frontlight_colors[i].rgb.g = static_cast<uint8_t>((_left.rgb.g + t * (_right.rgb.g - _left.rgb.g)) * brightness_front);
            frontlight_colors[i].rgb.b = static_cast<uint8_t>((_left.rgb.b + t * (_right.rgb.b - _left.rgb.b)) * brightness_front);
        }
        platform::board::assembly.frontlight.set_led_sequence<platform::hardware::Frontlight::Mapper>(frontlight_colors);
    }

    void LightChannelControl::perform_step(const int _delay)
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
        if (backlight.left.next != backlight.left.current)
        {
            left_changed = true;
            if (backlight.left.value.increment == 0)
            {
                backlight.left.current.value[0] = backlight.left.next.value[0];
                backlight.left.current.value[1] = backlight.left.next.value[1];
                backlight.left.current.value[2] = backlight.left.next.value[2];
            }
            else
            {
                if (backlight.left.current.rgb.r < backlight.left.next.rgb.r)
                {
                    backlight.left.current.rgb.r = (backlight.left.current.rgb.r < backlight.left.next.rgb.r) ? backlight.left.current.rgb.r + color_inc : backlight.left.next.rgb.r;
                }
                else if (backlight.left.current.rgb.r > backlight.left.next.rgb.r)
                {
                    backlight.left.current.rgb.r = (backlight.left.current.rgb.r > backlight.left.next.rgb.r) ? backlight.left.current.rgb.r - color_inc : backlight.left.next.rgb.r;
                }
                else
                {
                    backlight.left.current.rgb.r = backlight.left.next.rgb.r;
                }

                if (backlight.left.current.rgb.g < backlight.left.next.rgb.g)
                {
                    backlight.left.current.rgb.g = (backlight.left.current.rgb.g < backlight.left.next.rgb.g) ? backlight.left.current.rgb.g + color_inc : backlight.left.next.rgb.g;
                }
                else if (backlight.left.current.rgb.g > backlight.left.next.rgb.g)
                {
                    backlight.left.current.rgb.g = (backlight.left.current.rgb.g > backlight.left.next.rgb.g) ? backlight.left.current.rgb.g - color_inc : backlight.left.next.rgb.g;
                }
                else
                {
                    backlight.left.current.rgb.g = backlight.left.next.rgb.g;
                }

                if (backlight.left.current.rgb.b < backlight.left.next.rgb.b)
                {
                    backlight.left.current.rgb.b = (backlight.left.current.rgb.b < backlight.left.next.rgb.b) ? backlight.left.current.rgb.b + color_inc : backlight.left.next.rgb.b;
                }
                else if (backlight.left.current.rgb.b > backlight.left.next.rgb.b)
                {
                    backlight.left.current.rgb.b = (backlight.left.current.rgb.b > backlight.left.next.rgb.b) ? backlight.left.current.rgb.b - color_inc : backlight.left.next.rgb.b;
                }
                else
                {
                    backlight.left.current.rgb.b = backlight.left.next.rgb.b;
                }

                if (backlight.left.current.rgb.r == backlight.left.next.rgb.r &&
                    backlight.left.current.rgb.g == backlight.left.next.rgb.g &&
                    backlight.left.current.rgb.b == backlight.left.next.rgb.b)
                {
                    backlight.left.value.increment = 0;
                }
            }
        }

        bool right_changed = false;
        if (backlight.right.next != backlight.right.current)
        {
            right_changed = true;
            if (backlight.right.value.increment == 0)
            {
                backlight.right.current.value[0] = backlight.right.next.value[0];
                backlight.right.current.value[1] = backlight.right.next.value[1];
                backlight.right.current.value[2] = backlight.right.next.value[2];
            }
            else
            {
                if (backlight.right.current.rgb.r < backlight.right.next.rgb.r)
                {
                    backlight.right.current.rgb.r = (backlight.right.current.rgb.r < backlight.right.next.rgb.r) ? backlight.right.current.rgb.r + color_inc : backlight.right.next.rgb.r;
                }
                else if (backlight.right.current.rgb.r > backlight.right.next.rgb.r)
                {
                    backlight.right.current.rgb.r = (backlight.right.current.rgb.r > backlight.right.next.rgb.r) ? backlight.right.current.rgb.r - color_inc : backlight.right.next.rgb.r;
                }
                else
                {
                    backlight.right.current.rgb.r = backlight.right.next.rgb.r;
                }

                if (backlight.right.current.rgb.g < backlight.right.next.rgb.g)
                {
                    backlight.right.current.rgb.g = (backlight.right.current.rgb.g < backlight.right.next.rgb.g) ? backlight.right.current.rgb.g + color_inc : backlight.right.next.rgb.g;
                }
                else if (backlight.right.current.rgb.g > backlight.right.next.rgb.g)
                {
                    backlight.right.current.rgb.g = (backlight.right.current.rgb.g > backlight.right.next.rgb.g) ? backlight.right.current.rgb.g - color_inc : backlight.right.next.rgb.g;
                }
                else
                {
                    backlight.right.current.rgb.g = backlight.right.next.rgb.g;
                }

                if (backlight.right.current.rgb.b < backlight.right.next.rgb.b)
                {
                    backlight.right.current.rgb.b = (backlight.right.current.rgb.b < backlight.right.next.rgb.b) ? backlight.right.current.rgb.b + color_inc : backlight.right.next.rgb.b;
                }
                else if (backlight.right.current.rgb.b > backlight.right.next.rgb.b)
                {
                    backlight.right.current.rgb.b = (backlight.right.current.rgb.b > backlight.right.next.rgb.b) ? backlight.right.current.rgb.b - color_inc : backlight.right.next.rgb.b;
                }
                else
                {
                    backlight.right.current.rgb.b = backlight.right.next.rgb.b;
                }

                if (backlight.right.current.rgb.r == backlight.right.next.rgb.r &&
                    backlight.right.current.rgb.g == backlight.right.next.rgb.g &&
                    backlight.right.current.rgb.b == backlight.right.next.rgb.b)
                {
                    backlight.right.value.increment = 0;
                }
            }
        }

        if (left_changed || right_changed)
        {
            set_smartled(backlight.left.current, backlight.right.current);
        }
    }

    void LightChannelControl::program_switch()
    {
        static int program_id = 0;
        const int program_size = sizeof(program) / sizeof(program_t);

        if (backlight.left.next == backlight.left.current && backlight.right.next == backlight.right.current)
        {
            morph_left(program[program_id].left);
            morph_right(program[program_id].right);

            program_id = ((program_id + 1) < program_size) ? program_id + 1 : 0;
        }
    }

    namespace
    {
        LightChannelControl front_channel_control;
        LightChannelControl back_channel_control;
    }

    extern void initialize(void)
    {
        front_channel_control.initialize();
        back_channel_control.initialize();
    }

    extern void set_program(const PROGRAM _program, const CHANNEL _channel, const uint64_t _delay_ms)
    {
        assert(_channel != CHANNEL::UNDEFINED);

        if (_channel == CHANNEL::FRONTLIGHT)
        {
            front_channel_control.set_program(_program, _delay_ms);
        }
        else if (_channel == CHANNEL::BACKLIGHT)
        {
            back_channel_control.set_program(_program, _delay_ms);
        }
        else
        {
            assert(false && "Invalid channel specified");
        }
    }

    extern void set_program(const PROGRAM _program, const CHANNEL _channel, const Color &_left, const Color &_right, const uint64_t _delay_ms)
    {
        assert(_channel != CHANNEL::UNDEFINED);

        if (_channel == CHANNEL::FRONTLIGHT)
        {
            front_channel_control.set_left(_left);
            front_channel_control.set_right(_right);
            front_channel_control.set_program(_program, _delay_ms);
        }
        else if (_channel == CHANNEL::BACKLIGHT)
        {
            back_channel_control.set_left(_left);
            back_channel_control.set_right(_right);
            back_channel_control.set_program(_program, _delay_ms);
        }
        else
        {
            assert(false && "Invalid channel specified");
        }
    }

    extern void perform(void)
    {
        front_channel_control.perform();
        back_channel_control.perform();
    }

}
