/**
 * \file commander.c
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * @copyright Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 *
 */
/**
    \brief Command interpreter on the host interface

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#include <assert.h>
#include <stddef.h>

#include "cmd_control.h"
#include "cmd_event_trigger.h"
#include "cmd_macro.h"
#include "cmd_macro_load.h"
#include "cmd_macro_store.h"
#include "cmd_param.h"
#include "cmd_target.h"
#include "commander.h"
#include "macros.h"

/**
    \brief Interpreter for commander commandos

    This function needs to be registered with register_handler() on the serial frame modul.
*/
extern cmd_hci_status_result_t hci_commander_interpreter(chunk_t const *const _chunk)
{
    /* checks */
    assert(_chunk != NULL); // serial commander interpreter chunk null

    cmd_hci_status_result_t result = SUCCESS;

    /* command switch */
    host_command_t command = _chunk->space[0];
    chunk_t sdu = {&_chunk->space[1], _chunk->size - 1};

    switch (command)
    {
    /* module restart */
    case HC_RESET_REQ:
        // 7E 20 01 04 40 84 7E
        cmd_control_reset_request(&sdu);
        break;

    /* check hardware version */
    case HC_STATUS_REQ:
        // 7E 20 01 08 81 08 7E
        cmd_control_status_request(&sdu);
        break;

    /* check firmware version */
    case HC_FIRMWARE_REQ:
        // 7E 20 01 0c C1 8C 7E
        cmd_param_firmware_request(&sdu);
        break;

    /* check hardware version */
    case HC_HARDWARE_REQ:
        // 7E 20 01 10 12 31 7E
        cmd_param_hardware_request(&sdu);
        break;

    /* check module identifier */
    case HC_IDENTITY_REQ:
        // 7E 20 01 14 52 b5 7E
        // 7E 20 01 14 00 CF B7 7E
        // 7E 20 01 14 01 DF 69 7E
        cmd_param_identifier_request(&sdu);
        break;

    /* handle parameter request */
    case HC_PARAM_REQ:
        cmd_param_parameter_request(&sdu);
        break;

    /* key storage service */
    case HC_KEY_REQ:
        /* key "bla" */
        // 7E 20 01 1C 62 6C 61 93 5E 7E
        cmd_macro_key_request(&sdu);
        break;

    /* macro store request handling */
    case HC_MACRO_STORE_REQ:
        cmd_macro_store_request(&sdu);
        break;

    /* macro store response handling */
    case HC_MACRO_STORE_RES:
        cmd_macro_store_response(&sdu);
        break;

    /* macro load request handling */
    case HC_MACRO_LOAD_REQ:
        cmd_macro_load_request(&sdu);
        break;

    /* macro load response handling */
    case HC_MACRO_LOAD_RES:
        cmd_macro_load_response(&sdu);
        break;

    /* macro clean request handling */
    case HC_MACRO_CLEAN_REQ:
        // 7E 20 01 28 A5 6A 7E
        cmd_macro_clean_request(&sdu);
        break;

    /* key trigger request handling */
    case HC_EVENT_TRIGGER_REQ:
        cmd_event_trigger_request(&sdu);
        break;

    /* check temperature value */
    case HC_TEMPERATURE_REQ:
        // 7E 20 01 34 76 D7 7E
        cmd_control_temperature_request(&sdu);
        break;

    /* target power values */
    case HC_TARGET_POWER_REQ:
        // 7E 20 01 38 B7 5B 7E
        cmd_target_power_request(&sdu);
        break;

    /* target reset */
    case HC_TARGET_RESET_REQ:
        // start: 7E 20 01 40 00 0D CC 7E
        // stop: 7E 20 01 40 01 1D ED 7E
        // restart: 7E 20 01 40 02 2D 8E 7E
        cmd_target_reset_request(&sdu);
        break;

    /* target boot */
    case HC_TARGET_BOOT_REQ:
        // start: 7E 20 01 44 00 C1 08 7E
        // stop: 7E 20 01 44 01 D1 29 7E
        cmd_target_boot_request(&sdu);
        break;

    default:
        /* unknown message */
        result = CMD_PROTOCOL_RESULT_INVALID_COMMAND;
        break;
    }

    return result;
}
