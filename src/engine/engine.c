/**
 * \file engine.c
 * \author Koch, Roman (koch.roman@googlemail.com)
 * \brief
 * \version 0.1
 * @date 2023-03-28
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <pico/stdlib.h>

#include "engine.h"
#include "platform.h"

static engine_mode_t mode = ENGINE_MODE_UNDEFINED;
static engine_mode_t next_mode = ENGINE_MODE_UNDEFINED;

extern void engine_init(void)
{
    assert(mode == ENGINE_MODE_UNDEFINED);
    mode = ENGINE_MODE_IDLE;

    /* todo: init storage/registry */

    /* todo: board init (hardware) */
    platform_init();
}

extern void engine_start(void)
{
    assert(mode != ENGINE_MODE_UNDEFINED);

    switch (mode)
    {
    case ENGINE_MODE_IDLE:
        next_mode = ENGINE_MODE_ACTIVE;
        break;
    case ENGINE_MODE_ACTIVE:
        next_mode = mode;
        break;
    case ENGINE_MODE_PENDING:
        next_mode = mode;
        break;
    default:
        next_mode = mode;
        break;
    }
}

extern void engine_stop(void)
{
    assert(mode != ENGINE_MODE_UNDEFINED);

    switch (mode)
    {
    case ENGINE_MODE_IDLE:
        next_mode = mode;
        break;
    case ENGINE_MODE_ACTIVE:
        next_mode = ENGINE_MODE_PENDING;
        break;
    case ENGINE_MODE_PENDING:
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
    case ENGINE_MODE_IDLE:
        if (next_mode == ENGINE_MODE_ACTIVE)
        {
            mode = next_mode;
            next_mode = ENGINE_MODE_UNDEFINED;

            /* show current state */
        }
        break;
    case ENGINE_MODE_ACTIVE:
        if (next_mode == ENGINE_MODE_PENDING)
        {
            mode = next_mode;
            next_mode = ENGINE_MODE_IDLE;
        }
        break;
    case ENGINE_MODE_PENDING:
        if (next_mode == ENGINE_MODE_IDLE)
        {
            /* todo: check event queue and execute lines below only if no more events exists */

            mode = next_mode;
            next_mode = ENGINE_MODE_UNDEFINED;

            /* show current state */
        }
        break;
    default:
        next_mode = ENGINE_MODE_UNDEFINED;
        break;
    }
}

extern void engine_tick(void)
{
    if (mode != ENGINE_MODE_UNDEFINED)
    {
        /* todo: board tick */
    }
}

extern engine_mode_t engine_mode_get(void)
{
    return mode;
}
