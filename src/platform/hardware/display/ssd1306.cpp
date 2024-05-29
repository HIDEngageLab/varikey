/**
 * \file ssd1306.cpp
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#include <hardware/gpio.h>
#include <hardware/spi.h>
#include <pico/time.h>

#include "ssd1306.hpp"

#define OLED_CHARGE_PUMP 0x8D
#define OLED_DISP_NOR 0xA6
#define OLED_DISP_OFF 0xAE
#define OLED_DISP_ON 0xAF
#define OLED_DISP_REV 0xA7
#define OLED_EON_OFF 0xA4
#define OLED_EON_ON 0xA5
#define OLED_MEM_ADDRESSING 0x20
#define OLED_MULTIPLEX 0xA8
#define OLED_NOP 0xE3
#define OLED_PUMP_OFF 0x10
#define OLED_PUMP_ON 0x14
#define OLED_SCROLL_LEFT 0x27
#define OLED_SCROLL_OFF 0x2E
#define OLED_SCROLL_ON 0x2F
#define OLED_SCROLL_ON 0x2F
#define OLED_SCROLL_RIGHT 0x26
#define OLED_SCROLL_VL 0x2A
#define OLED_SCROLL_VR 0x29
#define OLED_SET_CHARGE 0xD9
#define OLED_SET_COL_ADDR 0x21
#define OLED_SET_COL_HI 0x10
#define OLED_SET_COL_LO 0x00
#define OLED_SET_CONTRAST 0x81
#define OLED_SET_LINE 0x40
#define OLED_SET_OFFSET 0xD3
#define OLED_SET_PADS 0xDA
#define OLED_SET_PAGE 0xB0
#define OLED_SET_PAGE_ADDR 0x22
#define OLED_SET_RATIO_OSC 0xD5
#define OLED_SET_SCAN_FLIP 0xC0
#define OLED_SET_SCAN_NOR 0xC8
#define OLED_SET_SEG_REMAP0 0xA0
#define OLED_SET_SEG_REMAP1 0xA1
#define OLED_SET_VCOM 0xDB
#define OLED_VERT_SCROLL_A 0xA3

#define WIDTH 128
#define HEIGHT 32
#define PAGES (HEIGHT / 8)

namespace platform
{
    namespace hardware
    {
        namespace ssd1306
        {
            uint8_t DATA_COMMAND_PIN = 0xff;
            uint8_t SPI_CSN_PIN = PICO_DEFAULT_SPI_CSN_PIN;

            static void select_command_mode()
            {
                gpio_put(DATA_COMMAND_PIN, 0);
            }
            static void select_data_mode()
            {
                gpio_put(DATA_COMMAND_PIN, 1);
            }

            static inline void chip_select()
            {
                asm volatile("nop \n nop \n nop");
                gpio_put(SPI_CSN_PIN, 0); // Active low
                asm volatile("nop \n nop \n nop");
            }

            static inline void chip_deselect()
            {
                asm volatile("nop \n nop \n nop");
                gpio_put(SPI_CSN_PIN, 1);
                asm volatile("nop \n nop \n nop");
            }

            static void write_byte(const uint8_t byte)
            {
                spi_write_blocking(spi_default, &byte, 1);
            }

            static void write_byte2(const uint8_t byte1, uint8_t byte2)
            {
                uint8_t buf[] = {byte1, byte2};
                spi_write_blocking(spi_default, buf, 2);
            }

            static void write_byte3(const uint8_t byte1, const uint8_t byte2, const uint8_t byte3)
            {
                uint8_t buf[] = {byte1, byte2, byte3};
                spi_write_blocking(spi_default, buf, 3);
            }

            extern void initialize(const uint8_t _data_command_pin, const uint8_t _spi_csn_pin)
            {
                DATA_COMMAND_PIN = _data_command_pin;
                SPI_CSN_PIN = _spi_csn_pin;

                select_command_mode();

                chip_select();

                write_byte(OLED_DISP_OFF);
                write_byte2(OLED_SET_RATIO_OSC, 0x80);
                write_byte2(OLED_MULTIPLEX, 0x1F);
                write_byte2(OLED_SET_OFFSET, 0x00);
                write_byte(OLED_SET_LINE);
                write_byte(OLED_SET_SEG_REMAP1);
                write_byte2(OLED_CHARGE_PUMP, 0x14);
                write_byte(OLED_PUMP_ON);
                write_byte(OLED_SET_SCAN_NOR);
                write_byte2(OLED_SET_PADS, 0x02);
                write_byte2(OLED_SET_CONTRAST, 0x8f);
                write_byte2(OLED_SET_CHARGE, 0x22);
                write_byte2(OLED_SET_VCOM, 0x40);
                write_byte(OLED_EON_OFF);
                write_byte(OLED_DISP_NOR);
                write_byte(OLED_DISP_ON);
                write_byte2(OLED_MEM_ADDRESSING, 0x00);

                chip_deselect();
                sleep_ms(1);
            }

            extern void clean(void)
            {
                select_command_mode();
                chip_select();
                write_byte2(OLED_MEM_ADDRESSING, 0x00);
                write_byte(OLED_SET_PAGE + 0);
                write_byte(OLED_SET_COL_LO);
                write_byte(OLED_SET_COL_HI);
                write_byte3(OLED_SET_COL_ADDR, 0, 127);
                write_byte3(OLED_SET_PAGE_ADDR, 0, 3);

                select_data_mode();
                for (uint8_t page = 0; page < PAGES; ++page)
                {
                    for (uint8_t column = 0; column < WIDTH; ++column)
                    {
                        write_byte(0x00);
                    }
                }
                chip_deselect();
            }

            /**
             * \brief Draw mask
             *
             * Attention: image should be rotated by -90 degree.
             * Example:
             * for a display with 128x32 (cols x rows) pixel is proper image size 32 x 128
             * the first line in display is a last column in a image
             *
             * @param image
             */
            static void draw_mask_00(uint8_t const *const image)
            {
                select_command_mode();
                chip_select();
                write_byte2(OLED_MEM_ADDRESSING, 0x00);
                write_byte(OLED_SET_PAGE);
                write_byte(OLED_SET_COL_LO);
                write_byte(OLED_SET_COL_HI);
                write_byte3(OLED_SET_COL_ADDR, 0, 127);
                write_byte3(OLED_SET_PAGE_ADDR, 0, 3);

                select_data_mode();
                for (uint8_t page = 0; page < PAGES; ++page)
                {
                    for (uint8_t column = 0; column < WIDTH; ++column)
                    {
                        uint8_t tmp = image[(3 - page) + column * 4];
                        write_byte(tmp);
                    }
                }
                chip_deselect();
            }

            static void draw_mask_01(uint8_t const *const image)
            {
                select_command_mode();
                chip_select();
                write_byte2(OLED_MEM_ADDRESSING, 0x01);
                write_byte(OLED_SET_PAGE);
                write_byte(OLED_SET_COL_LO);
                write_byte(OLED_SET_COL_HI);
                write_byte3(OLED_SET_COL_ADDR, 0, 127);
                write_byte3(OLED_SET_PAGE_ADDR, 0, 3);

                select_data_mode();
                for (uint8_t column = 0; column < WIDTH; ++column)
                {
                    for (uint8_t page = 0; page < PAGES; ++page)
                    {
                        uint8_t tmp = image[(3 - page) + column * 4];
                        write_byte(tmp);
                    }
                }
                chip_deselect();
            }

            extern void mask(uint8_t const *const image)
            {
                draw_mask_01(image);
            }

            extern void symbol(uint8_t const page_start, uint8_t const page_end,
                               uint8_t const column_start, uint8_t const column_end,
                               uint8_t const *const data, size_t const len)
            {
                select_command_mode();
                chip_select();
                write_byte2(OLED_MEM_ADDRESSING, 0x01);
                write_byte3(OLED_SET_PAGE_ADDR, page_start, page_end);
                write_byte3(OLED_SET_COL_ADDR, column_start, column_end);

                select_data_mode();
                for (size_t index = 0; index < len; ++index)
                {
                    const uint8_t x = data[index];
                    write_byte(x);
                }

                select_command_mode();
                write_byte3(OLED_SET_PAGE_ADDR, 0, 3);
                write_byte3(OLED_SET_COL_ADDR, 0, 127);
                chip_deselect();
            }

            extern void set_inverse(void)
            {
                select_command_mode();
                chip_select();
                write_byte(OLED_DISP_OFF);
                write_byte(OLED_DISP_REV);
                write_byte(OLED_DISP_ON);
                chip_deselect();
            }

            extern void set_normal(void)
            {
                select_command_mode();
                chip_select();
                write_byte(OLED_DISP_OFF);
                write_byte(OLED_DISP_NOR);
                write_byte(OLED_DISP_ON);
                chip_deselect();
            }
        }
    }
}