/**
 * \file engine_event_handler.cpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#include "engine_event_handler.hpp"
#include "board_assembly.hpp"
#include "cmd_control.hpp"
#include "cmd_feature.hpp"
#include "cmd_setting.hpp"
#include "display.hpp"
#include "engine_variant.hpp"
#include "keypad.hpp"
#include "keypad_keycode.hpp"
#include "keypad_modifiers.hpp"
#include "usb_descriptors.hpp"
#include "varikey.hpp"

namespace engine
{
    namespace handler
    {
        event_queue_t event_queue;

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
            const uint64_t curr = platform::board::assembly.soc.get_stopwatch();

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

        extern void push_key_event(const engine::keypad::KEY_ID _identifier,
                                   const engine::keypad::STATE _state)
        {
            const engine::keypad::TABLE table = engine::keypad::get_mapping();
            const engine::keypad::MODIFIER modifier = engine::keypad::get_modifier();

            const uint8_t key_code = engine::keypad::id2int(_identifier);

            payload::keypad::content_t key_event = {
                .identifier = engine::payload::keypad::IDENTIFIER::KEYCODE,
                .function = engine::keypad::transfer_state<engine::keypad::STATE, engine::payload::keypad::FUNCTION>(_state),
                .value = {
                    .modifier = modifier.value,
                    .code = key_code,
                    .table = table,
                },
            };
            engine::handler::event_t event = {
                .identifier = engine::payload::IDENTIFIER::KEYPAD,
                .keypad = key_event,
            };

            handler::event_queue.push(event);

            if (_state == engine::keypad::STATE::PRESS ||
                _state == engine::keypad::STATE::CLICK ||
                _state == engine::keypad::STATE::PUSH)
            {
                engine::keypad::perform(_identifier);
            }
        };

        extern void push_gpio_event(const platform::board::IDENTIFIER _identifier,
                                    const platform::board::VALUE _value,
                                    const uint32_t _diff)
        {
            static int c = 0;
            c++;
            const payload::gpio::content_t content = {
                .function = (_value == platform::board::VALUE::HIGH) ? payload::gpio::FUNCTION::HIGH : payload::gpio::FUNCTION::LOW,
                .identifier = _identifier,
                .diff = _diff,
            };
            const engine::handler::event_t event = {
                .identifier = payload::IDENTIFIER::GPIO,
                .gpio = content,
            };
            handler::event_queue.push(event);
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
                    backlight::set_mode(backlight::MODE::CONST, 0);
                    backlight::morph_left(_event.backlight.left);
                    backlight::morph_right(_event.backlight.right);
                    break;
                case PROGRAM::MOUNT:
                    backlight::set_mode(backlight::MODE::MOUNT, 0);
                    break;
                case PROGRAM::OFF:
                    backlight::set_mode(backlight::MODE::OFF, 0);
                    break;
                case PROGRAM::SET:
                    backlight::set_mode(backlight::MODE::CONST, 0);
                    backlight::set_left(_event.backlight.left);
                    backlight::set_right(_event.backlight.right);
                    break;
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
                switch (_event.gadget.function)
                {
                case payload::gadget::FUNCTION::MOUNT:
                    backlight::set_mode(backlight::MODE::TURBO, 0);
                    backlight::set_mode(backlight::MODE::MOUNT,
                                        registry::parameter::backlight::g_register.value.timeout);
                    break;
                case payload::gadget::FUNCTION::UNMOUNT:
                    backlight::set_mode(backlight::MODE::ALERT, 0);
                    break;
                case payload::gadget::FUNCTION::SUSPEND:
                    backlight::set_mode(backlight::MODE::SUSPEND, 0);
                    break;
                case payload::gadget::FUNCTION::RESUME:
                    backlight::set_mode(backlight::MODE::TURBO, 0);
                    backlight::set_mode(backlight::MODE::MOUNT,
                                        registry::parameter::backlight::g_register.value.timeout);
                    break;
                default:
                    break;
                }
                break;
            case payload::IDENTIFIER::GPIO:
            {
                if (events_over_serial_enabled)
                {
                    engine::hci::cmd::feature::gpio_indication(_event.gpio.function,
                                                               _event.gpio.identifier,
                                                               _event.gpio.diff);
                }
                if (events_over_usb_enabled)
                {
                    /* todo: idea send gpio level changes as a key press/release sequences */
                }
                break;
            }
            case payload::IDENTIFIER::KEYPAD:
                switch (_event.keypad.identifier)
                {
                case payload::keypad::IDENTIFIER::HCI:
                    if (_event.keypad.function == payload::keypad::FUNCTION::ENABLE)
                        set_hci_enabled(true);
                    else
                        set_hci_enabled(false);
                    break;
                case payload::keypad::IDENTIFIER::HID:
                    if (_event.keypad.function == payload::keypad::FUNCTION::ENABLE)
                        set_hid_enabled(true);
                    else
                        set_hid_enabled(false);
                    break;
                case payload::keypad::IDENTIFIER::KEYCODE:
                    if (events_over_serial_enabled)
                    {
                        hci::cmd::feature::key_indication(_event.keypad);
                    }

                    if (events_over_usb_enabled)
                    {
                        if (_event.keypad.function == payload::keypad::FUNCTION::PRESS)
                        {
                            const uint8_t code = _event.keypad.value.code;
                            const uint8_t mode = _event.keypad.value.modifier;
                            platform::usb::sent_keycode(mode, code);
                        }
                        else
                        {
                            platform::usb::sent_keycode();
                        }
                    }
                    break;
                case payload::keypad::IDENTIFIER::MAPPING:
                    if (_event.keypad.function == payload::keypad::FUNCTION::SET &&
                        _event.keypad.table != engine::payload::keypad::TABLE::UNDEFINED)
                    {
                        engine::keypad::set_mapping(_event.keypad.table);
                    }
                    break;
                default:
                    break;
                }
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
