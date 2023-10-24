/**
 * \file cmd_param_firmware_msg.cpp
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */
/**
    \brief Firmware message

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#include <pico/stdlib.h>
#include <stdlib.h>
#include <string.h>

#include "cmd_param_firmware_msg.hpp"
#include "commander.hpp"
#include "macros.hpp"
#include "revision.h"
#include "serial_frame.hpp"

#define PARAM_FIRMWARE_MESSAGE_CFM_SIZE 8

/**
    \brief Firmware request message

    Deserialize only
*/
extern void cmd_param_firmware_msg_req(chunk_t const *const _chunk, cmd_firmware_msg_t *const _msg)
{
    /* checks */
    assert(_chunk != NULL && _msg != NULL); /* firmware param request chunk null */

    /* deserialize */
    _msg->result = CMD_FIRMWARE_SUCCESS;
    _msg->value.size = 0;
    _msg->value.space = 0;
}

/**
    \brief Firmware confirmation message
*/
extern void cmd_param_firmware_msg_cfm(cmd_firmware_msg_t *const _msg)
{
    /* checks */
    assert(_msg != NULL); /* firmware param confirmation message null */

    /* handle */
    uint8_t space[PARAM_FIRMWARE_MESSAGE_CFM_SIZE] = {0};
    _msg->value.size = PARAM_FIRMWARE_MESSAGE_CFM_SIZE;
    _msg->value.space = space;
    uint8_t *ptr = space;

    *ptr++ = (uint8_t)HC_FIRMWARE_CFM;
    *ptr++ = (uint8_t)_msg->result;
    serialize_word(FIRMWARE_IDENTIFIER, &ptr);
    serialize_word(FIRMWARE_REVISION, &ptr);
    serialize_word(FIRMWARE_BUILD, &ptr);

    serial_frame_send(SERIAL_COMMANDER_INTERPRETER_ADDRESS, &_msg->value);
}
