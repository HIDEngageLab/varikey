// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: payload backlight module
// SPDX-FileType: SOURCE

#pragma once

#include <cstdint>
#include <cstdlib>

#include "backlight_channel.hpp"
#include "backlight_program.hpp"
#include "payload_identifier.hpp"
#include "smartled_color.hpp"

namespace engine::payload::backlight
{
    struct content_t
    {
        using PROGRAM = engine::backlight::PROGRAM;
        using CHANNEL = engine::backlight::CHANNEL;
        using Color = platform::hardware::smartled::Color;

        PROGRAM program;
        CHANNEL channel;
        Color left;
        Color right;

        const size_t size() const;
        void deserialize(uint8_t const *const);
        void serialize(uint8_t **) const;
    };
}
