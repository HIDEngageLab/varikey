/**
 * \file engine_event.hpp
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#ifndef __ENGINE_EVENT_HPP__
#define __ENGINE_EVENT_HPP__

#include <cstdint>
#include <queue>

#include "payload_backlight.hpp"
#include "payload_display.hpp"
#include "payload_gadget.hpp"
#include "payload_gpio.hpp"
#include "payload_identifier.hpp"
#include "payload_identity.hpp"
#include "payload_keycode.hpp"
#include "payload_keypad.hpp"
#include "payload_parameter.hpp"
#include "payload_reset.hpp"
#include "payload_temperature.hpp"

namespace engine
{
    /* Really size is 5 bytes */
    static const size_t EVENT_VALUE_SIZE = 6;

    struct __attribute__((__packed__)) event_t
    {
        payload::IDENTIFIER identifier;
        union
        {
            payload::backlight::content_t backlight;
            payload::display::content_t display;
            payload::gadget::content_t gadget;
            payload::gpio::content_t gpio;
            payload::identity::content_t identity;
            payload::keycode::content_t keycode;
            payload::keypad::content_t keypad;
            payload::parameter::content_t parameter;
            payload::reset::content_t reset;
            payload::temperature::content_t temperature;
        };
/*
        void deserialize(uint8_t const *const _space)
        {
            uint8_t const *ptr = _space;
            identifier = static_cast<const payload::IDENTIFIER>(*ptr++);
            switch (identifier)
            {
            case payload::IDENTIFIER::BACKLIGHT:
                backlight.deserialize(ptr);
                break;
            case payload::IDENTIFIER::CONFIG:
                config.deserialize(ptr);
                break;
            case payload::IDENTIFIER::DISPLAY:
                display.deserialize(ptr);
                break;
            case payload::IDENTIFIER::GADGET:
                gadget.deserialize(ptr);
                break;
            case payload::IDENTIFIER::GPIO:
                gpio.deserialize(ptr);
                break;
            case payload::IDENTIFIER::IDENTITY:
                identity.deserialize(ptr);
                break;
            case payload::IDENTIFIER::KEYCODE:
                keycode.deserialize(ptr);
                break;
            case payload::IDENTIFIER::KEYPAD:
                keypad.deserialize(ptr);
                break;
            case payload::IDENTIFIER::PARAMETER:
                parameter.deserialize(ptr);
                break;
            case payload::IDENTIFIER::RESET:
                reset.deserialize(ptr);
                break;
            case payload::IDENTIFIER::TEMPERATURE:
                temperature.deserialize(ptr);
                break;
            default:
                break;
            }
        }

        void serialize(uint8_t *const _space)
        {
            uint8_t *ptr = _space;
            *ptr++ = (uint8_t)identifier;
            switch (identifier)
            {
            case payload::IDENTIFIER::BACKLIGHT:
                backlight.serialize(ptr);
                break;
            case payload::IDENTIFIER::CONFIG:
                config.serialize(ptr);
                break;
            case payload::IDENTIFIER::DISPLAY:
                display.serialize(ptr);
                break;
            case payload::IDENTIFIER::GADGET:
                gadget.serialize(ptr);
                break;
            case payload::IDENTIFIER::GPIO:
                gpio.serialize(ptr);
                break;
            case payload::IDENTIFIER::IDENTITY:
                identity.serialize(ptr);
                break;
            case payload::IDENTIFIER::KEYCODE:
                keycode.serialize(ptr);
                break;
            case payload::IDENTIFIER::KEYPAD:
                keypad.serialize(ptr);
                break;
            case payload::IDENTIFIER::PARAMETER:
                parameter.serialize(ptr);
                break;
            case payload::IDENTIFIER::RESET:
                reset.serialize(ptr);
                break;
            case payload::IDENTIFIER::TEMPERATURE:
                temperature.serialize(ptr);
                break;
            default:
                break;
            }
        }
*/
    };

    union event_plane_t
    {
        uint8_t value[EVENT_VALUE_SIZE];
        event_t typed;
    };

    struct event_timed_t
    {
        uint64_t timestamp;
        event_plane_t event;
    };
}

#endif // __ENGINE_EVENT_HPP__
