/**
 * \file cmd_param.c
 * \author Koch, Roman (koch.roman@googlemail.com)
 * \brief
 *
 * @copyright Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 *
 */
/**
    \brief Module configuration

    \internal
    \author Roman Koch, koch.roman@googlemail.com
*/

#include "cmd_param.h"
#include "cmd_param_firmware_msg.h"
#include "cmd_param_hardware_msg.h"
#include "cmd_param_identity_msg.h"
#include "cmd_param_param_msg.h"
#include "composed_hid.h"
#include "param_backlight.h"
#include "param_features.h"
#include "param_key.h"
#include "param_maintainer.h"
#include "param_position.h"
#include "param_serial_number.h"
#include "param_user.h"
#include "registry_interface.h"

/**
    \brief Firmware identifier request

    Sends a part of a firmware identifier in a confirmation message
*/
extern void cmd_param_firmware_request(chunk_t const *_chunk)
{
    cmd_firmware_msg_t msg;
    cmd_param_firmware_msg_req(_chunk, &msg);
    cmd_param_firmware_msg_cfm(&msg);
}

/**
    \brief Hardware identifier request

    Sends a part of a hardware identifier in a confirmation message
*/
extern void cmd_param_hardware_request(chunk_t const *_chunk)
{
    cmd_hardware_msg_t msg;
    cmd_param_hardware_msg_req(_chunk, &msg);
    cmd_param_hardware_msg_cfm(&msg);
}

/**
    \brief Module Identifier Request

    Sends a part of a module identifier in a confirmation message
*/
extern void cmd_param_identifier_request(chunk_t const *_chunk)
{
    cmd_identity_msg_t msg;
    cmd_param_identity_req(_chunk, &msg);
    cmd_param_identity_cfm(&msg);
}

/**
    \brief Parameter request

    Set or get a module configuration parameter
*/
extern void cmd_param_parameter_request(chunk_t const *_chunk)
{
    cmd_param_msg_t msg;
    cmd_param_param_msg_req(_chunk, &msg);
    uint8_t space[24];

    if (msg.identifier == PARAMETER_IDENTIFIER_FEATURES)
    {
        if (msg.function == CMD_PARAM_FUNCTION_GET)
        {
            msg.value.size = sizeof(param_features_t);
            msg.value.space = space;
            msg.result = registry_features_get(&msg.value);
        }
        else if (msg.function == CMD_PARAM_FUNCTION_SET)
        {
            msg.result = registry_features_set(&msg.value);
        }
        else
        {
            msg.result = CMD_PARAM_UNSUPPORTED;
        }
    }
    else if (msg.identifier == PARAMETER_IDENTIFIER_MAINTAINER)
    {
        if (msg.function == CMD_PARAM_FUNCTION_GET)
        {
            msg.value.size = sizeof(param_maintainer_t);
            msg.value.space = space;
            msg.result = registry_maintainer_get(&msg.value);
        }
        else if (msg.function == CMD_PARAM_FUNCTION_SET)
        {
            msg.result = registry_maintainer_set(&msg.value);
        }
        else
        {
            msg.result = CMD_PARAM_UNSUPPORTED;
        }
    }
    else if (msg.identifier == PARAMETER_IDENTIFIER_POSITION)
    {
        if (msg.function == CMD_PARAM_FUNCTION_GET)
        {
            msg.value.size = sizeof(param_position_t);
            msg.value.space = space;
            msg.result = registry_position_get(&msg.value);
        }
        else if (msg.function == CMD_PARAM_FUNCTION_SET)
        {
            msg.result = registry_position_set(&msg.value);
        }
        else
        {
            msg.result = CMD_PARAM_UNSUPPORTED;
        }
    }
    else if (msg.identifier == PARAMETER_IDENTIFIER_SERIAL_NUMBER)
    {
        if (msg.function == CMD_PARAM_FUNCTION_GET)
        {
            msg.value.size = PARAMETER_SERIAL_NUMBER_SIZE;
            msg.value.space = space;
            msg.result = registry_serial_number_get(&msg.value);
        }
        else if (msg.function == CMD_PARAM_FUNCTION_SET)
        {
            msg.result = registry_serial_number_set(&msg.value);
        }
        else
        {
            msg.result = CMD_PARAM_UNSUPPORTED;
        }
    }
    else if (msg.identifier == PARAMETER_IDENTIFIER_BACKLIGHT)
    {
        if (msg.function == CMD_PARAM_FUNCTION_GET)
        {
            msg.value.size = sizeof(param_backlight_t);
            msg.value.space = space;
            msg.result = registry_backlight_get(&msg.value);
        }
        else if (msg.function == CMD_PARAM_FUNCTION_SET)
        {
            msg.result = registry_backlight_set(&msg.value);
        }
        else
        {
            msg.result = CMD_PARAM_UNSUPPORTED;
        }
    }
    else if (msg.identifier == PARAMETER_IDENTIFIER_KEY)
    {
        if (msg.function == CMD_PARAM_FUNCTION_GET)
        {
            msg.value.size = sizeof(param_key_t);
            msg.value.space = space;
            msg.result = registry_key_get(&msg.value);
        }
        else if (msg.function == CMD_PARAM_FUNCTION_SET)
        {
            msg.result = registry_key_set(&msg.value);
        }
        else
        {
            msg.result = CMD_PARAM_UNSUPPORTED;
        }
    }
    else if (msg.identifier == PARAMETER_IDENTIFIER_USER)
    {
        if (msg.function == CMD_PARAM_FUNCTION_GET)
        {
            msg.value.size = PARAMETER_USER_SIZE;
            msg.value.space = space;
            msg.result = registry_testregister_get(&msg.value);
        }
        else if (msg.function == CMD_PARAM_FUNCTION_SET)
        {
            msg.result = registry_testregister_set(&msg.value);
        }
        else
        {
            msg.result = CMD_PARAM_UNSUPPORTED;
        }
    }
    else
    {
        msg.result = CMD_PARAM_UNKNOWN;
    }

    /* send confirmation*/
    cmd_param_param_msg_cfm(&msg);
}