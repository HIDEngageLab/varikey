/**
 * \file param_display.cpp
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
#include "param_display.hpp"

#define DEFAULT_CLICK_MS 128
#define DEFAULT_PUSH_MS 384

param_display_t g_display = {{0xff, 0xff, 0xff, 0xff}};

/**
    \brief initialize field with default values
*/
extern void param_display_init(void)
{
    g_display.display.click_ms = DEFAULT_CLICK_MS;
    g_display.display.push_ms = DEFAULT_PUSH_MS;
}

/**
    \brief Deserialize wheel parameter value
*/
extern void param_display_deserialize(uint8_t const *const _space)
{
    /* ATTENTION: NO CHECKS */
    g_display.display.click_ms = SETWORD(_space[0], _space[1]);
    g_display.display.push_ms = SETWORD(_space[2], _space[3]);
}

/**
    \brief Serialize wheel parameter value
*/
extern void param_display_serialize(uint8_t *const _space)
{
    /* ATTENTION: NO CHECKS */
    _space[0] = HIBYTE(g_display.display.click_ms);
    _space[1] = LOBYTE(g_display.display.click_ms);
    _space[2] = HIBYTE(g_display.display.push_ms);
    _space[3] = LOBYTE(g_display.display.push_ms);
}
