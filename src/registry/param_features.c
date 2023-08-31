/**
 * \file param_features.c
 * \author Koch, Roman (koch.roman@googlemail.com)
 * \brief
 * \version 0.1
 * @date 2023-03-28
 *
 * @copyright Copyright (c) 2023
 *
 */
/**
    \brief Parameter "features"

    \internal
    \author Roman Koch, koch.roman@googlemail.com
*/

#include <pico/stdlib.h>
#include <stddef.h>

#include "param_features.h"
#include "parameter.h"
#include "types.h"

param_features_t g_features = {0xff};

/**
    \brief Initialize features field with default values
*/
extern void param_features_init(void)
{
    g_features.features.autostart = ENABLE;
}

/**
    \brief Set features level parameter value
*/
extern void param_features_deserialize(uint8_t const *const _space)
{
    /* ATTENTION: NO CHECKS */
    g_features.byte = _space[0];
}

/**
    \brief Serialize parameter value
*/
extern void param_features_serialize(uint8_t *const _space)
{
    /* ATTENTION: NO CHECKS */
    _space[0] = g_features.byte;
}
