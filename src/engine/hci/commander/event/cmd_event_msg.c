/**
 * \file cmd_event_msg.c
 * \author Koch, Roman (koch.roman@googlemail.com)
 * \brief
 *
 * @copyright Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 *
 */
/**
    \brief Event message

    \internal
    \author Roman Koch, koch.roman@googlemail.com
*/

#include <pico/stdlib.h>
#include <stdlib.h>
#include <string.h>

#include "cmd_event_msg.h"
#include "commander.h"
#include "macros.h"
#include "revision.h"
#include "serial_frame.h"
#include "storage_queue.h"

#define EVENT_CFM_LENGTH 3
#define EVENT_IND_LENGTH 16

/**
    \brief Event request message
*/
extern void cmd_event_msg_req(chunk_t const *const _chunk, cmd_event_msg_t *const _msg)
{
    /* checks */
    assert(_chunk != NULL && _msg != NULL); /* clean macro request chunk null */

    /* deserialize */
    _msg->result = CMD_EVENT_SUCCESS;
    _msg->event.type = _chunk->space[0];
    if (_msg->event.type == HIL_EVENT_KEY)
    {
        _msg->event.common.key.id = _chunk->space[1];
        _msg->event.common.key.level = _chunk->space[2];
    }
    else if (_msg->event.type == HIL_EVENT_WHEEL)
    {
        uint8_t const *ptr = &_chunk->space[1];
        _msg->event.common.wheel.value = deserialize_float(&ptr);
    }
    else
    {
        _msg->result = CMD_EVENT_UNKNOWN_EVENT;
    }

    _msg->value.size = 0;
    _msg->value.space = 0;
}

/**
    \brief Event confirmation message
*/
extern void cmd_event_msg_cfm(cmd_event_msg_t *const _msg)
{
    /* checks */
    assert(_msg != NULL); /* macro event confirmation chunk null */

    /* handle */
    uint8_t space[EVENT_CFM_LENGTH] = {0};
    _msg->value.size = EVENT_CFM_LENGTH;
    _msg->value.space = space;
    uint8_t *ptr = space;

    *ptr++ = (uint8_t)HC_EVENT_TRIGGER_CFM;
    *ptr++ = (uint8_t)_msg->result;
    *ptr++ = (uint8_t)_msg->event.type;

    serial_frame_send(SERIAL_COMMANDER_INTERPRETER_ADDRESS, &_msg->value);
}

/**
    \brief Event indication message
*/
extern void cmd_event_msg_ind(cmd_event_msg_t *const _msg)
{
    /* checks */
    assert(_msg != NULL); /* macro event indication chunk null */

    /* handle */
    uint8_t space[EVENT_IND_LENGTH] = {0};
    _msg->value.space = space;
    uint8_t *ptr = space;

    *ptr++ = (uint8_t)HC_EVENT_TRIGGER_IND;
    *ptr++ = (uint8_t)_msg->event.type;
    _msg->value.size = 2;
    switch (_msg->event.type)
    {
    case HIL_EVENT_KEY:
        *ptr++ = (uint8_t)_msg->event.common.key.id;
        *ptr++ = (uint8_t)_msg->event.common.key.level;
        _msg->value.size += 2;
        break;
    case HIL_EVENT_WHEEL:
        serialize_float(_msg->event.common.wheel.value, &ptr);
        _msg->value.size += 4;
        break;
    case HIL_EVENT_DELAY:
        serialize_float(_msg->event.common.delay.value, &ptr);
        _msg->value.size += 4;
        break;
    case HIL_EVENT_DEBUG:
        *ptr++ = (uint8_t)_msg->event.common.debug.id;
        *ptr++ = (uint8_t)_msg->event.common.debug.level;
        _msg->value.size += 2;
        break;
    case HIL_EVENT_LED:
        *ptr++ = (uint8_t)_msg->event.common.led.id;
        *ptr++ = (uint8_t)_msg->event.common.led.level;
        _msg->value.size += 2;
        break;
    case HIL_EVENT_POWER:
        *ptr++ = (uint8_t)_msg->event.common.power.voltage;
        *ptr++ = (uint8_t)_msg->event.common.power.level;
        serialize_float(_msg->event.common.power.value, &ptr);
        serialize_float(_msg->event.common.power.limit_low, &ptr);
        serialize_float(_msg->event.common.power.limit_high, &ptr);
        _msg->value.size += (1 + 1 + 4 + 4 + 4);
        break;
    default:
        _msg->event.type = HIL_EVENT_UNDEFINED;
        break;
    }

    serial_frame_send(SERIAL_COMMANDER_INTERPRETER_ADDRESS, &_msg->value);
}
