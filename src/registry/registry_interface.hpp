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

#include "macros.hpp"

typedef struct chunk_struct chunk_t;

/** \brief Parameter request result type */
typedef enum
{
    REGISTRY_SUCCESS = SUCCESS,
    REGISTRY_FAILURE = FAILURE,
    REGISTRY_UNKNOWN = 0x02,
    REGISTRY_UNSUPPORTED = 0x03,
    REGISTRY_ERROR = 0x04,
} registry_result_t;

extern registry_result_t registry_backlight_get(chunk_t *const _chunk);
extern registry_result_t registry_backlight_set(chunk_t const *const _chunk);
extern registry_result_t registry_display_get(chunk_t *const _chunk);
extern registry_result_t registry_display_set(chunk_t const *const _chunk);
extern registry_result_t registry_features_get(chunk_t *const _chunk);
extern registry_result_t registry_features_set(chunk_t const *const _chunk);
extern registry_result_t registry_key_get(chunk_t *const _chunk);
extern registry_result_t registry_key_set(chunk_t const *const _chunk);
extern registry_result_t registry_maintainer_get(chunk_t *const _chunk);
extern registry_result_t registry_maintainer_set(chunk_t const *const _chunk);
extern registry_result_t registry_position_get(chunk_t *const _chunk);
extern registry_result_t registry_position_set(chunk_t const *const _chunk);
extern registry_result_t registry_serial_number_get(chunk_t *const _chunk);
extern registry_result_t registry_serial_number_set(chunk_t const *const _chunk);
extern registry_result_t registry_testregister_get(chunk_t *const_chunk);
extern registry_result_t registry_testregister_set(chunk_t const *const _chunk);

#endif /* __REGISTRY_INTERFACE_HPP__ */
