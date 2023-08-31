/**
 * \file param_position.c
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * @copyright Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 *
 */
/**
    \brief Parameter "position"

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#include <pico/stdlib.h>
#include <string.h>

#include "macros.h"
#include "param_position.h"

#define MAGIC_LATITUDE 49.441607f
#define MAGIC_LONGITUDE 11.053841f

param_position_t g_position = {{0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff}};

/**
    \brief initialize field with default values

    magic values ;)
*/
extern void param_position_init(void)
{
    g_position.coordinates.latitude = MAGIC_LATITUDE;
    g_position.coordinates.longitude = MAGIC_LONGITUDE;
}

/**
    \brief Deserialize position parameter value
*/
extern void param_position_deserialize(uint8_t const *const _space)
{
    /* ATTENTION: NO CHECKS */
    memcpy(g_position.byte, _space, sizeof(param_position_t));
}

/**
    \brief Serialize position parameter value
*/
extern void param_position_serialize(uint8_t *const _space)
{
    /* ATTENTION: NO CHECKS */
    memcpy(_space, g_position.byte, sizeof(param_position_t));
}
