/**
 * \file param_keypad.cpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * \copyright Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

/**
    \brief Parameter "keypad"

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#include <stdlib.h>
#include <string.h>

#include "keypad_keycode_type.hpp"
#include "param_keypad.hpp"

namespace registry
{
    namespace parameter
    {
        namespace keypad
        {
            register_t g_register = {.byte = {0xff, 0xff, 0xff, 0xff}};

            /**
                \brief Initialize field with default values
            */
            void register_t::initialize(void)
            {
                value.click_ms = engine::Keycode::DEFAULT_CLICK_MS;
                value.push_ms = engine::Keycode::DEFAULT_PUSH_MS;
            }

            /**
                \brief Deserialize parameter value
            */
            void register_t::deserialize(uint8_t const *const _space)
            {
                /* ATTENTION: NO CHECKS */
                const uint8_t *ptr = _space;
                value.click_ms = deserialize_word(&ptr);
                value.push_ms = deserialize_word(&ptr);
            }

            /**
                \brief Serialize parameter value
            */
            void register_t::serialize(uint8_t **_ptr) const
            {
                /* ATTENTION: NO CHECKS */
                serialize_word(value.click_ms, _ptr);
                serialize_word(value.push_ms, _ptr);
            }
        }
    }
}