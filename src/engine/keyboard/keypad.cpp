/**
 * \file keypad.cpp
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
#include "keyboard_type.hpp"
#include "keypad.hpp"
#include "keypad_backlight_command.hpp"
#include "keypad_display_command.hpp"
#include "macros.hpp"
#include "param_serial_number.hpp"
#include "revision.h"
#include "usb_descriptors.hpp"

#define ROTARY_ENCODER_EVENTS_TIMEOUT_MAX_MS 200

#define _PRINT_EXTENDED_OUTPUT

static void set_keyboard_state(uint8_t const kbd_leds)
{
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

static void set_font(uint8_t const *buffer)
{
    const engine::keypad::display::FONT font_size = static_cast<engine::keypad::display::FONT>(buffer[0]);
    switch (font_size)
    {
    case engine::keypad::display::FONT::SMALL:
        display_set_font(FONT_SIZE::FONT_SMALL);
        break;
    case engine::keypad::display::FONT::NORMAL:
        display_set_font(FONT_SIZE::FONT_NORMAL);
        break;
    case engine::keypad::display::FONT::BIG:
        display_set_font(FONT_SIZE::FONT_BIG);
        break;
    case engine::keypad::display::FONT::HUGE:
        display_set_font(FONT_SIZE::FONT_HUGE);
        break;
    case engine::keypad::display::FONT::SYMBOL:
        display_set_font(FONT_SIZE::FONT_SYMBOL);
        break;
    default:
        display_set_font(FONT_SIZE::FONT_SMALL);
        break;
    }
}

static void set_display_position(uint8_t const *buffer)
{
    uint8_t const lines = buffer[0];
    uint8_t const columns = buffer[1];
    display_set_cursor(lines, columns);
}

static void set_backlight(uint8_t const *buffer)
{
    const engine::keypad::backlight::COMMAND mode = static_cast<engine::keypad::backlight::COMMAND>(buffer[0]);
    switch (mode)
    {
    case engine::keypad::backlight::COMMAND::PROGRAM_MEDIUM:
        backlight_mode(BACKLIGHT_PROGRAM_MEDIUM, 0);
        break;
    case engine::keypad::backlight::COMMAND::PROGRAM_SLOW:
        backlight_mode(BACKLIGHT_PROGRAM_SLOW, 0);
        break;
    case engine::keypad::backlight::COMMAND::PROGRAM_TURBO:
        backlight_mode(BACKLIGHT_PROGRAM_TURBO, 0);
        break;
    case engine::keypad::backlight::COMMAND::CONST:
        backlight_mode(BACKLIGHT_CONST, 0);
        break;
    case engine::keypad::backlight::COMMAND::NOT_MOUNTED:
        backlight_mode(BACKLIGHT_NOT_MOUNTED, 0);
        break;
    case engine::keypad::backlight::COMMAND::MOUNTED:
        backlight_mode(BACKLIGHT_MOUNTED, 0);
        break;
    case engine::keypad::backlight::COMMAND::SUSPENDED:
        backlight_mode(BACKLIGHT_SUSPENDED, 0);
        break;
    case engine::keypad::backlight::COMMAND::OFF:
        backlight_mode(BACKLIGHT_OFF, 0);
        break;
    case engine::keypad::backlight::COMMAND::MORPH:
    {
        const uint8_t r = buffer[2];
        const uint8_t g = buffer[3];
        const uint8_t b = buffer[4];
        backlight_mode(BACKLIGHT_CONST, 0);
        backlight_morph_left(r, g, b);
        backlight_morph_right(r, g, b);
        break;
    }
    case engine::keypad::backlight::COMMAND::SET:
    {
        const uint8_t r = buffer[2];
        const uint8_t g = buffer[3];
        const uint8_t b = buffer[4];
        backlight_mode(BACKLIGHT_CONST, 0);
        backlight_set_left(r, g, b);
        backlight_set_right(r, g, b);
        break;
    }
    default:
        backlight_mode(BACKLIGHT_PROGRAM_MEDIUM, 0);
        break;
    }
}

static void display_print_message(uint8_t const *buffer)
{
    char *const text = (char *const)buffer;
    display_print(text);
}

static void draw_icon(uint8_t const *buffer)
{
    KEYPAD_ICON const image = static_cast<KEYPAD_ICON>(buffer[0]);
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

extern void keypad_perform(void)
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

extern void keypad_handle_event(engine::keypad::event_t const _event)
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
        case engine::keypad::event::IDENTIFIER::WHEEL_LEFT:
            if (last_identifier == engine::keypad::event::IDENTIFIER::UNDEFINED)
            {
                last_identifier = engine::keypad::event::IDENTIFIER::WHEEL_LEFT;
            }
            else if (last_identifier == engine::keypad::event::IDENTIFIER::WHEEL_LEFT)
            {
            }
            else if (last_identifier == engine::keypad::event::IDENTIFIER::WHEEL_RIGHT)
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
        case engine::keypad::event::IDENTIFIER::WHEEL_RIGHT:
            if (last_identifier == engine::keypad::event::IDENTIFIER::UNDEFINED)
            {
                last_identifier = engine::keypad::event::IDENTIFIER::WHEEL_RIGHT;
            }
            else if (last_identifier == engine::keypad::event::IDENTIFIER::WHEEL_RIGHT)
            {
            }
            else if (last_identifier == engine::keypad::event::IDENTIFIER::WHEEL_LEFT)
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
        case engine::keypad::event::IDENTIFIER::WHEEL_PRESS:
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

/**
 * \brief Invoked when received GET_REPORT control request
 *
 * Application must fill buffer report's content and return its length.
 *
 * \param instance
 * \param report_id
 * \param report_type
 * \param buffer
 * \param bufsize
 * \return uint16_t Return zero will cause the stack to STALL request
 */
