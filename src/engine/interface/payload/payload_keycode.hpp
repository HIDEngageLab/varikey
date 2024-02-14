/**
 * \file payload_keycode.hpp
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#ifndef __PAYLOAD_KEYCODE_HPP__
#define __PAYLOAD_KEYCODE_HPP__

#include <cstdint>
#include <cstdlib>

#include "keypad.hpp"
#include "payload_keypad.hpp"

namespace engine
{
    namespace payload
    {
        namespace keycode
        {
            using KEY_ID = engine::keypad::KEY_ID;
            using TABLE = engine::keypad::TABLE;

            enum class STATE : uint8_t
            {
                PRESS = 0x00,
                RELEASE = 0x01,
                CLICK = 0x02,
                PUSH = 0x03,
                UNDEFINED = 0xff,
            };

            enum class CONTROL : uint8_t
            {
                BUTTON = 0x01,
                JOYSTICK_1 = 0x04,
                JOYSTICK_2 = 0x05,
                KEYPAD = 0x06,
                WHEEL_1 = 0x02,
                WHEEL_2 = 0x03,

                UNDEFINED = to_underlying(payload::IDENTIFIER::UNDEFINED),
            };

            struct __attribute__((packed)) content_t
            {
                CONTROL control;
                KEY_ID key_id;
                STATE state;
                TABLE table;

                const size_t size() const { return 5; }

                void deserialize(uint8_t const *const _space)
                {
                    control = static_cast<CONTROL>(_space[0]);
                    state = static_cast<const STATE>(_space[1]);
                    key_id = static_cast<KEY_ID>(_space[2]);
                    table = static_cast<TABLE>(_space[3]);
                    if (!(state == STATE::PRESS ||
                          state == STATE::RELEASE ||
                          state == STATE::CLICK ||
                          state == STATE::PUSH))
                    {
                        state = STATE::UNDEFINED;
                    }
                }

                void serialize(uint8_t *const _space)
                {
                    uint8_t *ptr = _space;
                    *ptr++ = (uint8_t)control;
                    *ptr++ = (uint8_t)engine::keypad::to_int(key_id, table);
                    *ptr++ = (uint8_t)state;
                    *ptr++ = (uint8_t)key_id;
                    *ptr++ = (uint8_t)table;
                }
            };
        }
    }
}

#endif // __PAYLOAD_KEYCODE_HPP__
