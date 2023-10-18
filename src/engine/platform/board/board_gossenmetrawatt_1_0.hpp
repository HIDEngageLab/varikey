/**
 * \file board_gossenmetrawatt_1_0.hpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#ifndef __BOARD_GOSSENMETRAWATT_1_0_HPP__
#define __BOARD_GOSSENMETRAWATT_1_0_HPP__

#include "board_interface.hpp"
#include "button.hpp"
#include "display.hpp"
#include "temperature.hpp"
#include "timer.hpp"

namespace platform
{
    namespace board
    {
        class Gossenmetrawatt_1_0 : public Interface
        {
        public:
            Gossenmetrawatt_1_0();
            virtual ~Gossenmetrawatt_1_0();

            const virtual int getIdentifier() const;

            hardware::Display display;
            hardware::Button button;

            driver::Timer timer;
            driver::Temperature temperature;
        };

    }
}

#endif /* __BOARD_GOSSENMETRAWATT_1_0_HPP__ */
