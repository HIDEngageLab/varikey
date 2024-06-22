/**
 * \file varikey.c
 * \author Roman Koch
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#include <assert.h>

#include "varikey.hpp"
#include "engine.hpp"
#include "platform.hpp"

enum STATE
{
    IDLE,
    ACTIVE,
};

STATE firmware_state = STATE::IDLE;

static bool running = true;

int main(void)
{
    varikey_initialize();
    while (running)
        ;

    return 0;
}

extern void varikey_initialize()
{
    assert(firmware_state == STATE::IDLE);
    firmware_state = STATE::ACTIVE;

    platform::initialize();
    engine::initialize();
    engine::start();
}

extern void varikey_shutdown()
{
    assert(firmware_state == STATE::ACTIVE);
    firmware_state = STATE::IDLE;

    engine::stop();
    while (engine::get_state() != engine::defines::STATE::IDLE)
        ;

    engine::shutdown();
    platform::shutdown();
}

extern void varikey_reboot(void)
{
    assert(firmware_state == STATE::IDLE);

    running = false;
    platform::reboot();
}

extern void varikey_bootsel(void)
{
    assert(firmware_state == STATE::IDLE);

    running = false;
    platform::bootsel();
}
