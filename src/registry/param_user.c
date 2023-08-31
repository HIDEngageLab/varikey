/**
 * \file param_user.c
 * \author Koch, Roman (koch.roman@googlemail.com)
 * \brief
 * \version 0.1
 * @date 2023-03-28
 *
 * @copyright Copyright (c) 2023
 *
 */
/**
    \brief Parameter "user register"

    \internal
    \author Roman Koch, koch.roman@googlemail.com
*/

#include <pico/stdlib.h>
#include <stddef.h>

#include "param_user.h"
#include "parameter.h"
#include "types.h"

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
