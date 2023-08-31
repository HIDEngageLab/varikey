/**
 * \file cmd_target.c
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * @copyright Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 *
 */
/**
    \brief Module target

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#include <stddef.h>

#include <hardware/watchdog.h>
#include <pico/stdlib.h>

#include "cmd_target.h"
#include "cmd_target_boot_msg.h"
#include "cmd_target_power_msg.h"
#include "cmd_target_reset_msg.h"
#include "commander.h"
#include "composed_hid.h"
#include "parameter.h"
#include "serial_frame.h"
#include "usart.h"

/**
    \brief Handle power request
*/
extern void cmd_target_power_request(chunk_t const *const _chunk)
{
    cmd_power_msg_t msg;
    cmd_target_power_msg_req(_chunk, &msg);

    cmd_power_cfm_msg_t cfm;
    cfm.function = msg.function;
    cfm.result = CMD_TARGET_POWER_RESULT_SUCCESS;

    /*
        if (msg.function == CMD_TARGET_POWER_FUNCTION_GET)
        {
            if (hil_power_request() != SUCCESS)
            {
                cfm.result = CMD_TARGET_POWER_RESULT_FAILURE;
            }
        }
        else if (msg.function == CMD_TARGET_POWER_FUNCTION_OBSERVER_INTERVAL)
        {
            if (hil_power_set_interval(msg.payload.interval.value) != SUCCESS)
            {
                cfm.result = CMD_TARGET_POWER_RESULT_SHORT_INTERVAL;
            }
        }
        else
        {
            hil_power_voltage_t hil_voltage;
            float voltage_value = 0;
            switch (msg.voltage)
            {
            case CMD_TARGET_POWER_VOLTAGE_1V8:
                hil_voltage = VOLTAGE_1V8;
                voltage_value = 1.8;
                break;
            case CMD_TARGET_POWER_VOLTAGE_3V2:
                hil_voltage = VOLTAGE_3V2;
                voltage_value = 3.2;
                break;
            case CMD_TARGET_POWER_VOLTAGE_5V0:
                hil_voltage = VOLTAGE_5V0;
                voltage_value = 5.0;
                break;
            case CMD_TARGET_POWER_VOLTAGE_SER_VBUS:
                hil_voltage = VOLTAGE_SVB;
                voltage_value = 5.0;
                break;
            default:
                break;
            }

            if (msg.function == CMD_TARGET_POWER_FUNCTION_OBSERVER_SET)
            {
                hil_event_power_t trigger;
                trigger.voltage = hil_voltage;
                trigger.value = voltage_value;
                trigger.limit_low = msg.payload.trigger.limit_low;
                trigger.limit_high = msg.payload.trigger.limit_high;
                if (hil_power_set_trigger(&trigger) != SUCCESS)
                {
                    cfm.result = CMD_TARGET_POWER_RESULT_FAILURE;
                }
            }
            else if (msg.function == CMD_TARGET_POWER_FUNCTION_OBSERVER_RESET)
            {
                if (hil_power_reset_trigger(hil_voltage) != SUCCESS)
                {
                    cfm.result = CMD_TARGET_POWER_RESULT_NO_OBSERVER;
                }
            }
        }
    */

    cmd_target_power_msg_cfm(&cfm);
}

/**
    \brief Handle power request
*/
extern void cmd_target_power_indication(cmd_power_voltage_t const _voltage, float const _power)
{
    cmd_power_ind_msg_t msg;
    msg.voltage = _voltage;
    msg.power = _power;
    cmd_target_power_msg_ind(&msg);
}

/**
    \brief Handle reset request
*/
extern void cmd_target_reset_request(chunk_t const *const _chunk)
{
    cmd_target_reset_msg_t msg;
    cmd_target_reset_msg_req(_chunk, &msg);

    msg.result = CMD_TARGET_RESET_RESULT_FAILURE;
    /*
    switch (msg.function)
    {
    case CMD_TARGET_RESET_FUNCTION_START:
        if (hil_target_reset_start() == SUCCESS)
        {
            msg.result = CMD_TARGET_RESET_RESULT_SUCCESS;
        }
        break;
    case CMD_TARGET_RESET_FUNCTION_STOP:
        if (hil_target_reset_stop() == SUCCESS)
        {
            msg.result = CMD_TARGET_RESET_RESULT_SUCCESS;
        }
        break;
    case CMD_TARGET_RESET_FUNCTION_RESTART:
        if (hil_target_restart() == SUCCESS)
        {
            msg.result = CMD_TARGET_RESET_RESULT_SUCCESS;
        }
        break;
    default:
        msg.result = CMD_TARGET_RESET_RESULT_UNKNOWN_FUNCTION;
        break;
    }
    */

    cmd_target_reset_msg_cfm(&msg);
}

/**
    \brief Handle boot request
*/
extern void cmd_target_boot_request(chunk_t const *const _chunk)
{
    cmd_target_boot_msg_t msg;
    cmd_target_boot_msg_req(_chunk, &msg);

    msg.result = CMD_TARGET_BOOT_RESULT_FAILURE;
    /*
    switch (msg.function)
    {
    case CMD_TARGET_BOOT_FUNCTION_START:
        if (hil_target_boot_start() == SUCCESS)
        {
            msg.result = CMD_TARGET_BOOT_RESULT_SUCCESS;
        }
        break;
    case CMD_TARGET_BOOT_FUNCTION_STOP:
        if (hil_target_boot_stop() == SUCCESS)
        {
            msg.result = CMD_TARGET_BOOT_RESULT_SUCCESS;
        }
        break;
    default:
        msg.result = CMD_TARGET_BOOT_RESULT_UNKNOWN_FUNCTION;
        break;
    }
    */

    cmd_target_boot_msg_cfm(&msg);
}
