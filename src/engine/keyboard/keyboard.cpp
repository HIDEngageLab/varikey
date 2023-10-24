/**
 * \file keyboard.cpp
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#include <pico/time.h>
#include <pico/types.h>

#include "tusb.h"

#include "backlight3.hpp"
#include "board.hpp"
#include "display.hpp"
#include "image_identifier.hpp"
#include "keyboard.hpp"
#include "keyboard_type.hpp"
#include "macros.hpp"
#include "param_serial_number.hpp"
#include "usb_descriptors.hpp"

#define ROTARY_ENCODER_EVENTS_TIMEOUT_MAX_MS 200

#define _PRINT_EXTENDED_OUTPUT

extern void keyboard_perform(void)
{
    // Poll every 10ms
    static absolute_time_t timestamp = {0};
    absolute_time_t current_time = get_absolute_time();

    const uint64_t us_diff = to_us_since_boot(current_time) - to_us_since_boot(timestamp);
    if (us_diff < 10 * 1000)
    {
        return;
    }
    timestamp = current_time;

    // Remote wakeup
    if (tud_suspended())
    {
        // Wake up host if we are in suspend mode
        // and REMOTE_WAKEUP feature is enabled by host
        tud_remote_wakeup();
    }
}

extern void keyboard_handle_event(engine::keypad::event_t const _event)
{
    if (tud_suspended())
    {
        tud_remote_wakeup();
    }

    if (!tud_hid_ready())
        return;

    if (_event.state == engine::keypad::event::STATE::PRESS)
    {
        static absolute_time_t timestamp = {0};
        absolute_time_t current_time = get_absolute_time();
        const float time_diff_ms = (to_us_since_boot(current_time) - to_us_since_boot(timestamp)) / 1000.0;
        timestamp = current_time;

#if defined(PRINT_EXTENDED_OUTPUT)
        printf("state:%d identifier:%d delay:%15f ms\n", _event.state, _event.identifier, time_diff_ms);
#endif

        uint8_t keycode[6] = {0};
        static engine::keypad::event::IDENTIFIER last_identifier = engine::keypad::event::IDENTIFIER::UNDEFINED;

        switch (_event.identifier)
        {
        case engine::keypad::event::IDENTIFIER::KEY_1:
            keycode[0] = static_cast<uint8_t>(engine::Keypad::KEYCODE::LEFT_1);
            tud_hid_keyboard_report(static_cast<uint8_t>(platform::usb::REPORT_ID::KEYBOARD), 0, keycode);
            break;
        case engine::keypad::event::IDENTIFIER::KEY_2:
            keycode[0] = static_cast<uint8_t>(engine::Keypad::KEYCODE::LEFT_2);
            tud_hid_keyboard_report(static_cast<uint8_t>(platform::usb::REPORT_ID::KEYBOARD), 0, keycode);
            break;
        case engine::keypad::event::IDENTIFIER::KEY_3:
            keycode[0] = static_cast<uint8_t>(engine::Keypad::KEYCODE::LEFT_3);
            tud_hid_keyboard_report(static_cast<uint8_t>(platform::usb::REPORT_ID::KEYBOARD), 0, keycode);
            break;
        case engine::keypad::event::IDENTIFIER::KEY_4:
            keycode[0] = static_cast<uint8_t>(engine::Keypad::KEYCODE::LEFT_4);
            tud_hid_keyboard_report(static_cast<uint8_t>(platform::usb::REPORT_ID::KEYBOARD), 0, keycode);
            break;
        case engine::keypad::event::IDENTIFIER::KEY_5:
            keycode[0] = static_cast<uint8_t>(engine::Keypad::KEYCODE::LEFT_5);
            tud_hid_keyboard_report(static_cast<uint8_t>(platform::usb::REPORT_ID::KEYBOARD), 0, keycode);
            break;
        case engine::keypad::event::IDENTIFIER::KEY_6:
            keycode[0] = static_cast<uint8_t>(engine::Keypad::KEYCODE::RIGHT_1);
            tud_hid_keyboard_report(static_cast<uint8_t>(platform::usb::REPORT_ID::KEYBOARD), 0, keycode);
            break;
        case engine::keypad::event::IDENTIFIER::KEY_7:
            keycode[0] = static_cast<uint8_t>(engine::Keypad::KEYCODE::RIGHT_2);
            tud_hid_keyboard_report(static_cast<uint8_t>(platform::usb::REPORT_ID::KEYBOARD), 0, keycode);
            break;
        case engine::keypad::event::IDENTIFIER::KEY_8:
            keycode[0] = static_cast<uint8_t>(engine::Keypad::KEYCODE::RIGHT_3);
            tud_hid_keyboard_report(static_cast<uint8_t>(platform::usb::REPORT_ID::KEYBOARD), 0, keycode);
            break;
        case engine::keypad::event::IDENTIFIER::KEY_9:
            keycode[0] = static_cast<uint8_t>(engine::Keypad::KEYCODE::RIGHT_4);
            tud_hid_keyboard_report(static_cast<uint8_t>(platform::usb::REPORT_ID::KEYBOARD), 0, keycode);
            break;
        case engine::keypad::event::IDENTIFIER::KEY_10:
            keycode[0] = static_cast<uint8_t>(engine::Keypad::KEYCODE::RIGHT_5);
            tud_hid_keyboard_report(static_cast<uint8_t>(platform::usb::REPORT_ID::KEYBOARD), 0, keycode);
            break;
        case engine::keypad::event::IDENTIFIER::KEY_11:
            if (last_identifier == engine::keypad::event::IDENTIFIER::UNDEFINED)
            {
                last_identifier = engine::keypad::event::IDENTIFIER::KEY_11;
            }
            else if (last_identifier == engine::keypad::event::IDENTIFIER::KEY_11)
            {
            }
            else if (last_identifier == engine::keypad::event::IDENTIFIER::KEY_12)
            {
                if (time_diff_ms < ROTARY_ENCODER_EVENTS_TIMEOUT_MAX_MS)
                {
                    keycode[0] = static_cast<uint8_t>(engine::Keypad::KEYCODE::LEFT);
                    tud_hid_keyboard_report(static_cast<uint8_t>(platform::usb::REPORT_ID::KEYBOARD), 0, keycode);
                }
                last_identifier = engine::keypad::event::IDENTIFIER::UNDEFINED;
            }
            else
            {
                last_identifier = engine::keypad::event::IDENTIFIER::UNDEFINED;
            }
            break;
        case engine::keypad::event::IDENTIFIER::KEY_12:
            if (last_identifier == engine::keypad::event::IDENTIFIER::UNDEFINED)
            {
                last_identifier = engine::keypad::event::IDENTIFIER::KEY_12;
            }
            else if (last_identifier == engine::keypad::event::IDENTIFIER::KEY_12)
            {
            }
            else if (last_identifier == engine::keypad::event::IDENTIFIER::KEY_11)
            {
                if (time_diff_ms < ROTARY_ENCODER_EVENTS_TIMEOUT_MAX_MS)
                {
                    keycode[0] = static_cast<uint8_t>(engine::Keypad::KEYCODE::RIGHT);
                    tud_hid_keyboard_report(static_cast<uint8_t>(platform::usb::REPORT_ID::KEYBOARD), 0, keycode);
                }
                last_identifier = engine::keypad::event::IDENTIFIER::UNDEFINED;
            }
            else
            {
                last_identifier = engine::keypad::event::IDENTIFIER::UNDEFINED;
            }
            break;
        case engine::keypad::event::IDENTIFIER::KEY_13:
            keycode[0] = static_cast<uint8_t>(engine::Keypad::KEYCODE::ENTER);
            tud_hid_keyboard_report(static_cast<uint8_t>(platform::usb::REPORT_ID::KEYBOARD), 0, keycode);
            break;
        case engine::keypad::event::IDENTIFIER::UNDEFINED:
            break;
        default:
            break;
        }
    }
    else
    {
        tud_hid_keyboard_report(static_cast<uint8_t>(platform::usb::REPORT_ID::KEYBOARD), 0, NULL);
    }
}

// Invoked when device is mounted
void tud_mount_cb(void)
{
    backlight_mode(BACKLIGHT_PROGRAM_TURBO, 0);
    backlight_mode(BACKLIGHT_MOUNTED, 15000);
}

// Invoked when device is unmounted
void tud_umount_cb(void)
{
    backlight_mode(BACKLIGHT_NOT_MOUNTED, 0);
}

// Invoked when usb bus is suspended
// remote_wakeup_en : if host allow us  to perform remote wakeup
// Within 7ms, device must draw an average of current less than 2.5 mA from bus
void tud_suspend_cb(bool remote_wakeup_en)
{
    (void)remote_wakeup_en;

#if defined(PRINT_EXTENDED_OUTPUT)
    printf("tud_suspend_cb\n");
    printf("remote_wakeup_en 0x%x\n", remote_wakeup_en);
#endif

    backlight_mode(BACKLIGHT_SUSPENDED, 0);
}

// Invoked when usb bus is resumed
void tud_resume_cb(void)
{
    backlight_mode(BACKLIGHT_PROGRAM_TURBO, 0);
    backlight_mode(BACKLIGHT_MOUNTED, 15000);
}

// Invoked when sent REPORT successfully to host
// Application can use this to send the next report
// Note: For composite reports, report[0] is report ID
void tud_hid_report_complete_cb(uint8_t instance, uint8_t const *report, uint16_t len)
{
    (void)instance;
    (void)len;

#if defined(PRINT_EXTENDED_OUTPUT)
    printf("tud_hid_report_complete_cb\n");
    for (int i = 0; i < len; ++i)
    {
        printf("0x%x\n", report[i]);
    }
    printf("\n");
#endif
}

// Invoked when received GET_REPORT control request
// Application must fill buffer report's content and return its length.
// Return zero will cause the stack to STALL request
uint16_t tud_hid_get_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t *buffer, uint16_t bufsize)
{
    (void)instance;

    if (report_type == HID_REPORT_TYPE_FEATURE)
    {
        switch (static_cast<platform::usb::REPORT_ID>(report_id))
        {
        case platform::usb::REPORT_ID::SERIAL:
        {
            memcpy((char *)buffer, (char *)g_serial_number.value, bufsize);
            break;
        }
        case platform::usb::REPORT_ID::GADGET:
        {
            buffer[0] = 0xa9;
            break;
        }
        case platform::usb::REPORT_ID::UNIQUE:
        {
            memcpy((char *)buffer, (char *)&g_unique_key, bufsize);
            break;
        }
        case platform::usb::REPORT_ID::HARDWARE:
        {
            uint8_t tmp[12] = {0x0e, 0x00, 0x00, 0x00};
            memcpy((char *)buffer, (char *)tmp, sizeof(tmp));
            // strncpy((char *)buffer, (char *)g_serial_number.value, bufsize);
            break;
        }
        case platform::usb::REPORT_ID::VERSION:
        {
            uint8_t tmp[12] = {0x01, 0x00, 0x00, 0x00};
            memcpy((char *)buffer, (char *)tmp, sizeof(tmp));
            // strncpy((char *)buffer, (char *)g_serial_number.value, bufsize);
            break;
        }
        case platform::usb::REPORT_ID::TEMPERATURE:
        {
            uint32_t value = board.soc.temperature.get_value() * 1000;
            memcpy((char *)buffer, (char *)&value, sizeof(uint32_t));
            break;
        }
        default:
            break;
        }
    }

#if defined(PRINT_EXTENDED_OUTPUT)
    printf("tud_hid_get_report_cb\n");

    printf("report_id 0x%x\n", report_id);
    printf("report_type 0x%x\n", report_type);
    for (int i = 0; i < reqlen; ++i)
    {
        printf("0x%x\n", buffer[i]);
    }
    printf("\n");
#endif

    return bufsize;
}

// Invoked when received SET_REPORT control request or
// received data on OUT endpoint ( Report ID = 0, Type = 0 )
void tud_hid_set_report_cb(uint8_t instance, uint8_t _report_id, hid_report_type_t report_type, uint8_t const *buffer, uint16_t bufsize)
{
    (void)instance;

    platform::usb::REPORT_ID report_id = static_cast<platform::usb::REPORT_ID>(_report_id);

    if (report_type == HID_REPORT_TYPE_FEATURE)
    {
        if (report_id == platform::usb::REPORT_ID::SERIAL)
        {
            // strncpy(buffer, (char*)g_serial_number.value, bufsize);
        }
    }
    else if (report_type == HID_REPORT_TYPE_OUTPUT)
    {
        if (report_id == platform::usb::REPORT_ID::KEYBOARD)
        {
            // bufsize should be (at least) 1
            if (bufsize < 1)
                return;

            uint8_t const kbd_leds = buffer[0];

            if (kbd_leds & KEYBOARD_LED_CAPSLOCK)
            {
                backlight_mode(BACKLIGHT_PROGRAM_TURBO, 0);
            }
            else if (kbd_leds & KEYBOARD_LED_NUMLOCK)
            {
                backlight_mode(BACKLIGHT_PROGRAM_MEDIUM, 0);
            }
            else
            {
                backlight_mode(BACKLIGHT_PROGRAM_TURBO, 0);
                backlight_mode(BACKLIGHT_MOUNTED, 15000);
            }
        }
        else if (report_id == platform::usb::REPORT_ID::CUSTOM)
        {
            if (bufsize < 1)
                return;

            const platform::usb::KEYPAD_COMMAND command = static_cast<platform::usb::KEYPAD_COMMAND>(buffer[0]);

            if (command == platform::usb::KEYPAD_COMMAND::RESET)
            {
                /* todo: reset keypad */
            }
            else if (command == platform::usb::KEYPAD_COMMAND::POSITION)
            {
                uint8_t const lines = buffer[1];
                uint8_t const columns = buffer[2];
                display_set_cursor(lines, columns);
            }
            else if (command == platform::usb::KEYPAD_COMMAND::ICON)
            {
                KEYPAD_ICON const image = static_cast<KEYPAD_ICON>(buffer[1]);
                switch (image)
                {
                case KEYPAD_ICON::KEYPAD_ICON_FRAME:
                    display_draw(KEYPAD_ICON::KEYPAD_ICON_FRAME);
                    break;
                case KEYPAD_ICON::KEYPAD_ICON_VARIKEY_LOGO:
                    display_draw(KEYPAD_ICON::KEYPAD_ICON_VARIKEY_LOGO);
                    break;
                case KEYPAD_ICON::KEYPAD_ICON_GOSSENMETRAWATT_LOGO:
                    display_draw(KEYPAD_ICON::KEYPAD_ICON_GOSSENMETRAWATT_LOGO);
                    break;
                case KEYPAD_ICON::KEYPAD_ICON_HEART:
                    display_draw(KEYPAD_ICON::KEYPAD_ICON_HEART);
                    break;
                default:
                    break;
                }
            }
            else if (command == platform::usb::KEYPAD_COMMAND::FONT_SIZE)
            {
                const uint8_t font_size = buffer[1];
                if (font_size == 1)
                {
                    display_set_font(FONT_SIZE::FONT_SMALL);
                }
                else if (font_size == 2)
                {
                    display_set_font(FONT_SIZE::FONT_NORMAL);
                }
                else if (font_size == 3)
                {
                    display_set_font(FONT_SIZE::FONT_BIG);
                }
                else if (font_size == 4)
                {
                    display_set_font(FONT_SIZE::FONT_HUGE);
                }
                else if (font_size == 5)
                {
                    display_set_font(FONT_SIZE::FONT_SYMBOL);
                }
                else
                {
                    display_set_font(FONT_SIZE::FONT_SMALL);
                }
            }
            else if (command == platform::usb::KEYPAD_COMMAND::TEXT)
            {
                char *const text = (char *const)&buffer[1];
                display_print(text);
            }
            else if (command == platform::usb::KEYPAD_COMMAND::BACKLIGHT)
            {
                const int mode = buffer[1];
                switch (mode)
                {
                case 1:
                    backlight_mode(BACKLIGHT_PROGRAM_MEDIUM, 0);
                    break;
                case 2:
                    backlight_mode(BACKLIGHT_PROGRAM_SLOW, 0);
                    break;
                case 3:
                    backlight_mode(BACKLIGHT_PROGRAM_TURBO, 0);
                    break;
                case 4:
                    backlight_mode(BACKLIGHT_CONST, 0);
                    break;
                case 5:
                    backlight_mode(BACKLIGHT_NOT_MOUNTED, 0);
                    break;
                case 6:
                    backlight_mode(BACKLIGHT_MOUNTED, 0);
                    break;
                case 7:
                    backlight_mode(BACKLIGHT_SUSPENDED, 0);
                    break;
                case 8:
                    backlight_mode(BACKLIGHT_OFF, 0);
                    break;
                case 0xaa:
                {
                    const uint8_t r = buffer[2];
                    const uint8_t g = buffer[3];
                    const uint8_t b = buffer[4];
                    backlight_mode(BACKLIGHT_CONST, 0);
                    // backlight_set_left(r, g, b);
                    // backlight_set_right(r, g, b);
                    backlight_morph_left(r, g, b);
                    backlight_morph_right(r, g, b);
                    break;
                }
                default:
                    backlight_mode(BACKLIGHT_PROGRAM_MEDIUM, 0);
                    break;
                }
            }
            else if (command == platform::usb::KEYPAD_COMMAND::CONFIG)
            {
                // backlight_mode_t const mode = buffer[1];
            }
        }
    }
}
