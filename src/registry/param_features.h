/**
 * \file param_features.h
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * @copyright Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 *
 */
/**
    \brief Parameter "features"

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#ifndef __PARAM_FEATURES_H__
#define __PARAM_FEATURES_H__

#include "macros.h"
#include "parameter.h"

/** \brief Features parameter */
typedef union
{
    uint8_t byte;
    /** \brief Node features details */
    struct param_features_struct
    {
        ability_t autostart : 1;
        uint8_t reserved : 7;
    } features;
} param_features_t;

/** \brief Global parameter "features" */
extern param_features_t g_features;

extern void param_features_init(void);

extern void param_features_deserialize(uint8_t const *const _space);
extern void param_features_serialize(uint8_t *const _space);

#endif /* __PARAM_FEATURES_H__ */
