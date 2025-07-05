// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: Display image management
// SPDX-FileType: SOURCE

#pragma once

#include <cstddef>
#include <cstdint>

namespace engine::display
{
    enum class ICON : uint16_t
    {
        FRAME = 0x0000,
        VARIKEY_LOGO = 0x0001,
        GMCI_LOGO = 0x0002,
        HEART = 0x0003,
        ADD_CIRCLE_8 = 0x0004,
        ADD_CIRCLE_16 = 0x0005,
        ADD_CIRCLE_24 = 0x0006,
        ADD_CIRCLE_32 = 0x0007,
        ADD_SQUARE_8 = 0x0008,
        ADD_SQUARE_16 = 0x0009,
        ADD_SQUARE_24 = 0x0010,
        ADD_SQUARE_32 = 0x0011,
        UNDEFINED = 0xffff,
    };

    namespace image
    {
        struct Type
        {
            uint8_t const width;
            uint8_t const height;
            uint8_t const *data;
        };

        static const uint16_t SIZE = 12;
        extern const Type images[SIZE];

        extern const bool is_defined(const engine::display::ICON _icon);
        extern const image::Type *get_image(const engine::display::ICON _icon);
    }
}
