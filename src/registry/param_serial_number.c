/**
 * \file param_serial_number.c
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 *
 */
/**
    \brief Configuration parameter serial number

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#include <string.h>

#include <pico/stdlib.h>

#include "macros.h"
#include "param_serial_number.h"
#include "parameter.h"
#include "random.h"

uint32_t g_unique_key = KEY_VALUE_INVALID;
param_serial_number_t g_serial_number = {{0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff}};

/**
    \brief Initialize with default values
*/
extern void param_serial_number_init(void)
{
    chunk_t chunk = {g_serial_number.value, PARAMETER_SERIAL_NUMBER_SIZE};
    random_create_sequence(&chunk);
}

/**
    \brief Deserialize serial number value from chunk
*/
extern void param_serial_number_deserialize(uint8_t const *_space)
{
    /* ATTENTION: NO CHECKS */
    memcpy(g_serial_number.value, _space, PARAMETER_SERIAL_NUMBER_SIZE);
}

/**
    \brief Serialize serial number value to chunk
*/
extern void param_serial_number_serialize(uint8_t *_space)
{
    /* ATTENTION: NO CHECKS */
    memcpy(_space, g_serial_number.value, PARAMETER_SERIAL_NUMBER_SIZE);
}
