/**
 * \file keyboard.c
 * \author Koch, Roman (koch.roman@googlemail.com)
 * \brief
 *
 * @copyright Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 *
 */

#include <pico/time.h>

#include "tusb.h"

#include "backlight.h"
#include "display.h"
#include "keyboard.h"
#include "keyboard_keycode.h"
#include "macros.h"
#include "param_serial_number.h"
#include "temperature.h"
#include "usb_descriptors.h"

#define ROTARY_ENCODER_EVENTS_TIMEOUT_MAX_MS 200

#define _PRINT_EXTENDED_OUTPUT

extern void keyboard_perform(void)
{
    // Poll every 10ms
    static absolute_time_t timestamp = {0};
    absolute_time_t current_time = get_absolute_time();

    const uint64_t us_diff = current_time._private_us_since_boot - timestamp._private_us_since_boot;
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

extern void keyboard_handle_event(keypad_event_t const _event)
{
    if (tud_suspended())
    {
        tud_remote_wakeup();
    }

    if (!tud_hid_ready())
        return;

    if (_event.state == KEYPAD_STATE_PRESS)
    {
        static absolute_time_t timestamp = {0};
        absolute_time_t current_time = get_absolute_time();
        const float time_diff_ms = (current_time._private_us_since_boot - timestamp._private_us_since_boot) / 1000.0;
        timestamp = current_time;

#if defined(PRINT_EXTENDED_OUTPUT)
        printf("state:%d identifier:%d delay:%15f ms\n", _event.state, _event.identifier, time_diff_ms);
#endif

        uint8_t keycode[6] = {0};
        static keypad_event_identifier_t last_identifier = KEYPAD_UNDEFINED;

        switch (_event.identifier)
        {
        case KEYPAD_R0_C0:
            keycode[0] = KEYBOARD_1_LEFT;
            tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, keycode);
            break;
        case KEYPAD_R1_C0:
            keycode[0] = KEYBOARD_2_LEFT;
            tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, keycode);
            break;
        case KEYPAD_R2_C0:
            keycode[0] = KEYBOARD_3_LEFT;
            tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, keycode);
            break;
        case KEYPAD_R3_C0:
            keycode[0] = KEYBOARD_4_LEFT;
            tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, keycode);
            break;
        case KEYPAD_R4_C0:
            keycode[0] = KEYBOARD_5_LEFT;
            tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, keycode);
            break;
        case KEYPAD_R0_C1:
            keycode[0] = KEYBOARD_1_RIGHT;
            tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, keycode);
            break;
        case KEYPAD_R1_C1:
            keycode[0] = KEYBOARD_2_RIGHT;
            tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, keycode);
            break;
        case KEYPAD_R2_C1:
            keycode[0] = KEYBOARD_3_RIGHT;
            tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, keycode);
            break;
        case KEYPAD_R3_C1:
            keycode[0] = KEYBOARD_4_RIGHT;
            tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, keycode);
            break;
        case KEYPAD_R4_C1:
            keycode[0] = KEYBOARD_5_RIGHT;
            tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, keycode);
            break;
        case KEYPAD_A:
            if (last_identifier == KEYPAD_UNDEFINED)
            {
                last_identifier = KEYPAD_A;
            }
            else if (last_identifier == KEYPAD_A)
            {
            }
            else if (last_identifier == KEYPAD_B)
            {
                if (time_diff_ms < ROTARY_ENCODER_EVENTS_TIMEOUT_MAX_MS)
                {
                    keycode[0] = KEYBOARD_LEFT;
                    tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, keycode);
                }
                last_identifier = KEYPAD_UNDEFINED;
            }
            else
            {
                last_identifier = KEYPAD_UNDEFINED;
            }
            break;
        case KEYPAD_B:
            if (last_identifier == KEYPAD_UNDEFINED)
            {
                last_identifier = KEYPAD_B;
            }
            else if (last_identifier == KEYPAD_B)
            {
            }
            else if (last_identifier == KEYPAD_A)
            {
                if (time_diff_ms < ROTARY_ENCODER_EVENTS_TIMEOUT_MAX_MS)
                {
                    keycode[0] = KEYBOARD_RIGHT;
                    tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, keycode);
                }
                last_identifier = KEYPAD_UNDEFINED;
            }
            else
            {
                last_identifier = KEYPAD_UNDEFINED;
            }
            break;
        case KEYPAD_C:
            keycode[0] = KEYBOARD_PUSH;
            tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, keycode);
            break;
        case KEYPAD_UNDEFINED:
            break;
        default:
            break;
        }
    }
    else
    {
        tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, NULL);
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
        switch (report_id)
        {
        case REPORT_ID_SERIAL:
        {
            memcpy((char *)buffer, (char *)g_serial_number.value, bufsize);
            break;
        }
        case REPORT_ID_GADGET:
        {
            buffer[0] = 0xa9;
            break;
        }
        case REPORT_ID_UNIQUE:
        {
            memcpy((char *)buffer, (char *)&g_unique_key, bufsize);
            break;
        }
        case REPORT_ID_HARDWARE:
        {
            uint8_t tmp[12] = {0x0e, 0x00, 0x00, 0x00};
            memcpy((char *)buffer, (char *)tmp, sizeof(tmp));
            // strncpy((char *)buffer, (char *)g_serial_number.value, bufsize);
            break;
        }
        case REPORT_ID_VERSION:
        {
            uint8_t tmp[12] = {0x01, 0x00, 0x00, 0x00};
            memcpy((char *)buffer, (char *)tmp, sizeof(tmp));
            // strncpy((char *)buffer, (char *)g_serial_number.value, bufsize);
            break;
        }
        case REPORT_ID_TEMPERATURE:
        {
            uint32_t value = temperature_get() * 1000;
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
void tud_hid_set_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t const *buffer, uint16_t bufsize)
{
    (void)instance;

    if (report_type == HID_REPORT_TYPE_FEATURE)
    {
        if (report_id == REPORT_ID_SERIAL)
        {
            // strncpy(buffer, (char*)g_serial_number.value, bufsize);
        }
    }
    else if (report_type == HID_REPORT_TYPE_OUTPUT)
    {
        if (report_id == REPORT_ID_KEYBOARD)
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
        else if (report_id == REPORT_ID_CUSTOM)
        {
            if (bufsize < 1)
                return;

            uint8_t const command = buffer[0];

            if (command == KEYPAD_COMMAND_RESET)
            {
                /* todo: reset keypad */
            }
            else if (command == KEYPAD_COMMAND_POSITION)
            {
                uint8_t const lines = buffer[1];
                uint8_t const columns = buffer[2];
                display_set_cursor(lines, columns);
            }
            else if (command == KEYPAD_COMMAND_ICON)
            {
                uint8_t const image = buffer[1];
                switch (image)
                {
                case KEYPAD_ICON_FRAME:
                    display_draw(&FRAME);
                    break;
                case KEYPAD_ICON_LOGO:
                    display_draw(&LOGO);
                    break;
                case KEYPAD_ICON_HEART:
                    display_draw(&HEART);
                    break;
                default:
                    break;
                }
            }
            else if (command == KEYPAD_COMMAND_FONT_SIZE)
            {
                const uint8_t font_size = buffer[1];
                if (font_size == 1)
                {
                    display_set_font(FONT_SMALL);
                }
                else if (font_size == 2)
                {
                    display_set_font(FONT_BIG);
                }
                else if (font_size == 3)
                {
                    display_set_font(FONT_HUGE);
                }
                else
                {
                    display_set_font(FONT_SMALL);
                }
            }
            else if (command == KEYPAD_COMMAND_TEXT)
            {
                char *const text = (char *const)&buffer[1];
                display_print(text);
            }
            else if (command == KEYPAD_COMMAND_BACKLIGHT)
            {
                backlight_mode_t const mode = buffer[1];
                switch (mode)
                {
                case BACKLIGHT_PROGRAM_MEDIUM:
                    backlight_mode(BACKLIGHT_PROGRAM_MEDIUM, 0);
                    break;
                case BACKLIGHT_PROGRAM_SLOW:
                    backlight_mode(BACKLIGHT_PROGRAM_SLOW, 0);
                    break;
                case BACKLIGHT_PROGRAM_TURBO:
                    backlight_mode(BACKLIGHT_PROGRAM_TURBO, 0);
                    break;
                case BACKLIGHT_CONST:
                    backlight_mode(BACKLIGHT_CONST, 0);
                    break;
                case BACKLIGHT_NOT_MOUNTED:
                    backlight_mode(BACKLIGHT_NOT_MOUNTED, 0);
                    break;
                case BACKLIGHT_MOUNTED:
                    backlight_mode(BACKLIGHT_MOUNTED, 0);
                    break;
                case BACKLIGHT_SUSPENDED:
                    backlight_mode(BACKLIGHT_SUSPENDED, 0);
                    break;
                case BACKLIGHT_OFF:
                    backlight_mode(BACKLIGHT_OFF, 0);
                    break;
                }
            }
            else if (command == KEYPAD_COMMAND_CONFIG)
            {
                backlight_mode_t const mode = buffer[1];
            }
        }
    }
}
