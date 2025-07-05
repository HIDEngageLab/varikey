// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: payload display module
// SPDX-FileType: SOURCE

#pragma once

#include <cstdint>
#include <cstring>

#include "display_font.hpp"
#include "display_image.hpp"
#include "display_position.hpp"
#include "display_type.hpp"
#include "macros.hpp"
#include "payload_identifier.hpp"

namespace engine::payload::display
{
    using FONT = engine::display::FONT;
    using ICON = engine::display::ICON;
    using Position = engine::display::Position;

    enum class FUNCTION : uint8_t
    {
        CLEAN = common::function::CUSTOM,
        FONT = common::function::CUSTOM + 1,
        ICON = common::function::CUSTOM + 2,
        POSITION = common::function::CUSTOM + 3,
        TEXT = common::function::CUSTOM + 4,

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
