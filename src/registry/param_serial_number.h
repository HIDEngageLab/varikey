/**
 * \file param_serial_number.h
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

#ifndef __PARAM_SERIAL_NUMBER_H__
#define __PARAM_SERIAL_NUMBER_H__

#include "parameter.h"

#ifndef KEY_VALUE_INVALID
#define KEY_VALUE_INVALID 0xffffffff
#define KEY_VALUE_MAX 0xffffffff
#define KEY_VALUE_MIN 0x00000000
#endif

#define PARAMETER_SERIAL_NUMBER_SIZE 12

/**
	\brief Serial number parameter

	Auto generated (read only) parameter with unique serial number
*/
typedef struct param_serial_number_struct
{
	uint8_t value[PARAMETER_SERIAL_NUMBER_SIZE];
} param_serial_number_t;

/** \brief Global serial number parameter */
extern param_serial_number_t g_serial_number;

/** \brief Global unique key parameter */
extern uint32_t g_unique_key;

extern void param_serial_number_init(void);

extern void param_serial_number_deserialize(uint8_t const *_space);
extern void param_serial_number_serialize(uint8_t *_space);

#endif /* __PARAM_SERIAL_NUMBER_H__ */
