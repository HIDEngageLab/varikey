/**
 * \file platform.c
 * \author Koch, Roman (koch.roman@googlemail.com)
 * \brief
 *
 * @copyright Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 *
 */

#include <stdio.h>

#include <hardware/gpio.h>
#include <hardware/i2c.h>
#include <hardware/spi.h>
#include <pico/assert.h>
#include <pico/binary_info.h>
#include <pico/stdlib.h>

#include "adp5585.h"
#include "chunk.h"
#include "display.h"
#include "images.h"
#include "keypad.h"
#include "platform.h"
#include "ssd1306.h"

#define _SCAN_I2C_BUS_FOR_DEVICES

typedef enum
{
    PLATFORM_STATE_UNDEFINED,
    PLATFORM_STATE_IDLE,
} state_t;

const int BACKLIGHT_PIN = 22;

const int AD5585_I2C_ADDRESS = 0x30;
const int AD5585_INT = 15;
const int AD5585_RST = 14;
const int PICO_I2C_SCL = 5;
const int PICO_I2C_SDA = 4;
const uint PICO_I2C_SPEED = (100 * 1000);

const int DISPLAY_CMD_SEL = 21;
const int DISPLAY_RESET = 20;
const int PICO_SPI_CS = 17;
const int PICO_SPI_SCK = 18;
const int PICO_SPI_TX = 19;
const uint PICO_SPI_SPEED = (10 * 1000 * 1000);

static state_t state = PLATFORM_STATE_UNDEFINED;

static bool scan_over_i2c(chunk_t *const _result);

extern void platform_init(void)
{
    // assert(state == PLATFORM_STATE_UNDEFINED); /* call in undefined state only */
    state = PLATFORM_STATE_IDLE;

    spi_init(spi_default, PICO_SPI_SPEED);
    gpio_set_function(PICO_DEFAULT_SPI_SCK_PIN, GPIO_FUNC_SPI);
    gpio_set_function(PICO_DEFAULT_SPI_TX_PIN, GPIO_FUNC_SPI);

    // Make the SPI pins available to picotool
    bi_decl(bi_2pins_with_func(PICO_DEFAULT_SPI_TX_PIN, PICO_DEFAULT_SPI_SCK_PIN, GPIO_FUNC_SPI));

    // Chip select is active-low, so we'll initialise it to a driven-high state
    gpio_init(PICO_DEFAULT_SPI_CSN_PIN);
    gpio_set_dir(PICO_DEFAULT_SPI_CSN_PIN, GPIO_OUT);
    gpio_put(PICO_DEFAULT_SPI_CSN_PIN, 1);

    // Make the CS pin available to picotool
    bi_decl(bi_1pin_with_name(PICO_DEFAULT_SPI_CSN_PIN, "SPI CS"));

    gpio_init(DISPLAY_RESET);
    gpio_set_dir(DISPLAY_RESET, GPIO_OUT);
    gpio_put(DISPLAY_RESET, 1);

    gpio_init(DISPLAY_CMD_SEL);
    gpio_set_dir(DISPLAY_CMD_SEL, GPIO_OUT);
    gpio_put(DISPLAY_CMD_SEL, 0);

    platform_ssd1306_init(DISPLAY_CMD_SEL);
    platform_ssd1306_clean();

    display_init();
    display_set_cursor(0, 0);
    display_draw(&LOGO);
    display_set_cursor(1, 30);
    display_set_font(FONT_HUGE);
    display_print("GMC-I");

    gpio_init(AD5585_RST);
    gpio_set_dir(AD5585_RST, GPIO_OUT);
    gpio_put(AD5585_RST, 1);

    gpio_set_function(PICO_I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(PICO_I2C_SCL, GPIO_FUNC_I2C);

    gpio_pull_up(PICO_I2C_SDA);
    gpio_pull_up(PICO_I2C_SCL);

    i2c_init(i2c_default, PICO_I2C_SPEED);

#if defined(SCAN_I2C_BUS_FOR_DEVICES)
    uint8_t devices_space[3];
    chunk_t devices = {devices_space, 3};
    while (!scan_over_i2c(&devices))
        ;
#endif

    gpio_set_dir(AD5585_INT, GPIO_IN);
    gpio_set_pulls(AD5585_INT, true, false);
    gpio_set_irq_enabled_with_callback(AD5585_INT, GPIO_IRQ_EDGE_FALL, true, &keypad_callback);

    gpio_put(AD5585_RST, 1);
    platform_adp5585_init(AD5585_I2C_ADDRESS);
}

extern void platform_shutdown(void)
{
    state = PLATFORM_STATE_UNDEFINED;

    gpio_put(AD5585_RST, 0);
    gpio_put(AD5585_INT, 0);
    gpio_set_irq_enabled(AD5585_INT, GPIO_IRQ_EDGE_FALL, false);
    gpio_set_irq_enabled(AD5585_INT, GPIO_IRQ_EDGE_FALL, false);

    gpio_put(DISPLAY_RESET, 1);
}

extern void platform_tick(void)
{
    // assert(state == PLATFORM_STATE_IDLE); /* call in ready state only */
}

static bool scan_over_i2c(chunk_t *const _result)
{
    bool found_flag = false;
    uint8_t result_address = 0;
    for (size_t i = 0; i < _result->size; ++i)
    {
        _result->space[i] = 0;
    }

    for (uint8_t addr = 0; addr < (1 << 7); ++addr)
    {
        // Skip over any reserved addresses.
        int ret;
        if ((addr & 0x78) == 0 || (addr & 0x78) == 0x78)
        {
            ret = PICO_ERROR_GENERIC;
        }
        else
        {
            uint8_t buffer;
            ret = i2c_read_blocking(i2c_default, addr, &buffer, 1, false);
            if (ret > 0)
            {
                found_flag = true;
                if (result_address < _result->size)
                {
                    _result->space[result_address++] = addr;
                }
            }
        }
    }

    return found_flag;
}
