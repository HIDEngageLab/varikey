/**
 * \file payload_keypad.hpp
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#ifndef __PAYLOAD_KEYPAD_HPP__
#define __PAYLOAD_KEYPAD_HPP__

#include <cstdint>

#include "macros.hpp"

#include "keypad_keycode.hpp"
#include "keypad_modifiers.hpp"
#include "payload_identifier.hpp"

namespace engine
{
    namespace payload
    {
        namespace keypad
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

            struct __attribute__((packed)) content_t
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

                const size_t size() const
                {
                    switch (identifier)
                    {
                    case IDENTIFIER::HCI:
                        return 2;
                    case IDENTIFIER::HID:
                        return 2;
                    case IDENTIFIER::KEYCODE:
                        return 4;
                    case IDENTIFIER::MAPPING:
                        return 3;
                    default:
                        break;
                    }
                    return 2;
                }

                void deserialize(uint8_t const *const _space)
                {
                    identifier = static_cast<const IDENTIFIER>(_space[0]);
                    if (!(identifier == IDENTIFIER::MAPPING ||
                          identifier == IDENTIFIER::KEYCODE ||
                          identifier == IDENTIFIER::HID ||
                          identifier == IDENTIFIER::HCI))
                    {
                        identifier = IDENTIFIER::UNDEFINED;
                    }

                    if (identifier == IDENTIFIER::HCI ||
                        identifier == IDENTIFIER::HID)
                    {
                        function = static_cast<const FUNCTION>(_space[1]);
                        if (!(function == FUNCTION::ENABLE ||
                              function == FUNCTION::DISABLE))
                        {
                            function = FUNCTION::UNDEFINED;
                        }
                    }
                    else if (identifier == IDENTIFIER::MAPPING)
                    {
                        function = static_cast<const FUNCTION>(_space[1]);
                        if (function == FUNCTION::SET ||
                            function == FUNCTION::GET)
                        {
                            table = static_cast<const TABLE>(_space[2]);
                            if (!(table == TABLE::CUSTOM ||
                                  table == TABLE::FUNCTIONAL ||
                                  table == TABLE::MULTIMEDIA ||
                                  table == TABLE::NAVIGATION ||
                                  table == TABLE::NUMBER ||
                                  table == TABLE::TELEFON))
                            {
                                table = TABLE::UNDEFINED;
                            }
                        }
                        else
                        {
                            function = FUNCTION::UNDEFINED;
                        }
                    }
                    else if (identifier == IDENTIFIER::KEYCODE)
                    {
                        function = static_cast<const FUNCTION>(_space[1]);
                        key.modifier.value = static_cast<uint8_t>(_space[2]);
                        key.code = static_cast<KEY_ID>(_space[3]);
                    }
                    else
                    {
                        table = TABLE::UNDEFINED;
                    }
                }

                void serialize(uint8_t **_ptr) const
                {
                    *(*_ptr)++ = (uint8_t)identifier;
                    if (identifier == IDENTIFIER::HCI ||
                        identifier == IDENTIFIER::HID)
                    {
                        *(*_ptr)++ = (uint8_t)function;
                    }
                    else if (identifier == IDENTIFIER::MAPPING)
                    {
                        *(*_ptr)++ = (uint8_t)function;
                        if (function == FUNCTION::SET ||
                            function == FUNCTION::GET)
                        {
                            *(*_ptr)++ = (uint8_t)table;
                        }
                        else
                        {
                            *(*_ptr)++ = (uint8_t)TABLE::UNDEFINED;
                        }
                    }
                    else if (identifier == IDENTIFIER::KEYCODE)
                    {
                        *(*_ptr)++ = (uint8_t)function;
                        *(*_ptr)++ = (uint8_t)key.modifier.value;
                        *(*_ptr)++ = (uint8_t)key.code;
                    }
                    else
                    {
                        *(*_ptr)++ = (uint8_t)TABLE::UNDEFINED;
                    }
                }
            };
        }
    }
}

#endif // __PAYLOAD_KEYPAD_HPP__
