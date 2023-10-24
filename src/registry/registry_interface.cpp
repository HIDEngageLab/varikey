/**
 * \file registry_interface.cpp
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

/**
    \brief configure node components with persistent parameter

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <pico/stdlib.h>

#include "checksum.hpp"
#include "macros.hpp"
#include "param_backlight.hpp"
#include "param_display.hpp"
#include "param_features.hpp"
#include "param_key.hpp"
#include "param_maintainer.hpp"
#include "param_position.hpp"
#include "param_serial_number.hpp"
#include "param_user.hpp"
#include "parameter.hpp"
#include "random.hpp"
#include "registry.hpp"
#include "registry_interface.hpp"

/**
    \brief Get BACKLIGHT parameters

    BACKLIGHT combine a two float values: reference voltage and rotation wheel voltage
*/
extern registry_result_t registry_backlight_get(chunk_t *const _chunk)
{
    /* checks */
    assert(registry_is_ready() == SUCCESS); /* state should be initialized */

    /* load and serialize adc */
    if (param_backlight_load() == SUCCESS)
    {
        /* checks */
        assert(_chunk->space != NULL && _chunk->size >= sizeof(param_backlight_t)); /* node param adc chunk null */

        param_backlight_serialize(_chunk->space);
        return REGISTRY_SUCCESS;
    }
    return REGISTRY_FAILURE;
}

/**
    \brief Save BACKLIGHT parameter value
*/
extern registry_result_t registry_backlight_set(chunk_t const *const _chunk)
{
    /* checks */
    assert(registry_is_ready() == SUCCESS);                                     /* state should be initialized */
    assert(_chunk->space != NULL && _chunk->size == sizeof(param_backlight_t)); /* chunk is not null */

    /* deserialize and save backlight */
    param_backlight_deserialize(_chunk->space);
    if (param_backlight_store() == SUCCESS)
    {
        return REGISTRY_SUCCESS;
    }
    return REGISTRY_FAILURE;
}

/**
    \brief Get DISPLAY parameters
*/
extern registry_result_t registry_display_get(chunk_t *const _chunk)
{
    /* checks */
    assert(registry_is_ready() == SUCCESS); /* state should be initialized */

    /* load and serialize display */
    if (param_display_load() == SUCCESS)
    {
        /* checks */
        assert(_chunk->space != NULL && _chunk->size >= sizeof(param_display_t)); /* node param display chunk null */

        param_display_serialize(_chunk->space);
        return REGISTRY_SUCCESS;
    }
    return REGISTRY_FAILURE;
}

/**
    \brief Save DISPLAY parameter value
*/
extern registry_result_t registry_display_set(chunk_t const *const _chunk)
{
    /* checks */
    assert(registry_is_ready() == SUCCESS);                                   /* state should be initialized */
    assert(_chunk->space != NULL && _chunk->size == sizeof(param_display_t)); /* chunk is not null */

    /* deserialize and save display */
    param_display_deserialize(_chunk->space);
    if (param_display_store() == SUCCESS)
    {
        return REGISTRY_SUCCESS;
    }
    return REGISTRY_FAILURE;
}

/**
    \brief Get features level parameter value
*/
extern registry_result_t registry_features_get(chunk_t *const _chunk)
{
    /* checks */
    assert(registry_is_ready() == SUCCESS); /* state should be initialized */
    assert(_chunk->space != NULL);          /* chunk is not null */

    /* load and serialize parameter value */
    if (param_features_load() == SUCCESS)
    {
        /* checks */
        assert(_chunk->space != NULL); /* param features chunk null */

        param_features_serialize(_chunk->space);
        return REGISTRY_SUCCESS;
    }
    return REGISTRY_FAILURE;
}

/**
    \brief Save parameter value
*/
extern registry_result_t registry_features_set(chunk_t const *const _chunk)
{
    /* checks */
    assert(registry_is_ready() == SUCCESS); /* state should be initialized */
    assert(_chunk->space != NULL);          /* param features chunk null */

    /* deserialize and save parameter value */
    param_features_deserialize(_chunk->space);

    if (param_features_store() == SUCCESS)
    {
        return REGISTRY_SUCCESS;
    }
    return REGISTRY_FAILURE;
}

/**
    \brief Get KEY parameters
*/
extern registry_result_t registry_key_get(chunk_t *const _chunk)
{
    /* checks */
    assert(registry_is_ready() == SUCCESS); /* state should be initialized */

    /* load and serialize key */
    if (param_key_load() == SUCCESS)
    {
        /* checks */
        assert(_chunk->space != NULL && _chunk->size >= sizeof(param_key_t)); /* node param key chunk null */

        param_key_serialize(_chunk->space);
        return REGISTRY_SUCCESS;
    }
    return REGISTRY_FAILURE;
}

