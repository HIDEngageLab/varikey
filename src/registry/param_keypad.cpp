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

#include "param_keypad.hpp"

namespace registry
{
    namespace parameter
    {
        namespace keypad
        {
            static const uint16_t DEFAULT_CLICK_MS = 128;
            static const uint16_t DEFAULT_PUSH_MS = 384;

            register_t g_register = {{0xff, 0xff, 0xff, 0xff}};

            /**
                \brief initialize field with default values
            */
            extern void initialize(void)
            {
                g_register.keypad.click_ms = DEFAULT_CLICK_MS;
                g_register.keypad.push_ms = DEFAULT_PUSH_MS;
            }

            /**
                \brief Deserialize wheel parameter value
            */
            extern void deserialize(uint8_t const *const _space)
            {
                /* ATTENTION: NO CHECKS */
                g_register.keypad.click_ms = SETWORD(_space[0], _space[1]);
                g_register.keypad.push_ms = SETWORD(_space[2], _space[3]);
            }

            /**
                \brief Serialize wheel parameter value
            */
            extern void serialize(uint8_t *const _space)
            {
                /* ATTENTION: NO CHECKS */
                _space[0] = HIBYTE(g_register.keypad.click_ms);
                _space[1] = LOBYTE(g_register.keypad.click_ms);
                _space[2] = HIBYTE(g_register.keypad.push_ms);
                _space[3] = LOBYTE(g_register.keypad.push_ms);
            }
        }
    }
}