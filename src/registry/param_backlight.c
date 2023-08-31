/**
 * \file param_adc.c
 * \author Koch, Roman (koch.roman@googlemail.com)
 * \brief
 * \version 0.1
 * @date 2023-03-28
 *
 * @copyright Copyright (c) 2023
 *
 */
/**
    \brief Parameter "vref"

    \internal
    \author Roman Koch, koch.roman@googlemail.com
*/

#include <pico/stdlib.h>
#include <string.h>

#include "param_backlight.h"
#include "types.h"

#define DEFAULT_REFERENCE 5.0f
#define DEFAULT_WHEEL 1.8f

param_backlight_t g_backlight = {{0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff}};

/**
    \brief initialize field with default values

    magic values ;)
*/
extern void param_backlight_init(void)
{
    g_backlight.voltage.reference = DEFAULT_REFERENCE;
    g_backlight.voltage.wheel = DEFAULT_WHEEL;
}

/**
    \brief Deserialize vref parameter value
*/
extern void param_backlight_deserialize(uint8_t const *const _space)
{
    /* ATTENTION: NO CHECKS */
    memcpy(g_backlight.byte, _space, sizeof(param_backlight_t));
}

/**
    \brief Serialize vref parameter value
*/
extern void param_backlight_serialize(uint8_t *const _space)
{
    /* ATTENTION: NO CHECKS */
    memcpy(_space, g_backlight.byte, sizeof(param_backlight_t));
}
