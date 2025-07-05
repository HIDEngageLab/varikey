// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: keypad keycode 15sbla module
// SPDX-FileType: SOURCE

#pragma once

#include "keypad_keycode.hpp"

namespace engine::keypad
{
    struct Keypad15SBLA : public KeypadCode
    {
        static code_table_t number_value;
        static code_table_t telephon_value;
        static code_table_t functional_value;
        static code_table_t multimedia_value;
        static code_table_t navigation_value;

        static const uint16_t DEFAULT_CLICK_MS{128};
        static const uint16_t DEFAULT_PUSH_MS{384};
    };
}
