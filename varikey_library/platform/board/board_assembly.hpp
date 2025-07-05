// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: Board assembly configuration
// SPDX-FileType: SOURCE

#pragma once

#include "component_interface.hpp"
#include "platform_defines.hpp"

#include "display_type.hpp"
#include "keymatrix_core_type.hpp"
#include "smartled_type.hpp"
#include "soc_type.hpp"
#include "usart.hpp"
#include "usb_device.hpp"

namespace platform::board
{
    struct Assembly : public pulp::ComponentInterface
    {
        virtual ~Assembly() {}

        const defines::IDENTIFIER getIdentifier() const;

        virtual void initialize();
        virtual void shutdown();

        virtual void perform();

        hardware::Frontlight frontlight;
        hardware::Backlight backlight;
        hardware::Display display;
        hardware::Keymatrix keypad;
        hardware::UsbDevice usb;
        hardware::UartDevice uart;
        driver::SoC soc;
    };

    extern Assembly assembly;
}
