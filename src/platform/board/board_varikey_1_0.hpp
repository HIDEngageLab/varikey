/**
 * \file board_varikey_1_0.hpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#ifndef __BOARD_VARIKEY_1_0_HPP__
#define __BOARD_VARIKEY_1_0_HPP__

#include "board_keypad.hpp"
#include "display_image.hpp"

namespace platform
{
    namespace board
    {
        struct Varikey_1_0 : public BoardKeypad
        {
            Varikey_1_0() {}
            virtual ~Varikey_1_0() {}

            static constexpr const char *INTRO = "VARIKEY";
            static const engine::display::ICON LOGO = engine::display::ICON::VARIKEY_LOGO;
            static const int8_t POSITION = 14;

            virtual void initialize();
            virtual void shutdown();
        };
    }
}

#endif /* __BOARD_VARIKEY_1_0_HPP__ */
