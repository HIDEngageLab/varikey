/**
 * \file param_user.cpp
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

/**
    \brief Parameter "user register"

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#include <pico/stdlib.h>
#include <stddef.h>

#include "macros.hpp"
#include "param_user.hpp"
#include "parameter.hpp"

/** \brief Global user register parameter */
param_user_register_t g_user_register = {{0xff, 0xff}};

/**
    \brief Initialize with default values
*/
extern void param_user_init()
{
    g_user_register.value[0] = 0xff;
    g_user_register.value[1] = 0xff;
}

/**
    \brief Set test register value
*/
extern void param_user_deserialize(uint8_t const *const _space)
{
    /* ATTENTION: NO CHECKS */
    g_user_register.value[0] = _space[0];
    g_user_register.value[1] = _space[1];
}

/**
    \brief Serialize parameter value
*/
extern void param_user_serialize(uint8_t *const _space)
{
    /* ATTENTION: NO CHECKS */
    _space[0] = g_user_register.value[0];
    _space[1] = g_user_register.value[1];
}
