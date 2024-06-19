/**
 * \file varikey.c
 * \author Roman Koch
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#include "varikey.hpp"
#include "engine.hpp"
#include "platform.hpp"

static bool running = true;

int main(void)
{
    platform::initialize();
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
    while (engine::get_state() != engine::defines::STATE::IDLE)
        ;

    engine::shutdown();
    platform::shutdown();
}

extern void varikey_bootsel(void)
{
    running = false;

    engine::stop();
    while (engine::get_state() != engine::defines::STATE::IDLE)
        ;

    engine::shutdown();
    platform::bootsel();
}
