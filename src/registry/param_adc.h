/*
    GMC INSTRUMENTS, GMC-I Messtechnik GmbH
    Südwestpark 15, D-90449 Nürnberg, +4991186020, www.gossenmetrawatt.com
    Roman Koch, roman.koch@gossenmetrawatt.com, koch.roman@googlemail.com

    Copyright (c) 2019-2021 - All rights reserved
    Unauthorized copying of this file, via any medium is strictly prohibited
    Proprietary and confidential
*/
/**
    \brief Parameter "vref"

    \internal
    \author Roman Koch, koch.roman@googlemail.com
*/

#ifndef _PARAM_ADC_H_
#define _PARAM_ADC_H_

#include "parameter.h"

/**
    \brief Vref parameter

    Parameter with two float values for latitude and longitude.
*/
typedef union
{
    uint8_t byte[sizeof(float) * 2];
    /** \brief Node vref details */
    struct param_adc_struct
    {
        float reference;
        float wheel;
    } voltage;
} param_adc_t;

extern param_adc_t g_adc;

extern void param_adc_init(void);

extern void param_adc_deserialize(uint8_t const *const _space);
extern void param_adc_serialize(uint8_t *const _space);

#endif /* _PARAM_ADC_H_ */
