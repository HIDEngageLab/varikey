/**
 * \file param_serial_number.c
 * \author Koch, Roman (koch.roman@googlemail.com)
 * \brief
 * \version 0.1
 * @date 2023-03-28
 *
 * @copyright Copyright (c) 2023
 *
 */
/**
    \brief Configuration parameter serial number

    \internal
    \author Roman Koch, koch.roman@googlemail.com
*/

#include <string.h>

#include <pico/stdlib.h>

#include "param_serial_number.h"
#include "parameter.h"
#include "random.h"
#include "types.h"

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
