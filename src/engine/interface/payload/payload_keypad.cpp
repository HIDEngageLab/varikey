/**
 * \file payload_keypad.cpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#include "payload_keypad.hpp"

using namespace engine::payload::keypad;

const size_t content_t::size() const
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

void content_t::deserialize(uint8_t const *const _space)
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

void content_t::serialize(uint8_t **_ptr) const
{
    *(*_ptr)++ = (uint8_t)identifier;
    if (identifier == IDENTIFIER::HCI ||
        identifier == IDENTIFIER::HID)
    {
        *(*_ptr)++ = (uint8_t)function;
    }
    else if (identifier == IDENTIFIER::KEYCODE)
    {
        *(*_ptr)++ = (uint8_t)function;
        *(*_ptr)++ = (uint8_t)key.modifier.value;
        *(*_ptr)++ = (uint8_t)key.code;
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
    else
    {
        *(*_ptr)++ = (uint8_t)TABLE::UNDEFINED;
    }
}
