/**
 * \file cmd_macro_clean_msg.c
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 *
 */
/**
    \brief Clean message

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#include <pico/stdlib.h>
#include <stdlib.h>
#include <string.h>

#include "cmd_macro_clean_msg.h"
#include "commander.h"
#include "macros.h"
#include "revision.h"
#include "serial_frame.h"

#define CMD_MACRO_CLEAN_CFM_SIZE 2

/**
    \brief Clean request message

    Deserialize only
*/
extern void cmd_macro_clean_msg_req(chunk_t const *const _chunk, cmd_macro_ctrl_msg_t *const _msg)
{
    /* checks */
    assert(_chunk != NULL && _msg != NULL); /* clean macro request chunk null */

    /* deserialize */
    _msg->result = CMD_MACRO_SUCCESS;

    _msg->value.size = 0;
    _msg->value.space = 0;
}

/**
    \brief Clean confirmation message
*/
extern void cmd_macro_clean_msg_cfm(cmd_macro_ctrl_msg_t *const _msg)
{
    /* checks */
    assert(_msg != NULL); /* clean macro confirmation message null */

    /* handle */
    uint8_t cfm_space[CMD_MACRO_CLEAN_CFM_SIZE] = {0};
    _msg->value.size = CMD_MACRO_CLEAN_CFM_SIZE;
    _msg->value.space = cfm_space;
    uint8_t *ptr = cfm_space;

    *ptr++ = (uint8_t)HC_MACRO_CLEAN_CFM;
    *ptr++ = (uint8_t)_msg->result;

    serial_frame_send(SERIAL_COMMANDER_INTERPRETER_ADDRESS, &_msg->value);
}
