/**
 * \file hid_handler.cpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#include <tusb.h>

#include "backlight_color.hpp"
#include "board_assembly.hpp"
#include "engine_event_handler.hpp"
#include "engine_gpio.hpp"
#include "hid_report.hpp"
#include "registry_defines.hpp"
#include "usb_descriptors.hpp"

namespace engine
{
    namespace hid
    {
        payload::gpio::content_t pin_request;
        payload::parameter::content_t parameter_request;

        extern void set_report_handler(const uint8_t _identifier, const const_chunk_t &_buffer)
        {
            set_report_t set_report;
            set_report.command = static_cast<platform::usb::COMMAND>(_identifier);

            if (set_report.command == platform::usb::COMMAND::KEYBOARD)
            {
                const uint8_t led_flags = _buffer.space[0];

                if ((led_flags & 0x01) == 0x01)
                    engine::keypad::enable_nums(true);
                else
                    engine::keypad::enable_nums(false);

                if ((led_flags & 0x02) == 0x02)
                    engine::keypad::enable_cups(true);
                else
                    engine::keypad::enable_cups(false);

                if ((led_flags & 0x04) == 0x04)
                    engine::keypad::enable_scroll(true);
                else
                    engine::keypad::enable_scroll(false);
            }
            else if (set_report.command == platform::usb::COMMAND::MOUSE)
            {
                /* do nothing */
            }
            else if (set_report.command == platform::usb::COMMAND::CUSTOM)
            {
                set_report.deserialize(_buffer);

                switch (set_report.report)
                {
                case SET_REPORT::BACKLIGHT:
                    using PROGRAM = engine::backlight::MODE;
                    if (set_report.backlight.program == PROGRAM::SET ||
                        set_report.backlight.program == PROGRAM::MORPH)
                    {
                        const handler::event_t event = {
                            .identifier = payload::IDENTIFIER::BACKLIGHT,
                            .backlight = {
                                .program = set_report.backlight.program,
                                .color_left = {.rgb = {
                                                   .r = set_report.backlight.color_left.rgb.r,
                                                   .g = set_report.backlight.color_left.rgb.g,
                                                   .b = set_report.backlight.color_left.rgb.b,
                                               }},
                                .color_right = {.rgb = {
                                                    .r = set_report.backlight.color_right.rgb.r,
                                                    .g = set_report.backlight.color_right.rgb.g,
                                                    .b = set_report.backlight.color_right.rgb.b,
                                                }},
                            }};
                        handler::event_queue.push(event);
                    }
                    else
                    {
                        const handler::event_t event = {
                            .identifier = payload::IDENTIFIER::BACKLIGHT,
                            .backlight = {
                                .program = set_report.backlight.program,
                                .color_left = {0},
                                .color_right = {0},
                            }};
                        handler::event_queue.push(event);
                    }
                    break;
                case SET_REPORT::DISPLAY:
                    switch (set_report.display.function)
                    {
                    case payload::display::FUNCTION::CLEAN:
                    {
                        const handler::event_t event = {
                            .identifier = payload::IDENTIFIER::DISPLAY,
                            .display = {
                                .function = payload::display::FUNCTION::CLEAN,
                            }};
                        handler::event_queue.push(event);
                        break;
                    }
                    case payload::display::FUNCTION::FONT:
                    {
                        const handler::event_t event = {
                            .identifier = payload::IDENTIFIER::DISPLAY,
                            .display = {
                                .function = payload::display::FUNCTION::FONT,
                                .font = set_report.display.font,
                            }};
                        handler::event_queue.push(event);
                        break;
                    }
                    case payload::display::FUNCTION::ICON:
                    {
                        const handler::event_t event = {
                            .identifier = payload::IDENTIFIER::DISPLAY,
                            .display = {
                                .function = payload::display::FUNCTION::ICON,
                                .icon = set_report.display.icon,
                            }};
                        handler::event_queue.push(event);
                        break;
                    }
                    case payload::display::FUNCTION::POSITION:
                    {
                        const handler::event_t event = {
                            .identifier = payload::IDENTIFIER::DISPLAY,
                            .display = {
                                .function = payload::display::FUNCTION::POSITION,
                                .position = {
                                    .line = set_report.display.position.line,
                                    .column = set_report.display.position.column,
                                }}};
                        handler::event_queue.push(event);
                        break;
                    }
                    case payload::display::FUNCTION::TEXT:
                    {
                        handler::event_t event = {
                            .identifier = payload::IDENTIFIER::DISPLAY,
                            .display = {
                                .function = payload::display::FUNCTION::TEXT,
                            }};
                        const uint8_t length = strnlen((const char *)set_report.display.text,
                                                       (size_t)payload::display::MESSAGE_SIZE - 1);
                        memcpy(event.display.text, set_report.display.text, length);
                        event.display.text[length] = '\0';
                        handler::event_queue.push(event);
                        break;
                    }
                    default:
                        break;
                    }
                    break;
                case SET_REPORT::GADGET:
                    switch (set_report.gadget.command)
                    {
                    case payload::gadget::COMMAND::MOUNT:
                    {
                        const handler::event_t event = {
                            .identifier = payload::IDENTIFIER::GADGET,
                            .gadget = {
                                .command = payload::gadget::COMMAND::MOUNT,
                            }};
                        handler::event_queue.push(event);
                        break;
                    }
                    case payload::gadget::COMMAND::RESUME:
                    {
                        const handler::event_t event = {
                            .identifier = payload::IDENTIFIER::GADGET,
                            .gadget = {
                                .command = payload::gadget::COMMAND::RESUME,
                            }};
                        handler::event_queue.push(event);
                        break;
                    }
                    case payload::gadget::COMMAND::SUSPEND:
                    {
                        const handler::event_t event = {
                            .identifier = payload::IDENTIFIER::GADGET,
                            .gadget = {
                                .command = payload::gadget::COMMAND::SUSPEND,
                            }};
                        handler::event_queue.push(event);
                        break;
                    }
                    case payload::gadget::COMMAND::UNMOUNT:
                    {
                        const handler::event_t event = {
                            .identifier = payload::IDENTIFIER::GADGET,
                            .gadget = {
                                .command = payload::gadget::COMMAND::UNMOUNT,
                            }};
                        handler::event_queue.push(event);
                        break;
                    }
                    default:
                        break;
                    }
                    break;
                case SET_REPORT::GPIO:
                    switch (set_report.gpio.function)
                    {
                    case engine::payload::gpio::FUNCTION::DISABLE:
                        engine::gpio::enable_event(false);
                        break;
                    case engine::payload::gpio::FUNCTION::ENABLE:
                        engine::gpio::enable_event(true);
                        break;
                    case engine::payload::gpio::FUNCTION::DIRECTION_GET:
                        pin_request.function = set_report.gpio.function;
                        pin_request.identifier = set_report.gpio.identifier;
                        break;
                    case engine::payload::gpio::FUNCTION::DIRECTION_SET:
                        engine::gpio::set_direction(set_report.gpio.identifier, set_report.gpio.direction);
                        break;
                    case engine::payload::gpio::FUNCTION::LEVEL_GET:
                        pin_request.function = set_report.gpio.function;
                        pin_request.identifier = set_report.gpio.identifier;
                        break;
                    case engine::payload::gpio::FUNCTION::LEVEL_SET:
                        engine::gpio::set_value(set_report.gpio.identifier, set_report.gpio.level == platform::board::VALUE::HIGH);
                        break;

                    default:
                        break;
                    }
                    break;
                case SET_REPORT::KEYPAD:
                    switch (set_report.keypad.identifier)
                    {
                    case payload::keypad::IDENTIFIER::HCI:
                        switch (set_report.keypad.function)
                        {
                        case payload::keypad::FUNCTION::ENABLE:
                            engine::handler::set_hci_enabled(true);
                            break;
                        case payload::keypad::FUNCTION::DISABLE:
                            engine::handler::set_hci_enabled(false);
                            break;
                        default:
                            break;
                        }
                        break;
                    case payload::keypad::IDENTIFIER::HID:
                        switch (set_report.keypad.function)
                        {
                        case payload::keypad::FUNCTION::ENABLE:
                            engine::handler::set_hid_enabled(true);
                            break;
                        case payload::keypad::FUNCTION::DISABLE:
                            engine::handler::set_hid_enabled(false);
                            break;
                        default:
                            break;
                        }
                        break;
                    case payload::keypad::IDENTIFIER::KEYCODE:
                    {
                        /* todo: function click or push... */
                        const engine::keypad::KEY_ID key_code_id = engine::keypad::int2id(set_report.keypad.code);
                        if (key_code_id != engine::keypad::KEY_ID::UNDEFINED)
                        {
                            engine::keypad::press_key(key_code_id);
                            engine::keypad::release_ley(key_code_id);
                        }
                        break;
                    }
                    case payload::keypad::IDENTIFIER::MAPPING:
                        switch (set_report.keypad.function)
                        {
                        case payload::keypad::FUNCTION::SET:
                            if (set_report.keypad.table != engine::payload::keypad::TABLE::UNDEFINED)
                            {
                                engine::keypad::set_mapping(set_report.keypad.table);
                            }
                            break;
                        case payload::keypad::FUNCTION::GET:
                            /* get mapping implemented with a get report */
                            break;
                        case payload::keypad::FUNCTION::CLEAN:
                            engine::keypad::clean();
                            break;
                        default:
                            break;
                        }
                        break;
                    default:
                        break;
                    }
                    break;
                case SET_REPORT::PARAMETER:
                    switch (set_report.parameter.function)
                    {
                    case engine::payload::parameter::FUNCTION::GET:
                        parameter_request.identifier = set_report.parameter.identifier;
                        parameter_request.function = set_report.parameter.function;
                        break;
                    case engine::payload::parameter::FUNCTION::SET:
                        engine::payload::parameter::set_parameter(set_report.parameter);
                        break;

                    default:
                        break;
                    }
                    break;
                case SET_REPORT::RESET:
                {
                    const handler::event_t event = {
                        .identifier = payload::IDENTIFIER::RESET,
                        .reset = {
                            .function = set_report.reset.function,
                        },
                    };
                    handler::event_queue.push(event);
                    break;
                }
                default:
                    break;
                }
            }
            else
            {
                /* ignore all the other events */
            }
        }

        extern void get_report_handler(const uint8_t identifier, const chunk_t &_buffer)
        {
            engine::hid::get_report_t report;
            report.report = static_cast<engine::hid::GET_REPORT>(identifier);
            report.result = engine::hid::RESULT::SUCCESS;

            uint8_t *ptr = _buffer.space;
            *ptr++ = (uint8_t)report.result;

            switch (report.report)
            {
            case GET_REPORT::FIRMWARE:
            {
                const engine::payload::identity::content_t identity{
                    .identifier = engine::payload::identity::IDENTIFIER::FIRMWARE,
                };
                identity.serialize(ptr);
                break;
            }
            case GET_REPORT::GPIO:
            {
                if (pin_request.function == engine::payload::gpio::FUNCTION::DIRECTION_GET)
                {
                    const engine::gpio::DIRECTION direction = engine::gpio::get_direction(pin_request.identifier);
                    if (direction == engine::gpio::DIRECTION::UNDEFINED)
                    {
                        report.result = engine::hid::RESULT::FAILURE;
                    }
                    const engine::payload::gpio::content_t gpio{
                        .function = engine::payload::gpio::FUNCTION::DIRECTION_GET,
                        .identifier = pin_request.identifier,
                        .direction = direction,
                    };
                    gpio.serialize(ptr);
                }
                else if (pin_request.function == engine::payload::gpio::FUNCTION::LEVEL_GET)
                {
                    const engine::gpio::VALUE value = engine::gpio::get_value(pin_request.identifier);
                    if (value == engine::gpio::VALUE::UNDEFINED)
                    {
                        report.result = engine::hid::RESULT::FAILURE;
                    }
                    const engine::payload::gpio::content_t gpio{
                        .function = engine::payload::gpio::FUNCTION::LEVEL_GET,
                        .identifier = pin_request.identifier,
                        .level = value,
                    };
                    gpio.serialize(ptr);
                }
                else
                {
                    report.result = engine::hid::RESULT::UNKNOWN;
                }
                break;
            }
            case GET_REPORT::HARDWARE:
            {
                const engine::payload::identity::content_t identity{
                    .identifier = engine::payload::identity::IDENTIFIER::HARDWARE,
                };
                identity.serialize(ptr);
                break;
            }
            case GET_REPORT::MAPPING:
            {
                const engine::payload::keypad::content_t keypad{
                    .identifier = engine::payload::keypad::IDENTIFIER::MAPPING,
                    .function = engine::payload::keypad::FUNCTION::GET,
                    .table = engine::keypad::get_mapping(),
                };
                keypad.serialize(ptr);
                break;
            }
            case GET_REPORT::PARAMETER:
                engine::payload::parameter::get_parameter(parameter_request);
                parameter_request.serialize(ptr);
                break;
            case GET_REPORT::SERIAL:
            {
                const engine::payload::identity::content_t identity{
                    .identifier = engine::payload::identity::IDENTIFIER::SERIAL,
                };
                identity.serialize(ptr);
                break;
            }
            case GET_REPORT::TEMPERATURE:
            {
                const engine::payload::temperature::content_t temperature{
                    .function = engine::payload::temperature::FUNCTION::GET,
                    .value = platform::board::assembly.soc.get_temperature(),
                };
                temperature.serialize(ptr);
                break;
            }
            case GET_REPORT::UNIQUE:
            {
                const engine::payload::identity::content_t identity{
                    .identifier = engine::payload::identity::IDENTIFIER::UNIQUE,
                };
                identity.serialize(ptr);
                break;
            }

            default:
                break;
            }
        }
    }
}
