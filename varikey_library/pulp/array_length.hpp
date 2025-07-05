// SPDX-FileCopyrightText: 2024 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: Array length utility macros
// SPDX-FileType: SOURCE

#pragma once

#include <cstdint>

template <std::size_t N>
constexpr std::size_t string_length(const char (&)[N])
{
    return N - 1; // Ignoriere das Nullterminierungszeichen
}
