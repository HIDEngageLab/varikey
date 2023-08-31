/**
 * \file ssd1306.h
 * \author Koch, Roman (koch.roman@googlemail.com)
 * \brief
 * \version 0.1
 * @date 2023-03-28
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef __PLATFORM_SSD1306_H__
#define __PLATFORM_SSD1306_H__

#include <stdint.h>

extern void platform_ssd1306_init(uint8_t data_command_select_pin);

extern void platform_ssd1306_clean(void);
extern void platform_ssd1306_mask(uint8_t const *const image);
extern void platform_ssd1306_symbol(uint8_t const page_start, uint8_t const page_end, uint8_t const column_start, uint8_t const column_end, uint8_t const *const data, uint8_t const len);
extern void platform_ssd1306_set_inverse(void);
extern void platform_ssd1306_set_normal(void);

extern void platform_ssd1306_perform(void);

#endif // __PLATFORM_SSD1306_H__
