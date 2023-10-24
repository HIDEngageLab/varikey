/**
 * \file keypad_event.hpp
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#ifndef __ENGINE_KEYPAD_EVENT_HPP__
#define __ENGINE_KEYPAD_EVENT_HPP__

#include <stdint.h>

namespace engine
{
    namespace keypad
    {
        namespace event
        {

            enum class IDENTIFIER : uint8_t
            {
                UNDEFINED,
                KEY_1,
                KEY_2,
                KEY_3,
                KEY_4,
                KEY_5,
                KEY_6,
                KEY_7,
                KEY_8,
                KEY_9,
                KEY_10,
                KEY_11,
                KEY_12,
                KEY_13,
            };

            enum class STATE : uint8_t
            {
                UNDEFINED,
                RELEASE,
                PRESS,
            };
        }

        struct event_t
        {
            event::STATE state;
            event::IDENTIFIER identifier;
        };
    }
}

#endif // __ENGINE_KEYPAD_EVENT_HPP__
