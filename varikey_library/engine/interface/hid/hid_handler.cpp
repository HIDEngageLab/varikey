// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: hid handler module
// SPDX-FileType: SOURCE

#include <tusb.h>

#include "backlight_color.hpp"
#include "board_assembly.hpp"
#include "engine_event_handler.hpp"
#include "engine_gpio.hpp"
#include "hid_report.hpp"
#include "keypad.hpp"
#include "registry_defines.hpp"
#include "usb_descriptors.hpp"

namespace engine::hid
{
    payload::gpio::content_t pin_request;
    payload::parameter::content_t parameter_request;
    payload::keypad::content_t keypad_request;
    payload::identity::content_t identity_request;

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
        }
        else if (set_report.command == platform::usb::COMMAND::CUSTOM)
        {
            set_report.deserialize(_buffer);

            switch (set_report.report)
            {
            case SET_REPORT::BACKLIGHT:
                using PROGRAM = engine::backlight::PROGRAM;
                if (set_report.backlight.program == PROGRAM::SET ||
                    set_report.backlight.program == PROGRAM::MORPH)
                {
                    const handler::event_t event = {
                        .identifier = payload::IDENTIFIER::BACKLIGHT,
                        .backlight = {
                            .program = set_report.backlight.program,
                            .left = {.rgb = {
                                         .r = set_report.backlight.left.rgb.r,
                                         .g = set_report.backlight.left.rgb.g,
                                         .b = set_report.backlight.left.rgb.b,
                                     }},
                            .right = {.rgb = {
                                          .r = set_report.backlight.right.rgb.r,
                                          .g = set_report.backlight.right.rgb.g,
                                          .b = set_report.backlight.right.rgb.b,
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
                            .left = {0},
                            .right = {0},
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
                switch (set_report.gadget.function)
                {
                case payload::gadget::FUNCTION::MOUNT:
                {
                    const handler::event_t event = {
                        .identifier = payload::IDENTIFIER::GADGET,
                        .gadget = {
                            .function = payload::gadget::FUNCTION::MOUNT,
                        }};
                    handler::event_queue.push(event);
                    break;
                }
                case payload::gadget::FUNCTION::RESUME:
                {
                    const handler::event_t event = {
                        .identifier = payload::IDENTIFIER::GADGET,
                        .gadget = {
                            .function = payload::gadget::FUNCTION::RESUME,
                        }};
                    handler::event_queue.push(event);
                    break;
                }
                case payload::gadget::FUNCTION::SUSPEND:
                {
                    const handler::event_t event = {
                        .identifier = payload::IDENTIFIER::GADGET,
                        .gadget = {
                            .function = payload::gadget::FUNCTION::SUSPEND,
                        }};
                    handler::event_queue.push(event);
                    break;
                }
                case payload::gadget::FUNCTION::UNMOUNT:
                {
                    const handler::event_t event = {
                        .identifier = payload::IDENTIFIER::GADGET,
                        .gadget = {
                            .function = payload::gadget::FUNCTION::UNMOUNT,
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
                case engine::payload::gpio::FUNCTION::DIRECTION:
                    pin_request.function = set_report.gpio.function;
                    pin_request.identifier = set_report.gpio.identifier;
                    break;
                case engine::payload::gpio::FUNCTION::IN:
                    engine::gpio::set_direction(set_report.gpio.identifier, engine::gpio::DIRECTION::INPUT);
                    break;
                case engine::payload::gpio::FUNCTION::OUT:
                    engine::gpio::set_direction(set_report.gpio.identifier, engine::gpio::DIRECTION::OUTPUT);
                    break;
                case engine::payload::gpio::FUNCTION::VALUE:
                    pin_request.function = set_report.gpio.function;
                    pin_request.identifier = set_report.gpio.identifier;
                    break;
                case engine::payload::gpio::FUNCTION::HIGH:
                    engine::gpio::set_value(set_report.gpio.identifier, true);
                    break;
                case engine::payload::gpio::FUNCTION::LOW:
                    engine::gpio::set_value(set_report.gpio.identifier, false);
                    break;

                default:
                    break;
                }
                break;
            case SET_REPORT::IDENTITY:
                identity_request.part = set_report.identity.part;
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

                    const engine::keypad::KEY_ID key_code_id = set_report.keypad.key.code;
                    if (key_code_id != engine::keypad::KEY_ID::UNDEFINED)
                    {

                        if (set_report.keypad.function == engine::payload::keypad::FUNCTION::CLICK ||
                            set_report.keypad.function == engine::payload::keypad::FUNCTION::PUSH)
                        {
                            engine::keypad::set_modifier(set_report.keypad.key.modifier);
                            engine::keypad::press_key(key_code_id);
                            engine::keypad::release_ley(key_code_id);
                        }
                        else if (set_report.keypad.function == engine::payload::keypad::FUNCTION::PRESS)
                        {
                            engine::keypad::set_modifier(set_report.keypad.key.modifier);
                            engine::keypad::press_key(key_code_id);
                        }
                        else if (set_report.keypad.function == engine::payload::keypad::FUNCTION::RELEASE)
                        {
                            engine::keypad::release_ley(key_code_id);
                        }
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
                        if (set_report.keypad.identifier == engine::payload::keypad::IDENTIFIER::MAPPING &&
                            set_report.keypad.function == engine::payload::keypad::FUNCTION::GET)
                        {
                            keypad_request.identifier = set_report.keypad.identifier;
                            keypad_request.function = set_report.keypad.function;
                        }
                        else
                        {
                            keypad_request.identifier = engine::payload::keypad::IDENTIFIER::UNDEFINED;
                        }
                        break;
                    case payload::keypad::FUNCTION::RESET:
                        engine::keypad::reset();
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
        case GET_REPORT::GPIO:
        {
            if (pin_request.function == engine::payload::gpio::FUNCTION::DIRECTION)
            {
                const engine::gpio::DIRECTION direction = engine::gpio::get_direction(pin_request.identifier);
                switch (direction)
                {
                case engine::gpio::DIRECTION::INPUT:
                {

                    const engine::payload::gpio::content_t gpio{
                        .function = engine::payload::gpio::FUNCTION::IN,
                        .identifier = pin_request.identifier,
                    };
                    gpio.serialize(&ptr);
                    break;
                }
                case engine::gpio::DIRECTION::OUTPUT:
                {
                    const engine::payload::gpio::content_t gpio{
                        .function = engine::payload::gpio::FUNCTION::OUT,
                        .identifier = pin_request.identifier,
                    };
                    gpio.serialize(&ptr);
                    break;
                }
                default:
                {
                    report.result = engine::hid::RESULT::FAILURE;
                    const engine::payload::gpio::content_t gpio{
                        .function = engine::payload::gpio::FUNCTION::UNDEFINED,
                        .identifier = pin_request.identifier,
                    };
                    gpio.serialize(&ptr);
                    break;
                }
                }
            }
            else if (pin_request.function == engine::payload::gpio::FUNCTION::VALUE)
            {
                const engine::gpio::VALUE value = engine::gpio::get_value(pin_request.identifier);
                switch (value)
                {
                case engine::gpio::VALUE::HIGH:
                {
                    const engine::payload::gpio::content_t gpio{
                        .function = engine::payload::gpio::FUNCTION::HIGH,
                        .identifier = pin_request.identifier,
                    };
                    gpio.serialize(&ptr);
                    break;
                }
                case engine::gpio::VALUE::LOW:
                {
                    const engine::payload::gpio::content_t gpio{
                        .function = engine::payload::gpio::FUNCTION::LOW,
                        .identifier = pin_request.identifier,
                    };
                    gpio.serialize(&ptr);
                    break;
                }

                default:
                {
                    report.result = engine::hid::RESULT::FAILURE;
                    const engine::payload::gpio::content_t gpio{
                        .function = engine::payload::gpio::FUNCTION::UNDEFINED,
                        .identifier = pin_request.identifier,
                    };
                    gpio.serialize(&ptr);
                    break;
                }
                }
            }
            else
            {
                report.result = engine::hid::RESULT::UNKNOWN;
            }
            break;
        }

        case GET_REPORT::IDENTITY:
            switch (identity_request.part)
            {
            case engine::payload::identity::PART::FIRMWARE:
            {
                const engine::payload::identity::content_t identity{
                    .part = engine::payload::identity::PART::FIRMWARE,
                };
                identity.serialize(&ptr);
                break;
            }
            case engine::payload::identity::PART::HARDWARE:
            {
                const engine::payload::identity::content_t identity{
                    .part = engine::payload::identity::PART::HARDWARE,
                };
                identity.serialize(&ptr);
                break;
            }
            case engine::payload::identity::PART::SERIAL:
            {
                const engine::payload::identity::content_t identity{
                    .part = engine::payload::identity::PART::SERIAL,
                };
                identity.serialize(&ptr);
                break;
            }
            case engine::payload::identity::PART::UNIQUE:
            {
                const engine::payload::identity::content_t identity{
                    .part = engine::payload::identity::PART::UNIQUE,
                };
                identity.serialize(&ptr);
                break;
            }

            default:
                break;
            }
            break;
        case GET_REPORT::KEYPAD:
            if (keypad_request.identifier == engine::payload::keypad::IDENTIFIER::MAPPING &&
                keypad_request.function == engine::payload::keypad::FUNCTION::GET)
            {
                const engine::payload::keypad::content_t keypad{
                    .identifier = engine::payload::keypad::IDENTIFIER::MAPPING,
                    .function = engine::payload::keypad::FUNCTION::GET,
                    .table = engine::keypad::get_mapping(),
                };
                keypad.serialize(&ptr);
            }
            break;
        case GET_REPORT::PARAMETER:
            engine::payload::parameter::get_parameter(parameter_request);
            parameter_request.serialize(&ptr);
            break;
        case GET_REPORT::TEMPERATURE:
        {
            const engine::payload::temperature::content_t temperature{
                .function = engine::payload::temperature::FUNCTION::GET,
                .value = platform::board::assembly.soc.get_temperature(),
            };
            temperature.serialize(&ptr);
            break;
        }

        default:
            break;
        }
    }
}
