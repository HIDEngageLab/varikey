/**
 * \file param_features.cpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 * 
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

/**
    \brief Parameter "features"

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#include <pico/stdlib.h>
#include <stddef.h>

#include "macros.hpp"
#include "param_features.hpp"
#include "parameter.hpp"

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
