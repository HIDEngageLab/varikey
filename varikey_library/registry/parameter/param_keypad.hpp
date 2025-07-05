// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: Keypad parameter configuration
// SPDX-FileType: SOURCE

#pragma once

#include "parameter.hpp"

namespace registry::parameter::keypad
{
    struct keypad_t
    {
        uint16_t click_ms;
        uint16_t push_ms;
    } __attribute__((packed));

    static const size_t SIZE = sizeof(keypad_t);

    union register_t
    {
        uint8_t byte[SIZE];
        keypad_t value;

        void initialize(void);

        void deserialize(uint8_t const *const);
        void serialize(uint8_t **) const;
    } __attribute__((packed));

    extern register_t g_register;
}
