/**
 * \file cmd_macro_key_msg.c
 * \author Koch, Roman (koch.roman@googlemail.com)
 * \brief
 *
 * @copyright Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 *
 */
/**
    \brief Key message

    \internal
    \author Roman Koch, koch.roman@googlemail.com
*/

#include <pico/stdlib.h>
#include <stdlib.h>
#include <string.h>

#include "cmd_macro_key_msg.h"
#include "commander.h"
#include "macros.h"
#include "revision.h"
#include "serial_frame.h"

#define KEY_CFM_SIZE 6

/**
    \brief Key request message

    Deserialize only
*/
extern void cmd_macro_key_msg_req(chunk_t const *const _chunk, cmd_macro_key_msg_t *const _msg)
{
    /* checks */
    assert(_chunk != NULL && _msg != NULL); /* key macro request chunk null */

    /* deserialize */
    _msg->result = SUCCESS;

    _msg->value.size = 0;
    _msg->value.space = 0;
}

/**
    \brief Key confirmation message
*/
extern void cmd_macro_key_msg_cfm(cmd_macro_key_msg_t *const _msg)
{
    /* checks */
    assert(_msg != NULL); /* key macro confirmation message null */

    /* handle */
    uint8_t space[KEY_CFM_SIZE] = {0};
    _msg->value.size = KEY_CFM_SIZE;
    _msg->value.space = space;
    uint8_t *ptr = space;

    *ptr++ = (uint8_t)HC_KEY_CFM;
    *ptr++ = (uint8_t)_msg->result;
    *ptr++ = (uint8_t)HIBYTE(HIWORD(_msg->hash));
    *ptr++ = (uint8_t)LOBYTE(HIWORD(_msg->hash));
    *ptr++ = (uint8_t)HIBYTE(LOWORD(_msg->hash));
    *ptr++ = (uint8_t)LOBYTE(LOWORD(_msg->hash));

    serial_frame_send(SERIAL_COMMANDER_INTERPRETER_ADDRESS, &_msg->value);
}
