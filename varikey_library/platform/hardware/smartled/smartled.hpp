// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: Hardware smartled ws2812 functionality
// SPDX-FileType: SOURCE

#pragma once

#include "component_interface.hpp"
#include "smartled_color.hpp"

namespace platform::hardware::smartled
{
    struct FrontChannel : public pulp::ComponentInterface
    {
        virtual void initialize();
        virtual void shutdown();

        void put_pixel(uint8_t r, uint8_t g, uint8_t b);

        template <typename Mapper>
        void set_led_sequence(const Color (&colors)[Mapper::mapping.size()])
        {
            // extends template with:  std::size_t N
            // static_assert(N == Mapper::mapping.size(), "Color array size does not match LED mapper size.");

            for (std::size_t i = 0; i < Mapper::mapping.size(); ++i)
            {
                const std::size_t index = static_cast<std::size_t>(Mapper::mapping[i]);
                const auto &color = colors[index];
                put_pixel(color.rgb.r, color.rgb.g, color.rgb.b);
            }
        }
    };

    struct BackChannel : public pulp::ComponentInterface
    {
        virtual void initialize();
        virtual void shutdown();

        void put_pixel(uint8_t r, uint8_t g, uint8_t b);

        template <typename Mapper>
        void set_led_sequence(const Color (&colors)[Mapper::mapping.size()])
        {
            // extends template with:  std::size_t N
            // static_assert(N == Mapper::mapping.size(), "Color array size does not match LED mapper size.");

            for (std::size_t i = 0; i < Mapper::mapping.size(); ++i)
            {
                const std::size_t index = static_cast<std::size_t>(Mapper::mapping[i]);
                const auto &color = colors[index];
                put_pixel(color.rgb.r, color.rgb.g, color.rgb.b);
            }
        }
    };
}
