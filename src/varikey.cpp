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

static bool running = true;

int main(void)
{
    platform::board::assembly.initialize();
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
    platform::board::assembly.shutdown();
}
