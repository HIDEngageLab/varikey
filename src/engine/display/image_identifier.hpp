/**
 * \file image_identifier.hpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#ifndef __IMAGE_IDENTIFIER_HPP__
#define __IMAGE_IDENTIFIER_HPP__

#include <stdint.h>

enum class KEYPAD_ICON : uint8_t
{
    KEYPAD_ICON_FRAME,
    KEYPAD_ICON_VARIKEY_LOGO,
    KEYPAD_ICON_GOSSENMETRAWATT_LOGO,
    KEYPAD_ICON_HEART,
};

#endif // __IMAGE_IDENTIFIER_HPP__
