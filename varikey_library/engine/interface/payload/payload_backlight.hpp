// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: payload backlight module
// SPDX-FileType: SOURCE

#pragma once

#include <cstdint>
#include <cstdlib>

#include "backlight_color.hpp"
#include "backlight_mode.hpp"
#include "payload_identifier.hpp"

namespace engine::payload::backlight
{
    struct content_t
    {
        using PROGRAM = engine::backlight::PROGRAM;
        using Color = engine::backlight::Color;

        PROGRAM program;
        Color left;
        Color right;

        const size_t size() const;
        void deserialize(uint8_t const *const);
        void serialize(uint8_t **) const;
    };
}
