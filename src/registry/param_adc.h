/**
 * @file param_adc.h
 * @author Roman Koch, koch.roman@gmail.com
 * @brief 
 * @version 0.1
 * 
 * @copyright Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 * 
 */
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
