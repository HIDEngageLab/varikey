/**
 * \file adp5585.h
 * \author Koch, Roman (koch.roman@googlemail.com)
 * \brief
 * \version 0.1
 * @date 2023-03-28
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef __PLATFORM_ADP5585_H__
#define __PLATFORM_ADP5585_H__

#include <pico/stdlib.h>

extern void platform_adp5585_init(int const _address);

extern bool platform_adp5585_has_event(void);
extern void platform_adp5585_get_event(uint8_t *const _state, uint8_t *const _identifier);

#endif // __PLATFORM_ADP5585_H__