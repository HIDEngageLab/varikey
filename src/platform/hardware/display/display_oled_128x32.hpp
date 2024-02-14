/**
 * \file display_oled_128x32.hpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#ifndef __PLATFORM_DISPLAY_OLED_128X32_HPP__
#define __PLATFORM_DISPLAY_OLED_128X32_HPP__

#include <cstddef>
#include <cstdint>

#include "component_interface.hpp"

namespace platform
{
    namespace hardware
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
}

#endif /* __PLATFORM_DISPLAY_OLED_128X32_HPP__ */
