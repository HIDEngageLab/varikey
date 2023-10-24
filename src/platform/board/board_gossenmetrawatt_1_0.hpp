/**
 * \file board_gossenmetrawatt_1_0.hpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#ifndef __BOARD_GOSSENMETRAWATT_1_0_HPP__
#define __BOARD_GOSSENMETRAWATT_1_0_HPP__

#include "board_keypad.hpp"
#include "image_identifier.hpp"

namespace platform
{
    namespace board
    {
        struct Gossenmetrawatt_1_0 : public BoardKeypad
        {
            Gossenmetrawatt_1_0() {}
            virtual ~Gossenmetrawatt_1_0() {}

            static constexpr const char *INTRO = "GMC-I";
            static const KEYPAD_ICON LOGO = KEYPAD_ICON::KEYPAD_ICON_GOSSENMETRAWATT_LOGO;
            static const int8_t POSITION = 30;

            virtual void initialize();
            virtual void shutdown();
        };
    }
}

#endif /* __BOARD_GOSSENMETRAWATT_1_0_HPP__ */
