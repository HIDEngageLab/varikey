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
#include "macros.hpp"
#include "payload_identifier.hpp"

namespace engine
{
    namespace payload
    {
        namespace display
        {
            using FONT = engine::display::FONT;
            using ICON = engine::display::ICON;
            using Position = engine::display::Position;

            enum class FUNCTION : uint8_t
            {
                CLEAN = common::function::CUSTOM,        /* clean up display */
                FONT = common::function::CUSTOM + 1,     /* font art/size */
                ICON = common::function::CUSTOM + 2,     /* icon identifier */
                POSITION = common::function::CUSTOM + 3, /* cursor position */
                TEXT = common::function::CUSTOM + 4,     /* text message */

                UNDEFINED = to_underlying(payload::IDENTIFIER::UNDEFINED),
            };

            static const uint8_t MESSAGE_SIZE = platform::hardware::Display::MAX_LINE_LENGTH + 1;

            struct content_t
            {
                FUNCTION function;
                union
                {
                    FONT font;
                    Position position;
                    char text[MESSAGE_SIZE];
                    ICON icon;
                };

                const size_t size() const;
                void deserialize(uint8_t const *const);
                void serialize(uint8_t **_ptr) const;
            };
        }
    }
}

#endif // __PAYLOAD_DISPLAY_HPP__
