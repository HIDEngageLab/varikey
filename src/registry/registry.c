/**
 * \file registry.c
 * \author Koch, Roman (koch.roman@googlemail.com)
 * \brief
 *
 * @copyright Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 *
 */
/**
    \brief configure node components with persistent parameter

    \internal
    \author Roman Koch, koch.roman@googlemail.com
*/

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <pico/stdlib.h>

#include "checksum.h"
#include "chunk.h"
#include "composed_hid.h"
#include "macros.h"
#include "param_backlight.h"
#include "param_features.h"
#include "param_key.h"
#include "param_maintainer.h"
#include "param_position.h"
#include "param_serial_number.h"
#include "param_user.h"
#include "parameter.h"
#include "random.h"
#include "registry.h"
#include "temperature.h"

/** \brief Node configuration state */
typedef enum
{
    UNDEFINED,
    READY,
} status_t;

static status_t status = UNDEFINED;

static void node_config_init(void);

extern void registry_init(void)
{
    /* configure node */
    if (param_check() == FAILURE)
    {
        param_format();
        // cmd_control_reset_indication(CMD_RESET_RESULT_PARAMETER_MISSED);
    }

    node_config_init();
    if (registry_is_ready() == SUCCESS)
    {
        if (param_backup_check() == FAILURE)
        {
            param_backup_create();
            // cmd_control_reset_indication(CMD_RESET_RESULT_PARAMETER_BACKUP_CREATED);
        }
    }
    else
    {
        // cmd_control_reset_indication(CMD_RESET_RESULT_ERROR);
        if (param_backup_restore() != SUCCESS)
        {
            param_backup_create();
            // cmd_control_reset_indication(CMD_RESET_RESULT_PARAMETER_BACKUP_CREATED);
        }
    }

    // debug_out_mem();
}

/**
    \brief Initialize parameter storage and load parameter from persistent memory

    This function load stored parameter values from persistent memory.
    Parameter-Functions sets the proper values.
*/
static void node_config_init(void)
{
    assert(status == UNDEFINED); // state should be undefined

    /* load backlight */
    if (param_backlight_load() == FAILURE)
    {
        return;
    }

    /* load display */
    if (param_display_load() == FAILURE)
    {
        return;
    }

    /* load features */
    if (param_features_load() == FAILURE)
    {
        return;
    }

    /* load button */
    if (param_key_load() == FAILURE)
    {
        return;
    }

    /* load maintainer */
    if (param_maintainer_load() == FAILURE)
    {
        return;
    }

    /* load position */
    if (param_position_load() == FAILURE)
    {
        return;
    }

    /* load serial number */
    if (param_serial_number_load() == FAILURE)
    {
        return;
    }
    /* *****************************************************
        set rand sequence seed;
        nodes with a special (=equal) serial number makes
        similarly probability based decisions over the time
     ****************************************************** */
    srand(*(uint16_t *)g_serial_number.value);

    /* Attention: do not load testregister  */

    /* all right */
    status = READY;
}

/**
    \brief cancel configuration
*/
extern void registry_shutdown(void)
{
    assert(status == READY); // state should be initialized
    /* do nothing */
    status = UNDEFINED;
}

/**
    \brief Function returns success if node configuration state is valid
*/
extern result_t registry_is_ready(void)
{
    if (status == READY)
    {
        return SUCCESS;
    }
    return FAILURE;
}
