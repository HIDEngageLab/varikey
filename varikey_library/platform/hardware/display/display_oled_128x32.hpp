// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: Hardware display oled 128x32 functionality
// SPDX-FileType: SOURCE

#pragma once

#include <cstddef>
#include <cstdint>

#include "component_interface.hpp"

namespace platform::hardware
{
    struct DisplayOLED128x32 : public pulp::ComponentInterface
    {
        virtual void initialize();
        virtual void shutdown();

        void symbol(uint8_t const line_start, uint8_t const line_end,
                    uint8_t const column_start, uint8_t const column_end,
                    uint8_t const *const data, size_t const len);
        void clean();
        void set_invert();
        void set_normal();
    };
}
