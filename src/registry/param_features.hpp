/**
 * \file param_features.hpp
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

#ifndef __PARAM_FEATURES_HPP__
#define __PARAM_FEATURES_HPP__

#include "macros.hpp"
#include "parameter.hpp"

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

#endif /* __PARAM_FEATURES_HPP__ */
