/**
 * \file font_identifier.hpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#ifndef __ENGINE_FONT_IDENTIFIER_HPP__
#define __ENGINE_FONT_IDENTIFIER_HPP__

#include <stdint.h>

enum class FONT_SIZE : uint8_t
{
    FONT_SMALL,
    FONT_NORMAL,
    FONT_BIG,
    FONT_HUGE,
    FONT_SYMBOL,
};

#endif // __ENGINE_FONT_IDENTIFIER_HPP__
