/**
 * \file param_adc.h
 * \author Koch, Roman (koch.roman@googlemail.com)
 * \brief
 * \version 0.1
 * @date 2023-03-28
 *
 * @copyright Copyright (c) 2023
 *
 */
/**
    \brief Parameter "backlight"

    \internal
    \author Roman Koch, koch.roman@googlemail.com
*/

#ifndef __PARAM_ADC_H__
#define __PARAM_ADC_H__

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

#endif /* __PARAM_ADC_H__ */
