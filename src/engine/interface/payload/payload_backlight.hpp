/**
 * \file payload_backlight.hpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#ifndef __PAYLOAD_BACKLIGHT_HPP__
#define __PAYLOAD_BACKLIGHT_HPP__

#include <cstdint>
#include <cstdlib>

#include "backlight_color.hpp"
#include "backlight_mode.hpp"
#include "payload_identifier.hpp"

namespace engine
{
    namespace payload
    {
        namespace backlight
        {
            struct __attribute__((packed)) content_t
            {
                using PROGRAM = engine::backlight::MODE;
                using color_t = engine::backlight::color_t;

                PROGRAM program;
                color_t color_left;
                color_t color_right;

                const size_t size() const;
                void deserialize(uint8_t const *const);
                void serialize(uint8_t **) const;
            };
        }
    }
}

#endif // __PAYLOAD_BACKLIGHT_HPP__
