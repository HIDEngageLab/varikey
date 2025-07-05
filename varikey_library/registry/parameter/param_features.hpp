// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: Features parameter configuration
// SPDX-FileType: SOURCE

#pragma once

#include "macros.hpp"
#include "parameter.hpp"

namespace registry::parameter::features
{
    struct features_t
    {
        ability_t autostart : 1;
        ability_t display : 1;
        ability_t keypad : 1;
        ability_t wakeup : 1;
        uint16_t reserved : 12;
    } __attribute__((packed));

    static const size_t SIZE = sizeof(features_t);

    union register_t
    {
        uint8_t byte[SIZE];
        features_t value;

        void initialize(void);

        void deserialize(uint8_t const *const);
        void serialize(uint8_t **) const;
    } __attribute__((packed));

    extern register_t g_register;
}
