/**
 * \file array_length.hpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <cstdint>

template <std::size_t N>
constexpr std::size_t string_length(const char (&)[N])
{
    return N - 1; // Ignoriere das Nullterminierungszeichen
}
