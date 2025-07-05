// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: Position parameter configuration
// SPDX-FileType: SOURCE

#pragma once

#include "parameter.hpp"

namespace registry::parameter::position
{
    struct coordinates_t
    {
        float latitude;
        float longitude;
    } __attribute__((packed));

    static const size_t SIZE = sizeof(coordinates_t);

    union register_t
    {
        uint8_t byte[SIZE];
        coordinates_t value;

        void initialize(void);

        void deserialize(uint8_t const *const);
        void serialize(uint8_t **) const;
    } __attribute__((packed));

    extern register_t g_register;
}
