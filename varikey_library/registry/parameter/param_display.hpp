// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: Display parameter configuration
// SPDX-FileType: SOURCE

#pragma once

#include "macros.hpp"
#include "parameter.hpp"

namespace registry::parameter::display
{

    struct display_t
    {
        ability_t rotate : 1;
        ability_t inverse : 1;
        ability_t slides : 1;
        uint8_t reserved : 5;
    } __attribute__((packed));

    static const size_t SIZE = sizeof(display_t);

    union register_t
    {
        uint8_t byte[SIZE];
        display_t value;

        void initialize(void);

        void deserialize(uint8_t const *const);
        void serialize(uint8_t **) const;
    } __attribute__((packed));

    extern register_t g_register;
}
