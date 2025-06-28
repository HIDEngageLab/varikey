/**
 * \file payload_display.cpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#include "payload_display.hpp"

using namespace engine::payload::display;

const size_t content_t::size() const
{
    if (function == FUNCTION::POSITION)
        return 3;
    if (function == FUNCTION::FONT)
        return 2;
    if (function == FUNCTION::ICON)
        return 2;
    if (function == FUNCTION::TEXT)
        return 2;
    return 1;
}

void content_t::deserialize(uint8_t const *const _space)
{
    function = static_cast<const FUNCTION>(_space[0]);
    if (!(function == FUNCTION::FONT ||
          function == FUNCTION::ICON ||
          function == FUNCTION::CLEAN ||
          function == FUNCTION::POSITION ||
          function == FUNCTION::TEXT))
    {
        function = FUNCTION::UNDEFINED;
    }
    if (function == FUNCTION::POSITION)
    {
        position.line = _space[1];
        position.column = _space[2];
    }
    else if (function == FUNCTION::FONT)
    {
        font = static_cast<const FONT>(_space[1]);
        if (!engine::display::font::is_defined(font))
        {
            font = FONT::UNDEFINED;
        }
    }
    else if (function == FUNCTION::ICON)
    {
        icon = static_cast<const ICON>(_space[1]);
        if (!engine::display::image::is_defined(icon))
        {
            icon = ICON::UNDEFINED;
        }
    }
    else if (function == FUNCTION::TEXT)
    {
        memcpy(text, &_space[1], MESSAGE_SIZE);
    }
}

void content_t::serialize(uint8_t **_ptr) const
{
    *(*_ptr)++ = (uint8_t)function;

    if (function == FUNCTION::POSITION)
    {
        *(*_ptr)++ = (uint8_t)position.line;
        *(*_ptr)++ = (uint8_t)position.column;
    }
    else if (function == FUNCTION::FONT)
    {
        *(*_ptr)++ = (uint8_t)font;
    }
    else if (function == FUNCTION::ICON)
    {
        *(*_ptr)++ = (uint8_t)icon;
    }
    else if (function == FUNCTION::TEXT)
    {
        *(*_ptr)++ = (uint8_t)strlen(text);
    }
}
