// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: Display management interface
// SPDX-FileType: SOURCE

#pragma once

#include <stdint.h>

#include "display_font.hpp"
#include "display_image.hpp"

namespace engine::display
{
    extern void set_font(const engine::display::FONT);
    extern void set_cursor(const uint8_t line, const uint8_t column);
    extern void print(char const *const text);
    extern void draw(const engine::display::ICON);
    extern void clean();
}
