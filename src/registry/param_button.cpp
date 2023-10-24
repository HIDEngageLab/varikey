/**
 * \file param_button.cpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * \copyright Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

/**
    \brief Parameter "button"

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#include <pico/stdlib.h>
#include <string.h>

#include "param_button.hpp"

#define DEFAULT_CLICK_MS 128
#define DEFAULT_PUSH_MS 384

param_button_t g_button = {{0xff, 0xff, 0xff, 0xff}};

/**
    \brief initialize field with default values
*/
extern void param_button_init(void)
{
    g_button.button.click_ms = DEFAULT_CLICK_MS;
    g_button.button.push_ms = DEFAULT_PUSH_MS;
}

/**
    \brief Deserialize vwheel parameter value
*/
extern void param_button_deserialize(uint8_t const *const _space)
{
    /* ATTENTION: NO CHECKS */
    g_button.button.click_ms = SETWORD(_space[0], _space[1]);
    g_button.button.push_ms = SETWORD(_space[2], _space[3]);
}

/**
    \brief Serialize vwheel parameter value
*/
extern void param_button_serialize(uint8_t *const _space)
{
    /* ATTENTION: NO CHECKS */
    _space[0] = HIBYTE(g_button.button.click_ms);
    _space[1] = LOBYTE(g_button.button.click_ms);
    _space[2] = HIBYTE(g_button.button.push_ms);
    _space[3] = LOBYTE(g_button.button.push_ms);
}
