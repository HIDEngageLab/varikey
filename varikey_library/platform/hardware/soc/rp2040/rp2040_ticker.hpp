// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: Hardware rp2040 ticker functionality
// SPDX-FileType: SOURCE

#pragma once

#include <hardware/timer.h>

#include "board_defines.hpp"
#include "component_interface.hpp"

namespace platform::soc
{
    struct RP2040Ticker : public pulp::ComponentInterface
    {
        virtual ~RP2040Ticker() {}

        static const int32_t TICKER_DELAY = -5;

        virtual void initialize(void);
        virtual void shutdown(void);

        void start(platform::board::ticker_handler_t);
        void stop(void);

        void delay_ms(uint32_t);
    };
}
