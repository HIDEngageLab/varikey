/**
 * \file param_maintainer.cpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 * 
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

/**
    \brief Parameter "maintainer"

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#include <pico/stdlib.h>
#include <stddef.h>

#include "macros.hpp"
#include "param_maintainer.hpp"
#include "parameter.hpp"

#define PARAMETER_MAINTAINER_FW_REVISION_DEFAULT 0
#define PARAMETER_MAINTAINER_HW_REVISION_DEFAULT 0
#define PARAMETER_MAINTAINER_IDENTIFIER_DEFAULT 0x00

param_maintainer_t g_maintainer = {0};

/**
    \brief Initialize field with default values
*/
extern void param_maintainer_init(void)
{
    g_maintainer.maintainer.value = PARAMETER_MAINTAINER_IDENTIFIER_DEFAULT;
    g_maintainer.maintainer.hardware = PARAMETER_MAINTAINER_HW_REVISION_DEFAULT;
    g_maintainer.maintainer.protocol = PARAMETER_MAINTAINER_FW_REVISION_DEFAULT;
}

/**
    \brief Set maintainer parameter value
*/
extern void param_maintainer_deserialize(uint8_t const *const _space)
{
    /* ATTENTION: NO CHECKS */
    g_maintainer.byte = _space[0];
}

/**
    \brief Serialize maintainer parameter value
*/
extern void param_maintainer_serialize(uint8_t *const _space)
{
    /* ATTENTION: NO CHECKS */
    _space[0] = g_maintainer.byte;
}
