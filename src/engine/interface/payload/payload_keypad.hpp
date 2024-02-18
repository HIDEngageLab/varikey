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

#include "keypad_keycode.hpp"
#include "payload_identifier.hpp"

namespace engine
{
    namespace payload
    {
        namespace keypad
        {
            using TABLE = engine::keypad::TABLE;

            const uint8_t KEYPAD_ID = to_underlying(payload::IDENTIFIER::KEYPAD);

            enum class IDENTIFIER : uint8_t
            {
                HCI = KEYPAD_ID + 2,
                HID = KEYPAD_ID + 3,
                KEYCODE = KEYPAD_ID + 4,
                MAPPING = KEYPAD_ID + 1,

                UNDEFINED = to_underlying(payload::IDENTIFIER::UNDEFINED),
            };

            enum class FUNCTION : uint8_t
            {
                DISABLE = common::function::DISABLE,
                ENABLE = common::function::ENABLE,
                GET = common::function::GET,
                SET = common::function::SET,
                CLEAN = common::function::CLEAN,

                UNDEFINED = to_underlying(common::function::UNDEFINED),
            };

            struct __attribute__((packed)) content_t
            {
                IDENTIFIER identifier;
                FUNCTION function;
                TABLE table;
                uint8_t code;

                const size_t size() const
                {
                    return 2 + (identifier == IDENTIFIER::MAPPING) ? 1 : 0;
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
                        else if (function == FUNCTION::CLEAN)
                        {
                            table = TABLE::UNDEFINED;
                        }
                        else
                        {
                            function = FUNCTION::UNDEFINED;
                        }
                    }
                    else if (identifier == IDENTIFIER::KEYCODE)
                    {
                        code = static_cast<uint8_t>(_space[1]);
                    }
                    else
                    {
                        table = TABLE::UNDEFINED;
                    }
                }

                void serialize(uint8_t *const _space) const
                {
                    uint8_t *ptr = _space;
                    *ptr++ = (uint8_t)identifier;
                    if (identifier == IDENTIFIER::HCI ||
                        identifier == IDENTIFIER::HID)
                    {
                        *ptr++ = (uint8_t)function;
                    }
                    else if (identifier == IDENTIFIER::MAPPING)
                    {
                        *ptr++ = (uint8_t)function;
                        if (function == FUNCTION::SET ||
                            function == FUNCTION::GET)
                        {
                            *ptr++ = (uint8_t)table;
                        }
                    }
                    else if (identifier == IDENTIFIER::KEYCODE)
                    {
                        *ptr++ = (uint8_t)code;
                    }
                }
            };
        }
    }
}

#endif // __PAYLOAD_KEYPAD_HPP__