uint16_t tud_hid_get_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t *buffer, uint16_t bufsize)
{
    (void)instance;

    if (report_type == HID_REPORT_TYPE_FEATURE)
    {
        switch (static_cast<platform::usb::REPORT_ID>(report_id))
        {
        case platform::usb::REPORT_ID::SERIAL:
        {
            memcpy((char *)buffer, (char *)g_serial_number.value, PARAMETER_SERIAL_NUMBER_SIZE);
            break;
        }
        case platform::usb::REPORT_ID::GADGET:
        {
            buffer[0] = 0xa9;
            break;
        }
        case platform::usb::REPORT_ID::UNIQUE:
        {
            serialize_long(g_unique_key, &buffer);
            break;
        }
        case platform::usb::REPORT_ID::HARDWARE:
        {
            uint8_t tmp[3] = {HARDWARE_IDENTIFIER, HARDWARE_NUMBER, HARDWARE_VARIANT};
            memcpy((char *)buffer, (char *)tmp, sizeof(tmp));
            break;
        }
        case platform::usb::REPORT_ID::VERSION:
        {
            uint8_t tmp[5] = {FIRMWARE_IDENTIFIER, HIBYTE(FIRMWARE_REVISION), LOBYTE(FIRMWARE_REVISION), HIBYTE(FIRMWARE_PATCH), LOBYTE(FIRMWARE_PATCH)};
            memcpy((char *)buffer, (char *)tmp, sizeof(tmp));
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

/**
 * \brief Invoked when received SET_REPORT control request or received data on OUT endpoint ( Report ID = 0, Type = 0 )
 *
 * \param instance
 * \param _report_id
 * \param report_type
 * \param buffer
 * \param bufsize
 */
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
            set_keyboard_state(kbd_leds);
        }
        else if (report_id == platform::usb::REPORT_ID::CUSTOM)
        {
            if (bufsize < 1)
                return;

            const platform::usb::KEYPAD_COMMAND command = static_cast<platform::usb::KEYPAD_COMMAND>(buffer[0]);
            const uint8_t *payload = &buffer[1];

            switch (command)
            {
            case platform::usb::KEYPAD_COMMAND::RESET:
                /* todo: reset keypad */
                break;
            case platform::usb::KEYPAD_COMMAND::POSITION:
                set_display_position(payload);
                break;
            case platform::usb::KEYPAD_COMMAND::ICON:
                draw_icon(payload);
                break;
            case platform::usb::KEYPAD_COMMAND::FONT_SIZE:
                set_font(payload);
                break;
            case platform::usb::KEYPAD_COMMAND::TEXT:
                display_print_message(payload);
                break;
            case platform::usb::KEYPAD_COMMAND::BACKLIGHT:
                set_backlight(payload);
                break;
            case platform::usb::KEYPAD_COMMAND::CONFIG:
                /* todo: config keypad */
                break;
            default:
                break;
            }
        }
    }
}
