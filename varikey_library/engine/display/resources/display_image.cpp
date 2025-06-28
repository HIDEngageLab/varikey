/**
 * \file display_image.cpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#include "display_image.hpp"
#include "image_add_circle_16.h"
#include "image_add_circle_24.h"
#include "image_add_circle_32.h"
#include "image_add_circle_8.h"
#include "image_add_square_16.h"
#include "image_add_square_24.h"
#include "image_add_square_32.h"
#include "image_add_square_8.h"
#include "image_frame.h"
#include "image_gmc.h"
#include "image_heart.h"
#include "image_varikey.h"

namespace engine
{
    namespace display
    {
        namespace image
        {

            const Type images[SIZE] = {
                {.width = 128, .height = 32, .data = IMAGE_FRAME},
                {.width = 32, .height = 32, .data = IMAGE_VARIKEY},
                {.width = 32, .height = 32, .data = IMAGE_GMC},
                {.width = 32, .height = 32, .data = IMAGE_HEART},
                {.width = 8, .height = 8, .data = IMAGE_ADD_CIRCLE_8},
                {.width = 16, .height = 16, .data = IMAGE_ADD_CIRCLE_16},
                {.width = 24, .height = 24, .data = IMAGE_ADD_CIRCLE_24},
                {.width = 32, .height = 32, .data = IMAGE_ADD_CIRCLE_32},
                {.width = 8, .height = 8, .data = IMAGE_ADD_SQUARE_8},
                {.width = 16, .height = 16, .data = IMAGE_ADD_SQUARE_16},
                {.width = 24, .height = 24, .data = IMAGE_ADD_SQUARE_24},
                {.width = 32, .height = 32, .data = IMAGE_ADD_SQUARE_32},
            };

            static const uint16_t get_image_index(const engine::display::ICON _icon)
            {
                uint16_t image_index = 0;
                switch (_icon)
                {
                case engine::display::ICON::FRAME:
                    image_index = 0;
                    break;
                case engine::display::ICON::VARIKEY_LOGO:
                    image_index = 1;
                    break;
                case engine::display::ICON::GOSSENMETRAWATT_LOGO:
                    image_index = 2;
                    break;
                case engine::display::ICON::HEART:
                    image_index = 3;
                    break;
                case engine::display::ICON::ADD_CIRCLE_8:
                    image_index = 4;
                    break;
                case engine::display::ICON::ADD_CIRCLE_16:
                    image_index = 5;
                    break;
                case engine::display::ICON::ADD_CIRCLE_24:
                    image_index = 6;
                    break;
                case engine::display::ICON::ADD_CIRCLE_32:
                    image_index = 7;
                    break;
                case engine::display::ICON::ADD_SQUARE_8:
                    image_index = 8;
                    break;
                case engine::display::ICON::ADD_SQUARE_16:
                    image_index = 9;
                    break;
                case engine::display::ICON::ADD_SQUARE_24:
                    image_index = 10;
                    break;
                case engine::display::ICON::ADD_SQUARE_32:
                    image_index = 11;
                    break;
                default:
                    break;
                }

                return image_index;
            }

            extern const bool is_defined(const engine::display::ICON _icon)
            {
                if (_icon == engine::display::ICON::FRAME ||
                    _icon == engine::display::ICON::VARIKEY_LOGO ||
                    _icon == engine::display::ICON::GOSSENMETRAWATT_LOGO ||
                    _icon == engine::display::ICON::HEART ||
                    _icon == engine::display::ICON::ADD_CIRCLE_8 ||
                    _icon == engine::display::ICON::ADD_CIRCLE_16 ||
                    _icon == engine::display::ICON::ADD_CIRCLE_24 ||
                    _icon == engine::display::ICON::ADD_CIRCLE_32 ||
                    _icon == engine::display::ICON::ADD_SQUARE_8 ||
                    _icon == engine::display::ICON::ADD_SQUARE_16 ||
                    _icon == engine::display::ICON::ADD_SQUARE_24 ||
                    _icon == engine::display::ICON::ADD_SQUARE_32)
                {
                    return true;
                }
                return false;
            }

            extern const image::Type *get_image(const engine::display::ICON _icon)
            {
                return &image::images[image::get_image_index(_icon)];
            }

        }
    }
}