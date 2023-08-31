/**
 * \file param_button.c
 * \author Koch, Roman (koch.roman@googlemail.com)
 * \brief
 * \version 0.1
 * @date 2023-03-28
 *
 * @copyright Copyright (c) 2023
 *
 */
/**
    \brief Parameter "wheel"

    \internal
    \author Roman Koch, koch.roman@googlemail.com
*/

#include <pico/stdlib.h>
#include <string.h>

#include "param_key.h"
#include "types.h"

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
