/**
 * \file engine_event_handler.cpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#include "engine_event_handler.hpp"
#include "board.hpp"
#include "cmd_control.hpp"
#include "cmd_feature.hpp"
#include "cmd_setting.hpp"
#include "display.hpp"
#include "engine_variant.hpp"
#include "usb_descriptors.hpp"
#include "varikey.hpp"

namespace engine
{
    namespace handler
    {
        event_queue_t event_queue;

        static bool caps = false;
        static bool nums = false;
        static bool scrl = false;

        static bool events_over_serial_enabled = engine::Variant::ENABLE_SERAIL_INTERFACE_ON_START;
        static bool events_over_usb_enabled = engine::Variant::ENABLE_USB_INTERFACE_ON_START;

        static void keypad_handle_event(event_t const _event);

        extern bool is_hci_enabled()
        {
            return events_over_serial_enabled;
        }

        extern void set_hci_enabled(const bool _value)
        {
            events_over_serial_enabled = _value;
        }

        extern bool is_hid_enabled()
        {
            return events_over_usb_enabled;
        }

        extern void set_hid_enabled(const bool _value)
        {
            events_over_usb_enabled = _value;
        }

        /**
         * \brief Called periodically by system ticker
         */
        extern void perform()
        {
            const uint64_t PERFORM_DELAY_NS = 15000;
            static uint64_t tsm = 0;
            const uint64_t curr = get_stopwatch();

            if ((curr - tsm) > PERFORM_DELAY_NS)
            {
                tsm = curr;
                if (!event_queue.empty())
                {
                    const event_t &event = event_queue.front();
                    keypad_handle_event(event);
                    event_queue.pop();
                }
            }
        }

        static void keypad_handle_event(event_t const _event)
        {
            using PROGRAM = engine::backlight::MODE;
            switch (_event.identifier)
            {
            case payload::IDENTIFIER::BACKLIGHT:
                switch (_event.backlight.program)
                {
                case PROGRAM::ALERT:
                    backlight::set_mode(backlight::MODE::ALERT, 0);
                    break;
                case PROGRAM::CONST:
                    backlight::set_mode(backlight::MODE::CONST, 0);
                    break;
                case PROGRAM::MEDIUM:
                    backlight::set_mode(backlight::MODE::MEDIUM, 0);
                    break;
                case PROGRAM::MORPH:
                {
                    backlight::set_mode(backlight::MODE::CONST, 0);
                    {
                        const uint8_t r = _event.backlight.color_left.rgb.r;
                        const uint8_t g = _event.backlight.color_left.rgb.g;
                        const uint8_t b = _event.backlight.color_left.rgb.b;
                        backlight::morph_left(r, g, b);
                    }
                    {
                        const uint8_t r = _event.backlight.color_right.rgb.r;
                        const uint8_t g = _event.backlight.color_right.rgb.g;
                        const uint8_t b = _event.backlight.color_right.rgb.b;
                        backlight::morph_right(r, g, b);
                    }
                    break;
                }
                case PROGRAM::MOUNT:
                    backlight::set_mode(backlight::MODE::MOUNT, 0);
                    break;
                case PROGRAM::OFF:
                    backlight::set_mode(backlight::MODE::OFF, 0);
                    break;
                case PROGRAM::SET:
                {
                    backlight::set_mode(backlight::MODE::CONST, 0);
                    {
                        const uint8_t r = _event.backlight.color_left.rgb.r;
                        const uint8_t g = _event.backlight.color_left.rgb.g;
                        const uint8_t b = _event.backlight.color_left.rgb.b;
                        backlight::set_left(r, g, b);
                    }
                    {
                        const uint8_t r = _event.backlight.color_right.rgb.r;
                        const uint8_t g = _event.backlight.color_right.rgb.g;
                        const uint8_t b = _event.backlight.color_right.rgb.b;
                        backlight::set_right(r, g, b);
                    }
                    break;
                }
                case PROGRAM::SLOW:
                    backlight::set_mode(backlight::MODE::SLOW, 0);
                    break;
                case PROGRAM::SUSPEND:
                    backlight::set_mode(backlight::MODE::SUSPEND, 0);
                    break;
                case PROGRAM::TURBO:
                    backlight::set_mode(backlight::MODE::TURBO, 0);
                    break;
                default:
                    backlight::set_mode(backlight::MODE::MEDIUM, 0);
                    break;
                }
                break;
            case payload::IDENTIFIER::DISPLAY:
                switch (_event.display.function)
                {
                case payload::display::FUNCTION::CLEAN:
                    display::clean();
                    break;
                case payload::display::FUNCTION::FONT:
                    display::set_font(_event.display.font);
                    break;
                case payload::display::FUNCTION::ICON:
                    display::draw(_event.display.icon);
                    break;
                case payload::display::FUNCTION::POSITION:
                    display::set_cursor(_event.display.position.line,
                                        _event.display.position.column);
                    break;
                case payload::display::FUNCTION::TEXT:
                    display::print((char *const)_event.display.text);
                    break;
                default:
                    break;
                }
                break;
            case payload::IDENTIFIER::GADGET:
                switch (_event.gadget.command)
                {
                case payload::gadget::COMMAND::MOUNT:
                    backlight::set_mode(backlight::MODE::TURBO, 0);
                    backlight::set_mode(backlight::MODE::MOUNT,
                                        registry::parameter::backlight::g_register.param_backlight.timeout);
                    break;
                case payload::gadget::COMMAND::UNMOUNT:
                    backlight::set_mode(backlight::MODE::ALERT, 0);
                    break;
                case payload::gadget::COMMAND::SUSPEND:
                    backlight::set_mode(backlight::MODE::SUSPEND, 0);
                    break;
                case payload::gadget::COMMAND::RESUME:
                    backlight::set_mode(backlight::MODE::TURBO, 0);
                    backlight::set_mode(backlight::MODE::MOUNT,
                                        registry::parameter::backlight::g_register.param_backlight.timeout);
                    break;
                case payload::gadget::COMMAND::RESET:
                    /* unsupported */
                    break;
                default:
                    break;
                }
                break;
            case payload::IDENTIFIER::GPIO:
                break;
            case payload::IDENTIFIER::KEYCODE:
                if (events_over_serial_enabled)
                {
                    hci::cmd::feature::key_indication(_event.keycode);
                }

                if (events_over_usb_enabled)
                {
                    if (_event.keycode.state == payload::keycode::STATE::PRESS)
                    {
                        uint8_t code = engine::keypad::to_int(_event.keycode.key_id, _event.keycode.table);
                        platform::usb::sent_keycode(code);
                    }
                    else
                    {
                        platform::usb::sent_keycode();
                    }
                }
                break;
            case payload::IDENTIFIER::KEYPAD:
                switch (_event.keypad.identifier)
                {
                case payload::keypad::IDENTIFIER::MAPPING:
                    if (_event.keypad.function == payload::keypad::FUNCTION::SET)
                    {
                        engine::keypad::set_mapping(_event.keypad.table);
                    }
                    /*
                    // todo: get report handler
                    else if (_event.keyboard.function == payload::keypad::FUNCTION::GET)
                    {
                        _event.keyboard.table = engine::keypad::get_mapping();
                    }
                    */

                    switch (_event.keypad.table)
                    {
                    case payload::keypad::TABLE::CUSTOM:
                        break;
                    case payload::keypad::TABLE::FUNCTIONAL:
                        if (_event.keypad.function == payload::keypad::FUNCTION::SET)
                            caps = true;
                        else
                            caps = false;
                        break;
                    case payload::keypad::TABLE::MULTIMEDIA:
                        if (_event.keypad.function == payload::keypad::FUNCTION::SET)
                            nums = true;
                        else
                            nums = false;
                        break;
                    case payload::keypad::TABLE::NAVIGATION:
                        if (_event.keypad.function == payload::keypad::FUNCTION::SET)
                            scrl = true;
                        else
                            scrl = false;
                        break;
                    case payload::keypad::TABLE::NUMBER:
                        break;
                    case payload::keypad::TABLE::TELEFON:
                        break;

                    default:
                        break;
                    }
                    break;
                case payload::keypad::IDENTIFIER::HID:
                    if (_event.keypad.function == payload::keypad::FUNCTION::ENABLE)
                        set_hid_enabled(true);
                    else
                        set_hid_enabled(false);
                    break;
                case payload::keypad::IDENTIFIER::HCI:
                    if (_event.keypad.function == payload::keypad::FUNCTION::ENABLE)
                        set_hci_enabled(true);
                    else
                        set_hci_enabled(false);
                    break;
                default:
                    break;
                }

                if (caps && nums && scrl)
                    backlight::set_mode(backlight::MODE::TURBO, 0);
                else if (caps && nums && !scrl)
                    backlight::set_mode(backlight::MODE::CONST, 0);
                else if (caps && !nums && scrl)
                    backlight::set_mode(backlight::MODE::MOUNT, 0);
                else if (caps && !nums && !scrl)
                    backlight::set_mode(backlight::MODE::SUSPEND, 0);
                else if (!caps && nums && scrl)
                    backlight::set_mode(backlight::MODE::MEDIUM, 0);
                else if (!caps && nums && !scrl)
                    backlight::set_mode(backlight::MODE::OFF, 0);
                else if (!caps && !nums && scrl)
                    backlight::set_mode(backlight::MODE::SLOW, 0);
                else if (!caps && !nums && !scrl)
                    backlight::set_mode(backlight::MODE::ALERT, 0);

                break;
            case payload::IDENTIFIER::PARAMETER:
                break;
            case payload::IDENTIFIER::RESET:
                if (_event.reset.function == engine::payload::reset::FUNCTION::FORMAT)
                {
                    registry::parameter::param_format();
                }

                /* no  return */
                varikey_shutdown();

                break;
            default:
                break;
            }
        }
    } // namespace handler
} // namespace engine
