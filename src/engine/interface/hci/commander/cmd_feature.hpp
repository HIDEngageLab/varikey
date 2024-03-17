/**
 * \file cmd_feature.hpp
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */
/**
    \brief Event trigger

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#ifndef __CMD_FEATURE_TRIGGER_HPP__
#define __CMD_FEATURE_TRIGGER_HPP__

#include "chunk.h"
#include "cmd_gpio_msg.hpp"
#include "payload_gpio.hpp"
#include "payload_keypad.hpp"

namespace engine
{
    namespace hci
    {
        namespace cmd
        {
            namespace feature
            {
                using IDENTIFIER = payload::gpio::IDENTIFIER;
                using FUNCTION = payload::gpio::FUNCTION;

                extern void backlight_request(chunk_t const *const);

                extern void display_request(chunk_t const *const);

                extern void gpio_request(chunk_t const *const);
                extern void gpio_indication(const FUNCTION, const IDENTIFIER, const uint32_t);

                extern void keypad_request(chunk_t const *);
                extern void key_indication(const payload::keypad::content_t &);
            }
        }
    }
}

#endif /* __CMD_FEATURE_TRIGGER_HPP__ */
