/**
 * \file ws2812.h
 * \author Koch, Roman (koch.roman@googlemail.com)
 * \brief
 *
 * @copyright Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 *
 */

#ifndef __PLATFORM_WS2812_H__
#define __PLATFORM_WS2812_H__

#include <stdint.h>

extern void ws2812_init(void);
extern void ws2812_put_pixel(uint8_t r, uint8_t g, uint8_t b);

#endif // __PLATFORM_WS2812_H__
