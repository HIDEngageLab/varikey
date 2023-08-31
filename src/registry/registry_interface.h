/**
 * \file registry_interface.h
 * \author Koch, Roman (koch.roman@googlemail.com)
 * \brief
 * \version 0.1
 * @date 2023-03-28
 *
 * @copyright Copyright (c) 2023
 *
 */
/**
    \brief Node configuration

    Depends on node parameter.
    Commands should be used with HCI.

    \internal
    \author Roman Koch, koch.roman@googlemail.com
*/

#ifndef __REGISTRY_INTERFACE_H__
#define __REGISTRY_INTERFACE_H__

#include "types.h"

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

#endif /* __REGISTRY_INTERFACE_H__ */
