// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: Hardware backlight ws2812 functionality
// SPDX-FileType: SOURCE

#pragma once

#include "backlight_color.hpp"
#include "component_interface.hpp"

namespace platform::hardware::backlight
{
    enum INDEX
    {
        FIRST,
        SECOND,
        THIRD
    };

    struct BacklightWs2812 : public pulp::ComponentInterface
    {
        virtual void initialize();
        virtual void shutdown();

        void set_backlight(const engine::backlight::Color &,
                           const engine::backlight::Color &);
    };
}
