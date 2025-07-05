// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: commander module
// SPDX-FileType: SOURCE

#pragma once

#include <stdint.h>

#include "chunk.h"
#include "cmd_protocol_msg.hpp"
#include "payload_identifier.hpp"

namespace engine::hci
{
    static const uint8_t INTERPRETER_ADDRESS = 0x20;

    enum class SUFFIX : uint8_t
    {
        REQ = 0x00,
        CFM = 0x01,
        IND = 0x02,
        RES = 0x03,
    };

    namespace hc
    {

        static const uint8_t BACKLIGHT = (uint8_t)payload::IDENTIFIER::BACKLIGHT;
        static const uint8_t DISPLAY = (uint8_t)payload::IDENTIFIER::DISPLAY;
        static const uint8_t GADGET = (uint8_t)payload::IDENTIFIER::GADGET;
        static const uint8_t GPIO = (uint8_t)payload::IDENTIFIER::GPIO;
        static const uint8_t HASH = (uint8_t)payload::IDENTIFIER::HASH;
        static const uint8_t IDENTITY = (uint8_t)payload::IDENTIFIER::IDENTITY;
        static const uint8_t KEYPAD = (uint8_t)payload::IDENTIFIER::KEYPAD;
        static const uint8_t PARAMETER = (uint8_t)payload::IDENTIFIER::PARAMETER;
        static const uint8_t PROTOCOL = (uint8_t)payload::IDENTIFIER::PROTOCOL;
        static const uint8_t RESET = (uint8_t)payload::IDENTIFIER::RESET;
        static const uint8_t TEMPERATURE = (uint8_t)payload::IDENTIFIER::TEMPERATURE;

        static const uint8_t OFFSET = 2;

        static const uint8_t BACKLIGHT_CFM_VALUE = ((BACKLIGHT << OFFSET) + (int)SUFFIX::CFM);
        static const uint8_t BACKLIGHT_REQ_VALUE = ((BACKLIGHT << OFFSET) + (int)SUFFIX::REQ);
        static const uint8_t DISPLAY_CFM_VALUE = ((DISPLAY << OFFSET) + (int)SUFFIX::CFM);
        static const uint8_t DISPLAY_REQ_VALUE = ((DISPLAY << OFFSET) + (int)SUFFIX::REQ);
        static const uint8_t GADGET_CFM_VALUE = ((GADGET << OFFSET) + (int)SUFFIX::CFM);
        static const uint8_t GADGET_IND_VALUE = ((GADGET << OFFSET) + (int)SUFFIX::IND);
        static const uint8_t GADGET_REQ_VALUE = ((GADGET << OFFSET) + (int)SUFFIX::REQ);
        static const uint8_t GPIO_CFM_VALUE = ((GPIO << OFFSET) + (int)SUFFIX::CFM);
        static const uint8_t GPIO_IND_VALUE = ((GPIO << OFFSET) + (int)SUFFIX::IND);
        static const uint8_t GPIO_REQ_VALUE = ((GPIO << OFFSET) + (int)SUFFIX::REQ);
        static const uint8_t HASH_CFM_VALUE = ((HASH << OFFSET) + (int)SUFFIX::CFM);
        static const uint8_t HASH_REQ_VALUE = ((HASH << OFFSET) + (int)SUFFIX::REQ);
        static const uint8_t IDENTITY_CFM_VALUE = ((IDENTITY << OFFSET) + (int)SUFFIX::CFM);
        static const uint8_t IDENTITY_REQ_VALUE = ((IDENTITY << OFFSET) + (int)SUFFIX::REQ);
        static const uint8_t KEYPAD_CFM_VALUE = ((KEYPAD << OFFSET) + (int)SUFFIX::CFM);
        static const uint8_t KEYPAD_IND_VALUE = ((KEYPAD << OFFSET) + (int)SUFFIX::IND);
        static const uint8_t KEYPAD_REQ_VALUE = ((KEYPAD << OFFSET) + (int)SUFFIX::REQ);
        static const uint8_t PARAM_CFM_VALUE = ((PARAMETER << OFFSET) + (int)SUFFIX::CFM);
        static const uint8_t PARAM_REQ_VALUE = ((PARAMETER << OFFSET) + (int)SUFFIX::REQ);
        static const uint8_t PROTOCOL_IND_VALUE = ((PROTOCOL << OFFSET) + (int)SUFFIX::IND);
        static const uint8_t RESET_CFM_VALUE = ((RESET << OFFSET) + (int)SUFFIX::CFM);
        static const uint8_t RESET_IND_VALUE = ((RESET << OFFSET) + (int)SUFFIX::IND);
        static const uint8_t RESET_REQ_VALUE = ((RESET << OFFSET) + (int)SUFFIX::REQ);
        static const uint8_t TEMPERATURE_CFM_VALUE = ((TEMPERATURE << OFFSET) + (int)SUFFIX::CFM);
        static const uint8_t TEMPERATURE_IND_VALUE = ((TEMPERATURE << OFFSET) + (int)SUFFIX::IND);
        static const uint8_t TEMPERATURE_REQ_VALUE = ((TEMPERATURE << OFFSET) + (int)SUFFIX::REQ);
    }

    enum class COMMAND : uint8_t
    {
        BACKLIGHT_CFM = hc::BACKLIGHT_CFM_VALUE,
        BACKLIGHT_REQ = hc::BACKLIGHT_REQ_VALUE,
        DISPLAY_CFM = hc::DISPLAY_CFM_VALUE,
        DISPLAY_REQ = hc::DISPLAY_REQ_VALUE,
        GADGET_CFM = hc::GADGET_CFM_VALUE,
        GADGET_IND = hc::GADGET_IND_VALUE,
        GADGET_REQ = hc::GADGET_REQ_VALUE,
        GPIO_CFM = hc::GPIO_CFM_VALUE,
        GPIO_IND = hc::GPIO_IND_VALUE,
        GPIO_REQ = hc::GPIO_REQ_VALUE,
        HASH_CFM = hc::HASH_CFM_VALUE,
        HASH_REQ = hc::HASH_REQ_VALUE,
        IDENTITY_CFM = hc::IDENTITY_CFM_VALUE,
        IDENTITY_REQ = hc::IDENTITY_REQ_VALUE,
        KEYPAD_CFM = hc::KEYPAD_CFM_VALUE,
        KEYPAD_IND = hc::KEYPAD_IND_VALUE,
        KEYPAD_REQ = hc::KEYPAD_REQ_VALUE,
        PARAM_CFM = hc::PARAM_CFM_VALUE,
        PARAM_REQ = hc::PARAM_REQ_VALUE,
        PROTOCOL_IND = hc::PROTOCOL_IND_VALUE,
        RESET_CFM = hc::RESET_CFM_VALUE,
        RESET_IND = hc::RESET_IND_VALUE,
        RESET_REQ = hc::RESET_REQ_VALUE,
        TEMPERATURE_CFM = hc::TEMPERATURE_CFM_VALUE,
        TEMPERATURE_IND = hc::TEMPERATURE_IND_VALUE,
        TEMPERATURE_REQ = hc::TEMPERATURE_REQ_VALUE,
    };
    extern cmd::protocol::RESULT interpreter(chunk_t const *const _chunk);
}
