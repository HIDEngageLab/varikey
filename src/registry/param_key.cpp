/**
 * \file param_key.cpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 * 
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

/**
    \brief Parameter "wheel"

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#include <pico/stdlib.h>
#include <string.h>

#include "macros.hpp"
#include "param_key.hpp"

#define DEFAULT_CLICK_MS 128
#define DEFAULT_PUSH_MS 384

param_key_t g_key = {{0xff, 0xff, 0xff, 0xff}};

/**
    \brief initialize field with default values
*/
extern void param_key_init(void)
{
    g_key.key.click_ms = DEFAULT_CLICK_MS;
    g_key.key.push_ms = DEFAULT_PUSH_MS;
}

/**
    \brief Deserialize wheel parameter value
*/
extern void param_key_deserialize(uint8_t const *const _space)
{
    /* ATTENTION: NO CHECKS */
    g_key.key.click_ms = SETWORD(_space[0], _space[1]);
    g_key.key.push_ms = SETWORD(_space[2], _space[3]);
}

/**
    \brief Serialize wheel parameter value
*/
extern void param_key_serialize(uint8_t *const _space)
{
    /* ATTENTION: NO CHECKS */
    _space[0] = HIBYTE(g_key.key.click_ms);
    _space[1] = LOBYTE(g_key.key.click_ms);
    _space[2] = HIBYTE(g_key.key.push_ms);
    _space[3] = LOBYTE(g_key.key.push_ms);
}