/**
    \brief Save KEY parameter value
*/
extern registry_result_t registry_key_set(chunk_t const *const _chunk)
{
    /* checks */
    assert(registry_is_ready() == SUCCESS);             /* state should be initialized */
    assert(_chunk->space != NULL && _chunk->size == 4); /* chunk is not null */

    /* deserialize and save key */
    param_key_deserialize(_chunk->space);
    if (param_key_store() == SUCCESS)
    {
        return REGISTRY_SUCCESS;
    }
    return REGISTRY_FAILURE;
}

/**
    \brief Get maintainer parameter value
*/
extern registry_result_t registry_maintainer_get(chunk_t *const _chunk)
{
    /* checks */
    assert(registry_is_ready() == SUCCESS); /* state should be initialized */

    /* load and serialize parameter value */
    if (param_maintainer_load() == SUCCESS)
    {
        /* checks */
        assert(_chunk->space != NULL); /* param maintainer chunk null */

        param_maintainer_serialize(_chunk->space);
        return REGISTRY_SUCCESS;
    }
    return REGISTRY_FAILURE;
}

/**
    \brief Save parameter value
*/
extern registry_result_t registry_maintainer_set(chunk_t const *const _chunk)
{
    /* checks */
    assert(registry_is_ready() == SUCCESS); /* state should be initialized */
    assert(_chunk->space != NULL);          /* param maintainer chunk null */

    /* deserialize, set and save parameter value*/
    param_maintainer_deserialize(_chunk->space);
    if (param_maintainer_store() == SUCCESS)
    {
        return REGISTRY_SUCCESS;
    }
    return REGISTRY_FAILURE;
}

/**
    \brief Get node position

    Position combine a two long values: latitude and longitude
*/
extern registry_result_t registry_position_get(chunk_t *const _chunk)
{
    /* checks */
    assert(registry_is_ready() == SUCCESS); /* state should be initialized */

    /* load and serialize position */
    if (param_position_load() == SUCCESS)
    {
        /* checks */
        assert(_chunk->space != NULL && _chunk->size >= sizeof(param_position_t)); /* node param position chunk null */

        param_position_serialize(_chunk->space);
        return REGISTRY_SUCCESS;
    }
    return REGISTRY_FAILURE;
}

/**
    \brief Save parameter value
*/
extern registry_result_t registry_position_set(chunk_t const *const _chunk)
{
    /* checks */
    assert(registry_is_ready() == SUCCESS);             /* state should be initialized */
    assert(_chunk->space != NULL && _chunk->size == 8); /* chunk is not null */

    /* deserialize and save position */
    param_position_deserialize(_chunk->space);
    if (param_position_store() == SUCCESS)
    {
        return REGISTRY_SUCCESS;
    }
    return REGISTRY_FAILURE;
}

/**
    \brief Get serial number value
*/
extern registry_result_t registry_serial_number_get(chunk_t *const _chunk)
{
    /* checks */
    assert(registry_is_ready() == SUCCESS); /* state should be initialized */

    /* load and serialize serial number */
    if (param_serial_number_load() == SUCCESS)
    {
        /* checks */
        assert(_chunk->space != NULL); /* serialize serial number parameter: chunk null */

        param_serial_number_serialize(_chunk->space);
        return REGISTRY_SUCCESS;
    }
    return REGISTRY_FAILURE;
}

/**
    \brief  Save serial number value
    is unsupported
*/
extern registry_result_t registry_serial_number_set(chunk_t const *const _chunk)
{
    /* checks */
    assert(registry_is_ready() == SUCCESS); /* state should be initialized */
    assert(_chunk->space != NULL);          /* serialize serial number parameter: chunk null */

    /* deserialize and save */
    param_serial_number_deserialize(_chunk->space);
    if (param_serial_number_store() == SUCCESS)
    {
        return REGISTRY_SUCCESS;
    }
    return REGISTRY_FAILURE;
}

/**
    \brief Get test register value
*/
extern registry_result_t registry_testregister_get(chunk_t *const _chunk)
{
    /* checks */
    assert(registry_is_ready() == SUCCESS); /* state should be initialized */

    /* serialize parameter value */
    if (param_user_load() == SUCCESS)
    {
        /* checks */
        assert(_chunk->space != NULL); /* param user serialize chunk null */

        param_user_serialize(_chunk->space);
        return REGISTRY_SUCCESS;
    }

    return REGISTRY_FAILURE;
}

/**
    \brief Save parameter value
*/
extern registry_result_t registry_testregister_set(chunk_t const *const _chunk)
{
    /* checks */
    assert(registry_is_ready() == SUCCESS); /* state should be initialized */
    assert(_chunk->space != NULL);          /* param user chunk null */

    /* serialize parameter value */
    param_user_deserialize(_chunk->space);
    if (param_user_store() == SUCCESS)
    {
        return REGISTRY_SUCCESS;
    }
    return REGISTRY_FAILURE;
}
