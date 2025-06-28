/**
 * \file varikey.c
 * \author Roman Koch
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#include "varikey.hpp"
#include "board_assembly.hpp"
#include "engine.hpp"
#include "keymatrix.hpp"
#include "keymatrix_queue.hpp"
#include "keymatrix_scanner.hpp"

#include <pico/multicore.h>

volatile bool scan_enabled = true;
volatile bool running_varikey = true;
volatile bool running_scanner = true;

void core1_main(void)
{
    keymatrix_init();
    keymatrix::init_queue();

    while (running_scanner)
    {
        if (scan_enabled)
        {
            // absolute_time_t start = get_absolute_time();

            keymatrix_scan();
            keymatrix_events();

            // absolute_time_t end = get_absolute_time();
            // printf("%d us\n", absolute_time_diff_us(start, end));
            sleep_us(500);
        }
        else
        {
            sleep_ms(100);
        }
    }
}

extern void varikey_loop(void)
{
    platform::board::assembly.initialize();
    engine::initialize();

    multicore_launch_core1(core1_main);

    //printf("Varikey started.\n");

    engine::start();

    while (running_varikey)
    {
    }
}

extern void varikey_shutdown(void)
{
    running_varikey = false;

    scan_enabled = false;
    running_scanner = false;

    engine::stop();
    while (engine::get_state() != engine::defines::STATE::IDLE)
        ;

    engine::shutdown();
    platform::board::assembly.shutdown();
}
