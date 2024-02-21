/**
 * \file registry_interface.hpp
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

/**
    \brief Node configuration

    Depends on node parameter.
    Commands should be used with HCI.

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#ifndef __REGISTRY_INTERFACE_HPP__
#define __REGISTRY_INTERFACE_HPP__

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
    extern result_t position_get(chunk_t &_chunk);
    extern result_t position_set(const const_chunk_t &_chunk);
    extern result_t serial_number_get(chunk_t &_chunk);
    extern result_t serial_number_set(const const_chunk_t &_chunk);
    extern result_t user_get(chunk_t &_chunk);
    extern result_t user_set(const const_chunk_t &_chunk);
}

#endif /* __REGISTRY_INTERFACE_HPP__ */
