// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: Hardware usb device functionality
// SPDX-FileType: SOURCE

#pragma once

#include "component_interface.hpp"

namespace platform::hardware
{
    struct UsbDevice : public pulp::ComponentInterface
    {
        virtual void initialize();
        virtual void shutdown();

        void perform();
    };
}
