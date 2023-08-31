/**
 * \file cmd_target_power_msg.h
 * \author Koch, Roman (koch.roman@googlemail.com)
 * \brief
 *
 * @copyright Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 *
 */
/**
    \brief target power message

    \internal
    \author Roman Koch, koch.roman@googlemail.com
*/

#ifndef __CMD_TARGET_POWER_MSG_H__
#define __CMD_TARGET_POWER_MSG_H__

#include "chunk.h"
#include "macros.h"

typedef struct chunk_struct chunk_t;

/** \brief Power message function code */
typedef enum
{
    CMD_TARGET_POWER_FUNCTION_GET = 0x00,
    CMD_TARGET_POWER_FUNCTION_OBSERVER_SET = 0x01,
    CMD_TARGET_POWER_FUNCTION_OBSERVER_RESET = 0x02,
    CMD_TARGET_POWER_FUNCTION_OBSERVER_INTERVAL = 0x07,
    CMD_TARGET_POWER_FUNCTION_UNDEFINED = 0xff,
} cmd_power_function_t;

/** \brief Power message result code */
typedef enum
{
    CMD_TARGET_POWER_RESULT_SUCCESS = SUCCESS,
    CMD_TARGET_POWER_RESULT_FAILURE = FAILURE,
    CMD_TARGET_POWER_RESULT_UNKNOWN_FUNCTION = 0x02,
    CMD_TARGET_POWER_RESULT_UNDEFINED_VOLTAGE = 0x03,
    CMD_TARGET_POWER_RESULT_SHORT_INTERVAL = 0x04,
    CMD_TARGET_POWER_RESULT_NO_OBSERVER = 0x05,
    CMD_TARGET_POWER_RESULT_ALLREADY_DONE = 0x0f,
} cmd_power_result_t;

/** \brief Power message voltage code */
typedef enum
{
    CMD_TARGET_POWER_VOLTAGE_1V8 = 0x00,
    CMD_TARGET_POWER_VOLTAGE_3V2 = 0x01,
    CMD_TARGET_POWER_VOLTAGE_5V0 = 0x02,
    CMD_TARGET_POWER_VOLTAGE_SER_VBUS = 0x03,
    CMD_TARGET_POWER_VOLTAGE_UNDEFINED = 0xff,
} cmd_power_voltage_t;

/** \brief Power confirmation message */
typedef struct cmd_power_cfm_msg_struct
{
    cmd_power_result_t result;
    cmd_power_function_t function;
    chunk_t value;
} cmd_power_cfm_msg_t;

/** \brief Power indication message */
typedef struct cmd_power_ind_msg_struct
{
    cmd_power_voltage_t voltage;
    float power;
    chunk_t value;
} cmd_power_ind_msg_t;

typedef struct cmd_power_observer_interval_struct
{
    uint32_t value;
} cmd_power_observer_interval_t;

typedef struct cmd_power_observer_trigger_struct
{
    float limit_low;
    float limit_high;
} cmd_power_observer_trigger_t;

/** \brief Power message */
typedef struct cmd_power_msg_struct
{
    cmd_power_function_t function;
    cmd_power_voltage_t voltage;
    union
    {
        cmd_power_observer_interval_t interval;
        cmd_power_observer_trigger_t trigger;
    } payload;
    chunk_t value;
} cmd_power_msg_t;

extern void cmd_target_power_msg_req(chunk_t const *const _chunk, cmd_power_msg_t *const _msg);
extern void cmd_target_power_msg_cfm(cmd_power_cfm_msg_t *const _msg);
extern void cmd_target_power_msg_ind(cmd_power_ind_msg_t *const _msg);

#endif /* __CMD_TARGET_POWER_MSG_H__ */
