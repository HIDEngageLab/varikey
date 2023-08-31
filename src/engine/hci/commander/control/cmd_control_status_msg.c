/**
 * \file cmd_control_status_msg.c
 * \author Koch, Roman (koch.roman@googlemail.com)
 * \brief
 * \version 0.1
 * @date 2023-03-28
 *
 * @copyright Copyright (c) 2023
 *
 */
/**
    \brief status message

    \internal
    \author Roman Koch, koch.roman@googlemail.com
*/

#include <pico/stdlib.h>
#include <stddef.h>
#include <stdint.h>

#include "chunk.h"
#include "cmd_control_status_msg.h"
#include "commander.h"
#include "engine.h"
#include "param_serial_number.h"
#include "serial_frame.h"
#include "storage_queue.h"
#include "types.h"

#define CMD_CONTROL_STATUS_MESSAGE_CFM_SIZE 13
#define CMD_CONTROL_STATUS_MESSAGE_IND_SIZE 7

/**
    \brief Status request message

    Deserialize only.
*/
extern void cmd_control_status_msg_req(chunk_t const *const _chunk, cmd_status_msg_t *const _msg)
{
    /* checks */
    assert(_chunk != NULL && _msg != NULL); // chunk is not null

    /* deserialize */
    _msg->result = CMD_STATUS_RESULT_FAILURE;
    _msg->function = _chunk->space[0];

    const engine_mode_t mode = engine_mode_get();
    switch (mode)
    {
    case ENGINE_MODE_IDLE:
        _msg->mode = CMD_MODE_IDLE;
        break;

    case ENGINE_MODE_ACTIVE:
        _msg->mode = CMD_MODE_ACTIVE;
        break;

    case ENGINE_MODE_PENDING:
        _msg->mode = CMD_MODE_PENDING;
        break;

    default:
        _msg->mode = CMD_MODE_UNDEFINED;
        break;
    }

    /*
    const engine_operation_t operation = engine_operation_get();
    switch (operation)
    {
    case ENGINE_OPERATION_PLAY:
        _msg->operation = CMD_OPERATION_PLAY;
        break;

    case ENGINE_OPERATION_RECORD:
        _msg->operation = CMD_OPERATION_RECORD;
        break;

    default:
        _msg->operation = CMD_OPERATION_UNDEFINED;
        break;
    }
    */

    _msg->value.size = _chunk->size - 1;
    _msg->value.space = &_chunk->space[1];

    /* trigger status/operation event */
    if (_msg->function == CMD_STATUS_FUNCTION_GET)
    {
        _msg->result = CMD_STATUS_RESULT_SUCCESS;
    }
    else
    {
        if (_msg->function == CMD_STATUS_FUNCTION_START)
        {
            if (_msg->operation != CMD_OPERATION_UNDEFINED)
            {
                if (mode == ENGINE_MODE_IDLE)
                {
                    _msg->result = CMD_STATUS_RESULT_SUCCESS;
                }
                else
                {
                    _msg->result = CMD_STATUS_RESULT_WRONG_MODE;
                }
            }
            else
            {
                _msg->result = CMD_STATUS_RESULT_WRONG_OPERATION;
            }
        }
        else if (_msg->function == CMD_STATUS_FUNCTION_STOP)
        {
            if (mode == ENGINE_MODE_ACTIVE || mode == ENGINE_MODE_PENDING)
            {
                _msg->result = CMD_STATUS_RESULT_SUCCESS;
            }
            else
            {
                _msg->result = CMD_STATUS_RESULT_WRONG_MODE;
            }
        }
        else if (_msg->function == CMD_STATUS_FUNCTION_PLAY)
        {
            if (mode == ENGINE_MODE_IDLE)
            {
                _msg->result = CMD_STATUS_RESULT_SUCCESS;
            }
            else
            {
                _msg->result = CMD_STATUS_RESULT_WRONG_MODE;
            }
        }
        else if (_msg->function == CMD_STATUS_FUNCTION_RECORD)
        {
            if (mode == ENGINE_MODE_IDLE)
            {
                _msg->result = CMD_STATUS_RESULT_SUCCESS;
            }
            else
            {
                _msg->result = CMD_STATUS_RESULT_WRONG_MODE;
            }
        }
        else
        {
            _msg->result = CMD_STATUS_RESULT_UNKNOWN_FUNCTION;
        }
    }
}

/**
    \brief Send status confirmation
*/
extern void cmd_control_status_msg_cfm(cmd_status_msg_t *const _msg)
{
    /* checks */
    assert(_msg != NULL); // command control status confirmation message not null

    /* space */
    uint8_t space[CMD_CONTROL_STATUS_MESSAGE_CFM_SIZE] = {0};
    _msg->value.size = CMD_CONTROL_STATUS_MESSAGE_CFM_SIZE;
    _msg->value.space = space;
    uint8_t *ptr = space;

    *ptr++ = (uint8_t)HC_STATUS_CFM;
    *ptr++ = (uint8_t)_msg->result;
    *ptr++ = (uint8_t)_msg->function;
    *ptr++ = (uint8_t)_msg->operation;
    *ptr++ = (uint8_t)_msg->mode;
    serialize_float(storage_get_free_memory_progress(), &ptr);
    serialize_long(g_unique_key, &ptr);

    serial_frame_send(SERIAL_COMMANDER_INTERPRETER_ADDRESS, &_msg->value);
}

/**
    \brief Send status indication
*/
extern void cmd_control_status_msg_ind(cmd_status_msg_t *const _msg)
{
    /* checks */
    assert(_msg != NULL); // command control status indication message not null

    /* handle */
    uint8_t space[CMD_CONTROL_STATUS_MESSAGE_IND_SIZE] = {0};
    _msg->value.size = CMD_CONTROL_STATUS_MESSAGE_IND_SIZE;
    _msg->value.space = space;
    uint8_t *ptr = space;

    *ptr++ = (uint8_t)HC_STATUS_IND;
    *ptr++ = (uint8_t)_msg->operation;
    *ptr++ = (uint8_t)_msg->mode;
    serialize_float(storage_get_free_memory_progress(), &ptr);

    serial_frame_send(SERIAL_COMMANDER_INTERPRETER_ADDRESS, &_msg->value);
}
