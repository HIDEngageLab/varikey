/**
 * \file param_key.h
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 *
 */
/**
    \brief Parameter "key"

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#ifndef __PARAM_KEY_H__
#define __PARAM_KEY_H__

#include "parameter.h"

/**
    \brief Button parameter

    Parameter with two short values for button click and push times in ms.
*/
typedef union
{
    uint8_t byte[sizeof(uint16_t) * 2];
    /** \brief Node wheel details */
    struct param_key_struct
    {
        uint16_t click_ms;
        uint16_t push_ms;
    } key;
} param_key_t;

extern param_key_t g_key;

extern void param_key_init(void);

extern void param_key_deserialize(uint8_t const *const _space);
extern void param_key_serialize(uint8_t *const _space);

#endif /* __PARAM_KEY_H__ */
