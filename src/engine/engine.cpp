/**
 * \file engine.cpp
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#include <pico/stdlib.h>

#include "backlight3.hpp"
#include "board.hpp"
#include "display.hpp"
#include "engine.hpp"
#include "keypad.hpp"
#include "random.hpp"
#include "registry.hpp"

static pulp::COMPONENT_STATE mode = pulp::COMPONENT_STATE::UNDEFINED;
static pulp::COMPONENT_STATE next_mode = pulp::COMPONENT_STATE::UNDEFINED;

static void start_device_application()
{
    backlight_mode(BACKLIGHT_PROGRAM_TURBO, 0);

    display_set_cursor(0, 0);
    display_draw(platform::Board::LOGO);
    display_set_cursor(1, platform::Board::POSITION);
    display_set_font(FONT_SIZE::FONT_BIG);
    display_print(platform::Board::INTRO);
}

static void stop_device_application()
{
    backlight_mode(BACKLIGHT_OFF, 0);
    display_clean();
}

extern void engine_initialize(void)
{
    assert(mode == pulp::COMPONENT_STATE::UNDEFINED);
    mode = pulp::COMPONENT_STATE::IDLE;

    random_init();
    registry_init();

    backlight_init();

    /* todo: init storage/registry */
}

extern void engine_start(void)
{
    assert(mode != pulp::COMPONENT_STATE::UNDEFINED);

    switch (mode)
    {
    case pulp::COMPONENT_STATE::IDLE:
        next_mode = pulp::COMPONENT_STATE::ACTIVE;
        /* start engine ticker */
        board.soc.ticker.start(engine_tick);
        break;
    case pulp::COMPONENT_STATE::ACTIVE:
        next_mode = mode;
        break;
    case pulp::COMPONENT_STATE::PENDING:
        next_mode = mode;
        break;
    default:
        next_mode = mode;
        break;
    }
}

extern void engine_stop(void)
{
    assert(mode != pulp::COMPONENT_STATE::UNDEFINED);

    switch (mode)
    {
    case pulp::COMPONENT_STATE::IDLE:
        next_mode = mode;
        break;
    case pulp::COMPONENT_STATE::ACTIVE:
        next_mode = pulp::COMPONENT_STATE::PENDING;
        break;
    case pulp::COMPONENT_STATE::PENDING:
        next_mode = mode;
        break;
    default:
        next_mode = mode;
        break;
    }
}

extern void engine_shutdown(void)
{
    /* todo: board shutdown */
}

extern void engine_perform(void)
{
    switch (mode)
    {
    case pulp::COMPONENT_STATE::IDLE:
        if (next_mode == pulp::COMPONENT_STATE::ACTIVE)
        {
            mode = next_mode;
            next_mode = pulp::COMPONENT_STATE::UNDEFINED;

            /* show state */
            start_device_application();
        }
        break;
    case pulp::COMPONENT_STATE::ACTIVE:
        backlight_perform();
        keypad_perform();

        if (next_mode == pulp::COMPONENT_STATE::PENDING)
        {
            mode = next_mode;
            next_mode = pulp::COMPONENT_STATE::IDLE;
        }
        break;
    case pulp::COMPONENT_STATE::PENDING:
        if (next_mode == pulp::COMPONENT_STATE::IDLE)
        {
            /* todo: check event queue and execute lines below only if no more events exists */

            mode = next_mode;
            next_mode = pulp::COMPONENT_STATE::UNDEFINED;

            /* start engine ticker */
            board.soc.ticker.stop();

            /* show state */
            stop_device_application();
        }
        break;
    default:
        next_mode = pulp::COMPONENT_STATE::UNDEFINED;
        break;
    }
}

extern void engine_tick(void)
{
    board_perform();
    engine_perform();
}

extern pulp::COMPONENT_STATE engine_mode_get(void)
{
    return mode;
}
