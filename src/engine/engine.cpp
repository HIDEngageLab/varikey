/**
 * \file engine.cpp
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#include <stdlib.h>

#include "backlight3.hpp"
#include "board.hpp"
#include "display.hpp"
#include "display_font.hpp"
#include "engine.hpp"
#include "engine_event_handler.hpp"
#include "hid_handler.hpp"
#include "keypad.hpp"
#include "random.hpp"
#include "registry.hpp"
#include "serial.hpp"

namespace engine
{
    static defines::STATE mode = defines::STATE::UNDEFINED;
    static defines::STATE next_mode = defines::STATE::UNDEFINED;

    static bool wakeup_enabled_flag = false;

    static void tick(void);
    static void start_device_application();
    static void stop_device_application();
    static void push_gadget_event(const payload::gadget::COMMAND);

    extern void initialize(void)
    {
        assert(mode == defines::STATE::UNDEFINED);
        mode = defines::STATE::IDLE;

        random_init();
        registry::initialize();
        backlight::initialize();

        serial_init();
    }

    extern void start(void)
    {
        assert(mode != defines::STATE::UNDEFINED);

        switch (mode)
        {
        case defines::STATE::IDLE:
            next_mode = defines::STATE::ACTIVE;
            /* start engine ticker */
            board.soc.ticker_start(tick);
            break;
        case defines::STATE::ACTIVE:
            next_mode = mode;
            break;
        case defines::STATE::PENDING:
            next_mode = mode;
            break;
        default:
            next_mode = mode;
            break;
        }
    }

    extern void stop(void)
    {
        assert(mode != defines::STATE::UNDEFINED);

        switch (mode)
        {
        case defines::STATE::IDLE:
            next_mode = mode;
            break;
        case defines::STATE::ACTIVE:
            next_mode = defines::STATE::PENDING;
            break;
        case defines::STATE::PENDING:
            next_mode = mode;
            break;
        default:
            next_mode = mode;
            break;
        }
    }

    extern void unmount()
    {
        push_gadget_event(payload::gadget::COMMAND::UNMOUNT);
    }

    extern void mount()
    {
        push_gadget_event(payload::gadget::COMMAND::MOUNT);
    }

    extern void suspend(const bool wakeup_enabled)
    {
        wakeup_enabled_flag = wakeup_enabled;
        push_gadget_event(payload::gadget::COMMAND::SUSPEND);
    }

    extern void resume()
    {
        push_gadget_event(payload::gadget::COMMAND::RESUME);
    }

    extern void shutdown(void)
    {
        /* todo: board shutdown */
    }

    extern void perform(void)
    {
        switch (mode)
        {
        case defines::STATE::IDLE:
            if (next_mode == defines::STATE::ACTIVE)
            {
                mode = next_mode;
                next_mode = defines::STATE::UNDEFINED;

                /* show state */
                start_device_application();
            }
            break;
        case defines::STATE::ACTIVE:
            backlight::perform();
            handler::perform();
            serial_perform();

            if (next_mode == defines::STATE::PENDING)
            {
                mode = next_mode;
                next_mode = defines::STATE::IDLE;
            }
            break;
        case defines::STATE::PENDING:
            if (next_mode == defines::STATE::IDLE)
            {
                /* todo: check event queue and execute lines below only if no more events exists */

                mode = next_mode;
                next_mode = defines::STATE::UNDEFINED;

                /* start engine ticker */
                board.soc.ticker_stop();

                /* show state */
                stop_device_application();
            }
            break;
        default:
            next_mode = defines::STATE::UNDEFINED;
            break;
        }
    }

    extern defines::STATE get_mode(void)
    {
        return mode;
    }

    static void tick(void)
    {
        board_perform();
        perform();
    }

    static void start_device_application()
    {
        backlight::set_mode(backlight::MODE::TURBO, 0);

        display::set_cursor(0, 0);
        display::draw(platform::Board::LOGO);
        display::set_cursor(1, platform::Board::POSITION);
        display::set_font(engine::display::FONT::BIG);
        display::print(platform::Board::INTRO);
    }

    static void stop_device_application()
    {
        backlight::set_mode(backlight::MODE::OFF, 0);
        display::clean();
    }

    static void push_gadget_event(const payload::gadget::COMMAND _identifier)
    {
        const engine::handler::event_t event = {
            .identifier = payload::IDENTIFIER::GADGET,
            .gadget = {
                .command = _identifier,
            }};
        engine::handler::event_queue.push(event);
    }
}