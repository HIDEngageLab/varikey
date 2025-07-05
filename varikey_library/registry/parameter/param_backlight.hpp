// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: Backlight parameter configuration
// SPDX-FileType: SOURCE

#pragma once

#include "backlight3.hpp"
#include "backlight_color.hpp"
#include "parameter.hpp"

namespace registry::parameter::backlight
{
    using namespace engine::backlight;

    struct backlight_t
    {
        PROGRAM program;
        Color left;
        Color right;
        uint16_t timeout;
    } __attribute__((packed));

    static const size_t SIZE = sizeof(backlight_t);

    union register_t
    {
        uint8_t byte[SIZE];
        backlight_t value;

        void initialize(void);

        void deserialize(uint8_t const *const);
        void serialize(uint8_t **) const;
    } __attribute__((packed));

    extern register_t g_register;
}
