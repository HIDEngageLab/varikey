/**
 * \file rp2040_ticker.hpp
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

/**
    \brief ticker

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#ifndef __PLATFORM_SOC_TICKER_HPP__
#define __PLATFORM_SOC_TICKER_HPP__

#include <hardware/timer.h>

#include "board_defines.hpp"
#include "component_interface.hpp"

namespace platform
{
    namespace soc
    {
        struct RP2040Ticker : public pulp::ComponentInterface
        {
            virtual ~RP2040Ticker() {}

            /*
                Negative delay so means we will call timer callback, and call it again
                TICKER_DELAY ms later regardless of how long the callback took to execute.
            */
            static const int32_t TICKER_DELAY = -5;

            virtual void initialize(void);
            virtual void shutdown(void);

            void start(platform::board::ticker_handler_t);
            void stop(void);

            void delay_ms(uint32_t);
        };
    }
}

#endif /* __PLATFORM_SOC_TICKER_HPP__ */
