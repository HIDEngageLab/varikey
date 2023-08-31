/**
 * \file platform.h
 * \author Koch, Roman (koch.roman@googlemail.com)
 * \brief
 *
 * @copyright Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 *
 */

#ifndef __PLATFORM_H__
#define __PLATFORM_H__

extern const int BACKLIGHT_PIN;

extern const int AD5585_I2C_ADDRESS;
extern const int AD5585_INT;
extern const int AD5585_RST;
extern const int PICO_I2C_SCL;
extern const int PICO_I2C_SDA;
extern const uint PICO_I2C_SPEED;

extern const int DISPLAY_CMD_SEL;
extern const int DISPLAY_RESET;
extern const int PICO_SPI_CS;
extern const int PICO_SPI_SCK;
extern const int PICO_SPI_TX;
extern const uint PICO_SPI_SPEED;

extern void platform_init(void);
extern void platform_shutdown(void);
extern void platform_tick(void);

#endif // __PLATFORM_H__
