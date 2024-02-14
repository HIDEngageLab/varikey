/**
 * \file varikey.c
 * \author Roman Koch
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#include "varikey.hpp"
#include "board.hpp"
#include "engine.hpp"

static bool running = true;

int main(void)
{
    board_initialize();
    engine::initialize();
    engine::start();

    while (running)
        ;

    return 0;
}

extern void varikey_shutdown(void)
{
    running = false;

    engine::stop();
    engine::shutdown();
    board_shutdown();
}
