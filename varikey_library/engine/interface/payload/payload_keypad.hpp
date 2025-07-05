// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: payload keypad module
// SPDX-FileType: SOURCE

#pragma once

#include <cstdint>

#include "macros.hpp"

#include "keypad_keycode.hpp"
#include "keypad_modifiers.hpp"
#include "payload_identifier.hpp"

namespace engine::payload::keypad
{
    using TABLE = engine::keypad::TABLE;
    using KEY_ID = engine::keypad::KEY_ID;
    using MODIFIER = engine::keypad::MODIFIER;

    enum class IDENTIFIER : uint8_t
    {
        HCI = 0x00,
        HID = 0x01,
        KEYCODE = 0x02,
        MAPPING = 0x03,

        UNDEFINED = to_underlying(payload::IDENTIFIER::UNDEFINED),
    };

    enum class FUNCTION : uint8_t
    {
        DISABLE = common::function::DISABLE,
        ENABLE = common::function::ENABLE,
        GET = common::function::GET,
        SET = common::function::SET,

        CLICK = common::function::CUSTOM,
        PRESS = common::function::CUSTOM + 1,
        PUSH = common::function::CUSTOM + 2,
        RELEASE = common::function::CUSTOM + 3,
        RESET = common::function::CUSTOM + 4,

        UNDEFINED = to_underlying(common::function::UNDEFINED),
    };

    struct content_t
    {
        IDENTIFIER identifier;
        FUNCTION function;
        union
        {
            TABLE table;
            struct
            {
                MODIFIER modifier;
                KEY_ID code;
            } key;
            struct
            {
                uint8_t modifier;
                uint8_t code;
                TABLE table;
            } value;
        };

        const size_t size() const;
        void deserialize(uint8_t const *const);
        void serialize(uint8_t **) const;
    };
}
