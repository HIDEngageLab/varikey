/**
 * \file composed_hid.c
 * \author Koch, Roman (koch.roman@googlemail.com)
 * \brief
 *
 * @copyright Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#include <hardware/exception.h>
#include <hardware/watchdog.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bsp/board.h"
#include "tusb.h"

#include "adp5585.h"
#include "backlight.h"
#include "composed_hid.h"
#include "engine.h"
#include "hardware/uart.h"
#include "keyboard.h"
#include "keypad.h"
#include "platform.h"
#include "random.h"
#include "registry.h"
#include "ssd1306.h"
#include "temperature.h"

static bool running = true;

int main(void)
{
    board_init();
    uart_init(uart0, 115200);
    tusb_init();
    while (!tusb_inited())
        ;

    temperature_init();

    random_init();
    registry_init();

    backlight_init();
    backlight_mode(BACKLIGHT_PROGRAM_TURBO, 0);
    platform_init();

    watchdog_enable(5000, true);
    while (running)
    {
        tud_task(); // tinyusb device task

        backlight_perform();
        keypad_perform();
        keyboard_perform();

        watchdog_update();
        sleep_ms(1);
    }

    return 0;
}

extern void composed_hid_device_shutdown(void)
{
    running = false;

    engine_shutdown();

    // usart_shutdown();

    sleep_ms(200);

    watchdog_enable(0, false);
    while (true)
        ;
}
