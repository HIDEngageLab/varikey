// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: Keymatrix core keymatrix core component functionality
// SPDX-FileType: SOURCE

#include <hardware/gpio.h>
#include <hardware/i2c.h>
#include <hardware/spi.h>
#include <pico/assert.h>
#include <pico/binary_info.h>
#include <pico/stdlib.h>

#include "hid_report.hpp"
#include "keypad.hpp"

#include "keymatrix_core.hpp"
#include "keymatrix_core_component.hpp"
#include "keymatrix_core_handler_type.hpp"
#include "keymatrix_core_type.hpp"

namespace platform::hardware
{
    int called_state = 0;

    static platform::hardware::KeyHandler key_handler;
    static void keymatrix_callback(uint gpio, uint32_t events);

    void KeymatrixCore::initialize()
    {
    }

    void KeymatrixCore::shutdown()
    {
    }

    bool KeymatrixCore::perform(void)
    {
        // if (called_state > 0)
        //{
        // called_state--;
        while (platform::hardware::protocol_core_has_event())
        {
            uint8_t state;
            uint8_t identifier;
            platform::hardware::protocol_core_get_event(&state, &identifier);

            pico::event_t event = {
                .identifier = static_cast<pico::event::IDENTIFIER>(identifier),
                .state = static_cast<pico::event::STATE>(state),
            };

            key_handler.event_handler(event);
        }

        return true;
        //}
        // else
        //{
        //    called_state = 0;
        //}

        return false;
    }

    static void keymatrix_callback(uint gpio, uint32_t events)
    {
        (void)events;
        (void)gpio;
        called_state++;
    }
}
