/**
 * \file cmd_control.c
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 *
 */
/**
    \brief Module control

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#include <stddef.h>

#include <hardware/watchdog.h>
#include <pico/stdlib.h>

#include "cmd_control.h"
#include "cmd_control_reset_msg.h"
#include "cmd_control_temperature_msg.h"
#include "commander.h"
#include "composed_hid.h"
#include "keyboard.h"
#include "parameter.h"
#include "serial_frame.h"
#include "usart.h"

/**
    \brief Handle reset request
*/
extern void cmd_control_reset_request(chunk_t const *const _chunk)
{
    cmd_reset_msg_t msg;
    cmd_control_reset_msg_req(_chunk, &msg);

    if (msg.function == CMD_RESET_FUNCTION_FORMAT)
    {
        param_format();
    }

    /* no  return */
    composed_hid_device_shutdown();
}

/**
    \brief Handle reset indication
*/
extern void cmd_control_reset_indication(cmd_reset_result_t const _result)
{
    cmd_reset_msg_t msg;
    msg.function = CMD_RESET_FUNCTION_SHUTDOWN;
    msg.result = _result;
    cmd_control_reset_msg_ind(&msg);
}

/**
    \brief Handle status request
*/
extern void cmd_control_status_request(chunk_t const *const _chunk)
{
    cmd_status_msg_t msg;
    cmd_control_status_msg_req(_chunk, &msg);
    cmd_control_status_msg_cfm(&msg);
}

/**
    \brief Send a state switch indication message
*/
extern void cmd_control_status_indication(cmd_mode_t const _mode, cmd_operation_t const _operation)
{
    cmd_status_msg_t msg;
    msg.mode = _mode;
    msg.operation = _operation;
    cmd_control_status_msg_ind(&msg);
}

/**
    \brief Handle temperature request
*/
extern void cmd_control_temperature_request(chunk_t const *const _chunk)
{
    cmd_temperature_msg_t msg;
    cmd_control_temperature_msg_req(_chunk, &msg);
    cmd_control_temperature_msg_cfm(&msg);
}
