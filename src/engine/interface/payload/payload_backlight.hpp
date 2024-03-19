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
            struct content_t
            {
                using PROGRAM = engine::backlight::MODE;
                using Color = engine::backlight::Color;

                PROGRAM program;
                Color left;
                Color right;

                const size_t size() const;
                void deserialize(uint8_t const *const);
                void serialize(uint8_t **) const;
            };
        }
    }
}

#endif // __PAYLOAD_BACKLIGHT_HPP__
