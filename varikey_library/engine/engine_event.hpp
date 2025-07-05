// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: Engine event definitions
// SPDX-FileType: SOURCE

#pragma once

#include <cstdint>
#include <queue>

#include "payload_backlight.hpp"
#include "payload_display.hpp"
#include "payload_gadget.hpp"
#include "payload_gpio.hpp"
#include "payload_identifier.hpp"
#include "payload_identity.hpp"
#include "payload_keypad.hpp"
#include "payload_parameter.hpp"
#include "payload_reset.hpp"
#include "payload_temperature.hpp"

namespace engine::handler
{
    struct event_t
    {
        payload::IDENTIFIER identifier;
        union
        {
            payload::backlight::content_t backlight;
            payload::display::content_t display;
            payload::gadget::content_t gadget;
            payload::gpio::content_t gpio;
            payload::identity::content_t identity;
            payload::keypad::content_t keypad;
            payload::parameter::content_t parameter;
            payload::reset::content_t reset;
            payload::temperature::content_t temperature;
        };
    };

    union event_plane_t
    {
        uint8_t value[sizeof(event_t)];
        event_t typed;
    };

    struct event_timed_t
    {
        uint64_t timestamp;
        event_plane_t event;
    };
}
