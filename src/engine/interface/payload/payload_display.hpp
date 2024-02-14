/**
 * \file payload_display.hpp
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#ifndef __PAYLOAD_DISPLAY_HPP__
#define __PAYLOAD_DISPLAY_HPP__

#include <cstdint>
#include <cstring>

#include "display_font.hpp"
#include "display_image.hpp"
#include "display_position.hpp"
#include "display_type.hpp"
#include "payload_identifier.hpp"

namespace engine
{
    namespace payload
    {
        namespace display
        {
            const uint8_t DISPLAY_ID = to_underlying(payload::IDENTIFIER::DISPLAY);

            enum class FUNCTION : uint8_t
            {
                CLEAN = DISPLAY_ID + 5,    /* clean up display */
                FONT = DISPLAY_ID + 1,     /* font art/size */
                ICON = DISPLAY_ID + 2,     /* icon identifier */
                POSITION = DISPLAY_ID + 3, /* cursor position */
                TEXT = DISPLAY_ID + 4,     /* text message */

                UNDEFINED = to_underlying(payload::IDENTIFIER::UNDEFINED),
            };

            static const uint8_t MESSAGE_SIZE = platform::hardware::Display::MAX_LINE_LENGTH + 1;

            struct __attribute__((packed)) content_t
            {

                FUNCTION function;
                union
                {
                    engine::display::FONT font;
                    engine::display::position_t position;
                    char text[MESSAGE_SIZE];
                    engine::display::ICON icon;
                };

                const size_t size() const
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

                void deserialize(uint8_t const *const _space)
                {
                    function = static_cast<const FUNCTION>(_space[0]);
                    if (!(function == FUNCTION::FONT ||
                          function == FUNCTION::ICON ||
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
                        font = static_cast<const engine::display::FONT>(_space[1]);
                        if (!engine::display::font::is_defined(font))
                        {
                            font = engine::display::FONT::UNDEFINED;
                        }
                    }
                    else if (function == FUNCTION::ICON)
                    {
                        icon = static_cast<const engine::display::ICON>(_space[1]);
                        if (!engine::display::image::is_defined(icon))
                        {
                            icon = engine::display::ICON::UNDEFINED;
                        }
                    }
                    else if (function == FUNCTION::TEXT)
                    {
                        memcpy(text, &_space[1], engine::payload::display::MESSAGE_SIZE);
                    }
                }

                void serialize(uint8_t *const _space) const
                {
                    uint8_t *ptr = _space;
                    *ptr++ = (uint8_t)function;

                    if (function == FUNCTION::POSITION)
                    {
                        *ptr++ = (uint8_t)position.line;
                        *ptr++ = (uint8_t)position.column;
                    }
                    else if (function == FUNCTION::FONT)
                    {
                        *ptr++ = (uint8_t)font;
                    }
                    else if (function == FUNCTION::ICON)
                    {
                        *ptr++ = (uint8_t)icon;
                    }
                    else if (function == FUNCTION::TEXT)
                    {
                        *ptr++ = (uint8_t)strlen(text);
                    }
                }
            };
        }
    }
}

#endif // __PAYLOAD_DISPLAY_HPP__
