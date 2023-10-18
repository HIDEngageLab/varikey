/**
 * \file param_adc.h
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 *
 */
/**
    \brief Parameter "backlight"

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#ifndef __PARAM_BACKLIGHT_H__
#define __PARAM_BACKLIGHT_H__

#include "parameter.h"

/**
    \brief Vref parameter

    Parameter with two float values for latitude and longitude.
*/
typedef union
{
    uint8_t byte[sizeof(float) * 2];
    /** \brief Node backlight details */
    struct param_backlight_struct
    {
        float reference;
        float wheel;
    } voltage;
} param_backlight_t;

extern param_backlight_t g_backlight;

extern void param_backlight_init(void);

extern void param_backlight_deserialize(uint8_t const *const _space);
extern void param_backlight_serialize(uint8_t *const _space);

#endif /* __PARAM_BACKLIGHT_H__ */
