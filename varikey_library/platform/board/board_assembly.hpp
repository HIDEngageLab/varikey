/**
 * \file board.hpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "component_interface.hpp"
#include "platform_defines.hpp"

#include "backlight_type.hpp"
#include "display_type.hpp"
#include "keymatrix_core_type.hpp"
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

        hardware::Backlight backlight;
        hardware::Display display;
        hardware::Keymatrix keypad;
        hardware::UsbDevice usb;
        hardware::UartDevice uart;
        driver::SoC soc;
    };

    extern Assembly assembly;
}
