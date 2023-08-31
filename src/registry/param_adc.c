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

#include <string.h>
#include <pico/stdlib.h>
#include "../pulp/types.h"
#include "param_adc.h"

#define DEFAULT_REFERENCE 5.0f
#define DEFAULT_WHEEL 1.8f

param_adc_t g_adc = {{0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff}};

/**
    \brief initialize field with default values

    magic values ;)
*/
extern void param_adc_init(void)
{
    g_adc.voltage.reference = DEFAULT_REFERENCE;
    g_adc.voltage.wheel = DEFAULT_WHEEL;
}

/**
    \brief Deserialize vref parameter value
*/
extern void param_adc_deserialize(uint8_t const *const _space)
{
    /* ATTENTION: NO CHECKS */
    memcpy(g_adc.byte, _space, sizeof(param_adc_t));
}

/**
    \brief Serialize vref parameter value
*/
extern void param_adc_serialize(uint8_t *const _space)
{
    /* ATTENTION: NO CHECKS */
    memcpy(_space, g_adc.byte, sizeof(param_adc_t));
}
