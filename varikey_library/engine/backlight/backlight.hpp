// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: Three-channel backlight interface
// SPDX-FileType: SOURCE

#pragma once

#include <stdint.h>

#include "backlight_channel.hpp"
#include "backlight_program.hpp"
#include "backlight_settings.hpp"
#include "smartled_color.hpp"

namespace engine::backlight
{
    using Color = platform::hardware::smartled::Color;
    
    struct LightChannelControl
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
            Color current;
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

        static const int BLINK_ALERT = Settings::BLINK_ALERT_TIMEOUT;
        static const int BLINK_MOUNT = Settings::BLINK_MOUNT_TIMEOUT;
        static const int BLINK_SUSPEND = Settings::BLINK_SUSPEND_TIMEOUT;

        void initialize(void);
        void perform(void);

        void set_program(const PROGRAM, const uint64_t _delay_ms);

        void set_left(const uint8_t r, const uint8_t g, const uint8_t b);
        void set_right(const uint8_t r, const uint8_t g, const uint8_t b);

        void morph_left(const uint8_t r, const uint8_t g, const uint8_t b);
        void morph_right(const uint8_t r, const uint8_t g, const uint8_t b);

        inline void set_left(const Color &_color) { set_left(_color.rgb.r, _color.rgb.g, _color.rgb.b); }
        inline void set_right(const Color &_color) { set_right(_color.rgb.r, _color.rgb.g, _color.rgb.b); }
        inline void morph_left(const Color &_color) { morph_left(_color.rgb.r, _color.rgb.g, _color.rgb.b); }
        inline void morph_right(const Color &_color) { morph_right(_color.rgb.r, _color.rgb.g, _color.rgb.b); }

    private:
        void set_smartled(const Color &_left, const Color &_right);
        void perform_step(const int _delay);
        void program_switch();
    };

    extern void initialize(void);
    extern void set_program(const PROGRAM, const CHANNEL, const uint64_t _delay_ms);
    extern void set_program(const PROGRAM, const CHANNEL, const Color &, const Color &, const uint64_t _delay_ms);
    extern void perform(void);

}
