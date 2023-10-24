/**
 * \file composed_hid.c
 * \author Roman Koch
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#include "composed_hid.hpp"
#include "board.hpp"
#include "engine.hpp"

static bool running = true;

int main(void)
{
    board_initialize();
    engine_initialize();
    engine_start();

    while (running)
        ;

    return 0;
}

extern void composed_hid_shutdown(void)
{
    running = false;

    engine_stop();
    engine_shutdown();
    board_shutdown();
}
