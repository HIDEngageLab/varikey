// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: Registry interface definition
// SPDX-FileType: SOURCE

#pragma once

#include "chunk.h"
#include "macros.hpp"
#include "parameter_identifier.hpp"

namespace registry
{
    extern result_t backlight_get(chunk_t &_chunk);
    extern result_t backlight_set(const const_chunk_t &_chunk);
    extern result_t display_get(chunk_t &_chunk);
    extern result_t display_set(const const_chunk_t &_chunk);
    extern result_t features_get(chunk_t &_chunk);
    extern result_t features_set(const const_chunk_t &_chunk);
    extern result_t keypad_get(chunk_t &_chunk);
    extern result_t keypad_set(const const_chunk_t &_chunk);
    extern result_t maintainer_get(chunk_t &_chunk);
    extern result_t maintainer_set(const const_chunk_t &_chunk);
    extern result_t mapping_get(chunk_t &_chunk);
    extern result_t mapping_set(const const_chunk_t &_chunk);
    extern result_t mapping_get(const uint8_t, chunk_t &_chunk);
    extern result_t mapping_set(const uint8_t, const const_chunk_t &_chunk);
    extern result_t position_get(chunk_t &_chunk);
    extern result_t position_set(const const_chunk_t &_chunk);
    extern result_t serial_number_get(chunk_t &_chunk);
    extern result_t serial_number_set(const const_chunk_t &_chunk);
    extern result_t user_get(chunk_t &_chunk);
    extern result_t user_set(const const_chunk_t &_chunk);
}
