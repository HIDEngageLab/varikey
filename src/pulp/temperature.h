/**
 * \file temperature.h
 * \author Koch, Roman (koch.roman@googlemail.com)
 * \brief
 *
 * @copyright Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 *
 */
/**
	\brief Handle internal temperature sensor

	\internal
	\author Roman Koch, koch.roman@googlemail.com
*/

#ifndef __PULP_TEMPERATURE_H__
#define __PULP_TEMPERATURE_H__

#include <stdint.h>

extern void temperature_init(void);
extern uint16_t temperature_get_raw_value(void);
extern float temperature_get(void);
extern uint8_t temperature_create_random_byte(void);

#endif /* __PULP_TEMPERATURE_H__ */
