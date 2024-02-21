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
            register_t g_register = {{0xff, 0xff, 0xff, 0xff}};

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
                value.click_ms = SETWORD(_space[0], _space[1]);
                value.push_ms = SETWORD(_space[2], _space[3]);
            }

            /**
                \brief Serialize parameter value
            */
            void register_t::serialize(uint8_t *const _space) const
            {
                /* ATTENTION: NO CHECKS */
                _space[0] = HIBYTE(value.click_ms);
                _space[1] = LOBYTE(value.click_ms);
                _space[2] = HIBYTE(value.push_ms);
                _space[3] = LOBYTE(value.push_ms);
            }
        }
    }
}