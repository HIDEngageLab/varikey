/**
 * \file ws2812.c
 * \author Koch, Roman (koch.roman@googlemail.com)
 * \brief
 *
 * @copyright Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 *
 */

#include <stdio.h>
#include <stdlib.h>

#include <hardware/clocks.h>
#include <hardware/pio.h>
#include <pico/stdlib.h>

#include "macros.h"
#include "platform.h"
#include "ws2812.pio.h"

const float LUM_R = 1.400;
const float LUM_G = 0.700;
const float LUM_B = 0.400;

const float LUM_R_FACTOR = 1.400;
const float LUM_G_FACTOR = 0.700;
const float LUM_B_FAKTOR = 0.400;

extern void ws2812_init(void)
{
  PIO pio = pio0;
  int sm = 0;
  uint offset = pio_add_program(pio, &ws2812_program);
  ws2812_program_init(pio, sm, offset, BACKLIGHT_PIN, 800000, false);
  pio_sm_clear_fifos(pio, sm);
}

extern void ws2812_put_pixel(uint8_t r, uint8_t g, uint8_t b)
{
  uint32_t color = ((uint32_t)(r) << 8) |
                   ((uint32_t)(g) << 16) |
                   (uint32_t)(b);
  pio_sm_put_blocking(pio0, 0, color << 8u);
}
