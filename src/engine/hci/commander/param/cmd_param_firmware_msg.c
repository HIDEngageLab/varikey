/**
 * \file cmd_param_firmware_msg.c
 * \author Koch, Roman (koch.roman@googlemail.com)
 * \brief
 * \version 0.1
 * @date 2023-03-28
 *
 * @copyright Copyright (c) 2023
 *
 */
/**
    \brief Firmware message

    \internal
    \author Roman Koch, koch.roman@googlemail.com
*/

#include <pico/stdlib.h>
#include <stdlib.h>
#include <string.h>

#include "cmd_param_firmware_msg.h"
#include "commander.h"
#include "revision.h"
#include "serial_frame.h"
#include "types.h"

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
