/**
 * \file keypad_keycode_varikey.hpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#ifndef __ENGINE_KEYPAD_KEYCODE_VARIKEY_HPP__
#define __ENGINE_KEYPAD_KEYCODE_VARIKEY_HPP__

#include "keypad_keycode.hpp"

namespace engine
{
    namespace keypad
    {
        struct KeypadVarikey : public KeypadCode
        {
            static code_table_t number_value;
            static code_table_t telephon_value;
            static code_table_t functional_value;
            static code_table_t multimedia_value;
            static code_table_t navigation_value;
            static code_table_t custom_value;

            static const uint16_t DEFAULT_CLICK_MS{128};
            static const uint16_t DEFAULT_PUSH_MS{384};
        };
    }
}

#endif // __ENGINE_KEYPAD_KEYCODE_VARIKEY_HPP__
