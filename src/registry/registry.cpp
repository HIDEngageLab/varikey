/**
 * \file registry.cpp
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

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "checksum.hpp"
#include "chunk.h"
#include "cmd_control.hpp"
#include "cmd_reset_msg.hpp"
#include "macros.hpp"
#include "param_backlight.hpp"
#include "param_features.hpp"
#include "param_keypad.hpp"
#include "param_maintainer.hpp"
#include "param_position.hpp"
#include "param_serial_number.hpp"
#include "param_user.hpp"
#include "parameter.hpp"
#include "random.hpp"
#include "registry.hpp"
#include "varikey.hpp"

/* If FORMAT_PARAMETER_REGISTRY was defined, the registry memory and backup will be recreated */
#define _FORMAT_PARAMETER_REGISTRY

namespace registry
{
    /** \brief Node configuration state */
    typedef enum
    {
        UNDEFINED,
        READY,
    } status_t;

    static status_t status = UNDEFINED;

    static void node_config_init(void);

    extern void initialize(void)
    {

#if defined(FORMAT_PARAMETER_REGISTRY)
        /* format parameter storage */
        parameter::param_format();
        parameter::param_backup_create();
#endif

        /* configure node */
        if (parameter::param_check() == FAILURE)
        {
            parameter::param_format();
            engine::hci::cmd::control::reset_indication(engine::hci::cmd::reset::RESULT::PARAMETER_MISSED);
        }

        node_config_init();
        if (is_ready() == SUCCESS)
        {
            if (parameter::param_backup_check() == FAILURE)
            {
                parameter::param_backup_create();
                engine::hci::cmd::control::reset_indication(engine::hci::cmd::reset::RESULT::BACKUP_CREATED);
            }
        }
        else
        {
            engine::hci::cmd::control::reset_indication(engine::hci::cmd::reset::RESULT::CRITICAL_ERROR);
            if (parameter::param_backup_restore() != SUCCESS)
            {
                parameter::param_backup_create();
                engine::hci::cmd::control::reset_indication(engine::hci::cmd::reset::RESULT::BACKUP_CREATED);
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
        if (parameter::param_backlight_load() == FAILURE)
        {
            return;
        }

        /* load display */
        if (parameter::param_display_load() == FAILURE)
        {
            return;
        }

        /* load features */
        if (parameter::param_features_load() == FAILURE)
        {
            return;
        }

        /* load keypad */
        if (parameter::param_keypad_load() == FAILURE)
        {
            return;
        }

        /* load maintainer */
        if (parameter::param_maintainer_load() == FAILURE)
        {
            return;
        }

        /* load custom mapping table */
        if (parameter::param_mapping_load() == FAILURE)
        {
            return;
        }

        /* load position */
        if (parameter::param_position_load() == FAILURE)
        {
            return;
        }

        /* load serial number */
        if (parameter::param_serial_number_load() == FAILURE)
        {
            return;
        }
        /* *****************************************************
            set rand sequence seed;
            nodes with a special (=equal) serial number makes
            similarly probability based decisions over the time
         ****************************************************** */
        srand(*(uint16_t *)parameter::serial_number::g_register.value);

        /* Attention: do not load testregister  */

        /* all right */
        status = READY;
    }

    /**
        \brief cancel configuration
    */
    extern void shutdown(void)
    {
        assert(status == READY); // state should be initialized
        /* do nothing */
        status = UNDEFINED;
    }

    /**
        \brief Function returns success if node configuration state is valid
    */
    extern result_t is_ready(void)
    {
        if (status == READY)
        {
            return SUCCESS;
        }
        return FAILURE;
    }
}