// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: Hardware rp2040 watchdog functionality
// SPDX-FileType: SOURCE

#pragma once

#include "component_interface.hpp"

namespace platform::soc
{
    struct RP2040Watchdog : public pulp::ComponentInterface
    {
        virtual ~RP2040Watchdog() {}

        virtual void initialize() {}
        virtual void shutdown() {}

        void start();
        void update();
        void reboot();
    };
}
