/**
 * \file hid_report.hpp
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#ifndef __ENGINE_HID_REPORT_HPP__
#define __ENGINE_HID_REPORT_HPP__

#include <cstdint>
#include <queue>

#include "chunk.h"
#include "engine_event.hpp"
#include "payload_identifier.hpp"
#include "usb_descriptors.hpp"

namespace engine
{
    namespace hid
    {
        static const size_t MAX_REPORT_SIZE{128};

        enum class SET_REPORT : uint8_t
        {
            BACKLIGHT = (int)payload::IDENTIFIER::BACKLIGHT,
            DISPLAY = (int)payload::IDENTIFIER::DISPLAY,
            GADGET = (int)payload::IDENTIFIER::GADGET,
            GPIO = (int)payload::IDENTIFIER::GPIO,
            IDENTITY = (int)payload::IDENTIFIER::IDENTITY,
            KEYPAD = (int)payload::IDENTIFIER::KEYPAD,
            PARAMETER = (int)payload::IDENTIFIER::PARAMETER,
            RESET = (int)payload::IDENTIFIER::RESET,

            UNDEFINED = (int)payload::IDENTIFIER::UNDEFINED,
        };

        struct set_report_t
        {
            platform::usb::COMMAND command;
            SET_REPORT report;
            union
            {
                uint8_t buffer[MAX_REPORT_SIZE];
                payload::backlight::content_t backlight;
                payload::display::content_t display;
                payload::gadget::content_t gadget;
                payload::gpio::content_t gpio;
                payload::identity::content_t identity;
                payload::keypad::content_t keypad;
                payload::parameter::content_t parameter;
                payload::reset::content_t reset;
            };

            void deserialize(const const_chunk_t &);
            void serialize(const chunk_t &) const;
        };

        enum class GET_REPORT : uint8_t
        {
            GPIO = (int)payload::IDENTIFIER::GPIO,
            IDENTITY = (int)payload::IDENTIFIER::IDENTITY,
            KEYPAD = (int)payload::IDENTIFIER::KEYPAD,
            PARAMETER = (int)payload::IDENTIFIER::PARAMETER,
            TEMPERATURE = (int)payload::IDENTIFIER::TEMPERATURE,

            UNDEFINED = (int)payload::IDENTIFIER::UNDEFINED,
        };

        enum class RESULT : uint8_t
        {
            CUSTOM = common::result::CUSTOM,
            ERROR = common::result::ERROR,
            FAILURE = common::result::FAILURE,
            SUCCESS = common::result::SUCCESS,
            UNKNOWN = common::result::UNKNOWN,
            UNSUPPORTED = common::result::UNSUPPORTED,

            UNDEFINED = (int)common::result::UNDEFINED,
        };

        struct get_report_t
        {
            GET_REPORT report;
            RESULT result;
            union
            {
                payload::gpio::content_t gpio;
                payload::identity::content_t identity;
                payload::keypad::content_t keypad;
                payload::parameter::content_t parameter;
                payload::temperature::content_t temperature;
            };
        };
    }
}

#endif // __ENGINE_HID_REPORT_HPP__
