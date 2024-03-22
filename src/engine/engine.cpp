/**
 * \file engine.cpp
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#include <stdlib.h>

#include "backlight3.hpp"
#include "board_assembly.hpp"
#include "cmd_control.hpp"
#include "display.hpp"
#include "display_font.hpp"
#include "engine.hpp"
#include "engine_event_handler.hpp"
#include "engine_variant.hpp"
#include "hid_handler.hpp"
#include "keypad.hpp"
#include "random.hpp"
#include "registry.hpp"
#include "serial.hpp"

namespace engine
{
    static defines::STATE state = defines::STATE::UNDEFINED;
    static defines::STATE next_state = defines::STATE::UNDEFINED;

    static bool wakeup_enabled_flag = false;

    static void tick(void);
    static void start_device_application();
    static void stop_device_application();

    extern void initialize(void)
    {
        assert(state == defines::STATE::UNDEFINED);
        state = defines::STATE::IDLE;

        random_init();
        serial::init();

        registry::initialize();
        backlight::initialize();
    }

    extern void start(void)
    {
        assert(state != defines::STATE::UNDEFINED);

        switch (state)
        {
        case defines::STATE::IDLE:
            /* TODO: autostart */
            next_state = defines::STATE::ACTIVE;
            /* start engine ticker */
            platform::board::assembly.soc.ticker_start(tick);
            break;
        case defines::STATE::ACTIVE:
            next_state = state;
            break;
        case defines::STATE::PENDING:
            next_state = state;
            break;
        case defines::STATE::SUSPEND:
            next_state = state;
            break;
        default:
            next_state = state;
            break;
        }
    }

    extern void stop(void)
    {
        assert(state != defines::STATE::UNDEFINED);

        switch (state)
        {
        case defines::STATE::IDLE:
            next_state = state;
            /* start engine ticker */
            platform::board::assembly.soc.ticker_stop();
            break;
        case defines::STATE::ACTIVE:
            next_state = defines::STATE::PENDING;
            break;
        case defines::STATE::PENDING:
            next_state = state;
            break;
        case defines::STATE::SUSPEND:
            next_state = state;
            break;
        default:
            next_state = state;
            break;
        }
    }

    extern void mount()
    {
        next_state = defines::STATE::ACTIVE;
    }

    extern void unmount()
    {
        next_state = defines::STATE::PENDING;
    }

    extern void suspend(const bool wakeup_enabled)
    {
        wakeup_enabled_flag = wakeup_enabled;
        next_state = defines::STATE::SUSPEND;
    }

    extern void resume()
    {
        next_state = defines::STATE::ACTIVE;
    }

    extern void shutdown(void)
    {
        /* todo: board shutdown */
    }

    extern void perform(void)
    {
        backlight::perform();
        handler::perform();
        serial::perform();

        switch (state)
        {
        case defines::STATE::IDLE:
            if (next_state == defines::STATE::ACTIVE)
            {
                state = next_state;
                next_state = defines::STATE::UNDEFINED;

                handler::set_hci_enabled(true);
                handler::set_hid_enabled(true);

                /* show state */
                start_device_application();

                engine::hci::cmd::control::gadget_indication(state);
            }
            break;
        case defines::STATE::ACTIVE:
            if (next_state == defines::STATE::PENDING)
            {
                state = next_state;
                next_state = defines::STATE::IDLE;
            }
            else if (next_state == defines::STATE::SUSPEND)
            {
                state = next_state;
                next_state = defines::STATE::UNDEFINED;

                handler::set_hci_enabled(false);
                handler::set_hid_enabled(false);

                engine::hci::cmd::control::gadget_indication(state);
            }
            break;
        case defines::STATE::PENDING:
            if (next_state == defines::STATE::IDLE)
            {
                /* todo: check event queue and execute lines below only if no more events exists */

                state = next_state;
                if (registry::parameter::features::g_register.value.autostart == ability_t::ENABLE)
                {
                    /* autostart */
                    next_state = defines::STATE::ACTIVE;
                }
                else
                {
                    /* true unmount */
                    next_state = defines::STATE::UNDEFINED;
                }

                handler::set_hci_enabled(false);
                handler::set_hid_enabled(false);

                /* show state */
                stop_device_application();

                engine::hci::cmd::control::gadget_indication(state);
            }
            break;
        case defines::STATE::SUSPEND:
            if (next_state == defines::STATE::PENDING)
            {
                state = next_state;
                next_state = defines::STATE::IDLE;
            }
            else if (next_state == defines::STATE::ACTIVE)
            {
                state = next_state;
                next_state = defines::STATE::UNDEFINED;

                handler::set_hci_enabled(true);
                handler::set_hid_enabled(true);

                engine::hci::cmd::control::gadget_indication(state);
            }

            break;
        default:
            next_state = defines::STATE::UNDEFINED;
            break;
        }
    }

    extern defines::STATE get_state(void)
    {
        return state;
    }

    static void tick(void)
    {
        platform::board::assembly.perform();
        perform();
    }

    static void start_device_application()
    {
        backlight::set_program(backlight::PROGRAM::TURBO, 0);

        display::set_cursor(0, 0);
        display::draw(engine::Variant::LOGO);
        display::set_cursor(engine::Variant::INTRO_ROW, engine::Variant::INTRO_COL);
        display::set_font(engine::Variant::FONT_SIZE);
        display::print(engine::Variant::INTRO);
    }

    static void stop_device_application()
    {
        backlight::set_program(backlight::PROGRAM::OFF, 0);
        display::clean();
    }

}