/**
 * \file storage_interface.c
 * \author Koch, Roman (koch.roman@googlemail.com)
 * \brief
 *
 * @copyright Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 *
 */
/**
    \brief Storage

    \internal
    \author Roman Koch, koch.roman@googlemail.com
*/

#include <pico/stdlib.h>
#include <stddef.h>
#include <string.h>

#include "revision.h"
#include "storage_interface.h"
#include "storage_queue.h"

/**
    \brief Storage state type
*/
typedef enum
{
    STORAGE_IDLE,
    STORAGE_STORE,
    STORAGE_LOAD,
} storage_state_t;

static storage_state_t state = STORAGE_IDLE;

static uint16_t max_index = 0;

/**
    \brief Start store data item

    \return "Error" code
*/
extern storage_result_t storage_store_start(storage_transport_t *const _data)
{
    /* check state and select */
    if (state == STORAGE_IDLE)
    {
        if (storage_select_all() == SUCCESS)
        {
            state = STORAGE_STORE;
        }
        else
        {
            return STORAGE_EMPTY;
        }
    }

    return storage_store_continue(_data);
}

/**
    \brief Continue store macro data

    \return "Error" code
*/
extern storage_result_t storage_store_continue(storage_transport_t *const _data)
{
    /* take next */
    if (state == STORAGE_STORE)
    {
        /* checks */
        assert(_data != NULL); // data chunk not null

        result_t result = storage_get_selected(_data);
        if (result == SUCCESS)
        {
            return STORAGE_SUCCESS;
        }
        else
        {
            state = STORAGE_IDLE;
            return STORAGE_NOT_FOUND;
        }
    }

    return STORAGE_BUSY;
}

/**
    \brief Start load storage data

    \return Data item hash code or zero
*/
extern storage_result_t storage_load_start(storage_transport_t *const _data)
{
    /* check state and select */
    if (state == STORAGE_IDLE)
    {
        state = STORAGE_LOAD;
        max_index = _data->max;
    }

    return STORAGE_SUCCESS;
}

/**
    \brief Continue load storage data

    \return "Error" code
*/
extern storage_result_t storage_load_continue(storage_transport_t *const _data)
{
    /* upload next */
    if (state == STORAGE_LOAD)
    {
        /* checks */
        assert(_data != NULL); // data chunk not null

        if (storage_enqueue(_data) == SUCCESS)
        {
            if (_data->index == max_index)
            {
                state = STORAGE_IDLE;
                max_index = 0;
            }

            return STORAGE_SUCCESS;
        }
        else
        {
            state = STORAGE_IDLE;
            max_index = 0;

            return STORAGE_FAILURE;
        }
    }

    return STORAGE_BUSY;
}

/**
    \brief Stop list read session
*/
extern storage_result_t storage_stop(void)
{
    if (state != STORAGE_IDLE)
    {
        state = STORAGE_IDLE;
        max_index = 0;

        return STORAGE_SUCCESS;
    }

    return STORAGE_FAILURE;
}

/**
    \brief Format the data base

    All data going lost.
*/
extern storage_result_t storage_erase(void)
{
    /* check state and select */
    if (state == STORAGE_IDLE)
    {
        storage_init();

        return STORAGE_SUCCESS;
    }

    return STORAGE_BUSY;
}
