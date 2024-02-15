/**
 * \file hid_handler.cpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#include <tusb.h>

#include "backlight_color.hpp"
#include "board.hpp"
#include "engine_event_handler.hpp"
#include "hid_report.hpp"
#include "usb_descriptors.hpp"

namespace engine
{
    namespace hid
    {
        extern void set_report_handler(const uint8_t _identifier, const const_chunk_t &_buffer)
        {
            set_report_t set_report;
            set_report.command = static_cast<platform::usb::COMMAND>(_identifier);

            if (set_report.command == platform::usb::COMMAND::KEYBOARD)
            {
                const uint8_t led_flags = _buffer.space[0];

                static bool num{false};
                static bool caps{false};
                static bool scroll{false};

                if (led_flags & 0x01)
                {
                    num = !num;
                }

                if (led_flags & 0x02)
                {
                    caps = !caps;
                }

                if (led_flags & 0x04)
                {
                    scroll = !scroll;
                }
            }
            else if (set_report.command == platform::usb::COMMAND::MOUSE)
            {
                /* do nothing */
            }
            else if (set_report.command == platform::usb::COMMAND::CUSTOM)
            {
                set_report.deserialize(_buffer);

                switch (set_report.identifier)
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
                    case payload::gadget::COMMAND::RESET:
                    {
                        const handler::event_t event = {
                            .identifier = payload::IDENTIFIER::GADGET,
                            .gadget = {
                                .command = payload::gadget::COMMAND::RESET,
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
                    break;
                case SET_REPORT::KEYCODE:
                    break;
                case SET_REPORT::KEYPAD:
                    break;
                case SET_REPORT::PARAMETER:
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

        extern void get_report_handler(const uint8_t _identifier, const chunk_t &_buffer)
        {
            engine::hid::get_report_t _report;
            _report.identifier = static_cast<engine::hid::GET_REPORT>(_identifier);
            _report.serialize(_buffer);
        }
    }
}
