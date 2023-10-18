/**
 * \file board_varikey_1_0.hpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#ifndef __BOARD_VARIKEY_1_0_HPP__
#define __BOARD_VARIKEY_1_0_HPP__

#include "board_interface.hpp"
#include "button.hpp"
#include "display.hpp"
#include "temperature.hpp"
#include "timer.hpp"

namespace platform
{
    namespace board
    {
        class Varikey_1_0 : public Interface
        {
        public:
            Varikey_1_0();
            virtual ~Varikey_1_0();

            const virtual int getIdentifier() const;

            hardware::Display display;
            hardware::Button button;

            driver::Timer timer;
            driver::Temperature temperature;
        };
    }
}

#endif /* __BOARD_VARIKEY_1_0_HPP__ */
