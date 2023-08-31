/**
 * \file commander.h
 * \author Koch, Roman (koch.roman@googlemail.com)
 * \brief
 *
 * @copyright Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 *
 */
/**
    \brief Command interpreter on the host interface

    \internal
    \author Roman Koch, koch.roman@googlemail.com
*/

#ifndef __SERIAL_COMMANDER_H__
#define __SERIAL_COMMANDER_H__

#include "chunk.h"
#include "cmd_hci_status_msg.h"
#include "cmd_primitives.h"

#define SERIAL_COMMANDER_INTERPRETER_ADDRESS 0x20

/*
    python lines to print proper command codes

    CMD_REQ = 0
    CMD_CFM = 1
    CMD_IND = 2
    CMD_RES = 3
    CMD_OFFSET = 2

    for i in range(0, 20):
        str = '0x%02X ' % i
        str += "REQ:0x%02X " % ((i << CMD_OFFSET) + CMD_REQ)
        str += "CFM:0x%02X " % ((i << CMD_OFFSET) + CMD_CFM)
        str += "IND:0x%02X " % ((i << CMD_OFFSET) + CMD_IND)
        str += "RES:0x%02X " % ((i << CMD_OFFSET) + CMD_RES)
        print(str)
*/
/*
    0x00 REQ:0x00 CFM:0x01 IND:0x02 RES:0x03
    0x01 REQ:0x04 CFM:0x05 IND:0x06 RES:0x07
    0x02 REQ:0x08 CFM:0x09 IND:0x0A RES:0x0B
    0x03 REQ:0x0C CFM:0x0D IND:0x0E RES:0x0F
    0x04 REQ:0x10 CFM:0x11 IND:0x12 RES:0x13
    0x05 REQ:0x14 CFM:0x15 IND:0x16 RES:0x17
    0x06 REQ:0x18 CFM:0x19 IND:0x1A RES:0x1B
    0x07 REQ:0x1C CFM:0x1D IND:0x1E RES:0x1F
    0x08 REQ:0x20 CFM:0x21 IND:0x22 RES:0x23
    0x09 REQ:0x24 CFM:0x25 IND:0x26 RES:0x27
    0x0A REQ:0x28 CFM:0x29 IND:0x2A RES:0x2B
    0x0B REQ:0x2C CFM:0x2D IND:0x2E RES:0x2F
    0x0C REQ:0x30 CFM:0x31 IND:0x32 RES:0x33
    0x0D REQ:0x34 CFM:0x35 IND:0x36 RES:0x37
    0x0E REQ:0x38 CFM:0x39 IND:0x3A RES:0x3B
    0x0F REQ:0x3C CFM:0x3D IND:0x3E RES:0x3F
    0x10 REQ:0x40 CFM:0x41 IND:0x42 RES:0x43
    0x11 REQ:0x44 CFM:0x45 IND:0x46 RES:0x47
    0x12 REQ:0x48 CFM:0x49 IND:0x4A RES:0x4B
    0x13 REQ:0x4C CFM:0x4D IND:0x4E RES:0x4F
*/

#define HC_PROTOCOL 0x00
#define HC_RESET 0x01
#define HC_STATUS 0x02
#define HC_FIRMWARE 0x03
#define HC_HARDWARE 0x04
#define HC_IDENTITY 0x05
#define HC_PARAM 0x06
#define HC_KEY 0x07
#define HC_MACRO_STORE 0x08
#define HC_MACRO_LOAD 0x09
#define HC_MACRO_CLEAN 0x0a
#define HC_RESERVED_0B 0x02
#define HC_EVENT_TRIGGER 0x0c
#define HC_TEMPERATURE 0x0d
#define HC_TARGET_POWER 0x0e
#define HC_RESERVED_0F 0x02
#define HC_TARGET_RESET 0x10
#define HC_TARGET_BOOT 0x11

#define CMD_OFFSET 2

/* \name HCI interface */
/* @{ */

/* \name Protocol status */
/* @{ */
#define HC_PROTOCOL_IND_VALUE ((HC_PROTOCOL << CMD_OFFSET) + CMD_IND)
/* @} */

/* \name Module restart */
/* @{ */
#define HC_RESET_REQ_VALUE ((HC_RESET << CMD_OFFSET) + CMD_REQ)
#define HC_RESET_IND_VALUE ((HC_RESET << CMD_OFFSET) + CMD_IND)
/* @} */

/* \name Operation mode */
/* @{ */
#define HC_STATUS_REQ_VALUE ((HC_STATUS << CMD_OFFSET) + CMD_REQ)
#define HC_STATUS_CFM_VALUE ((HC_STATUS << CMD_OFFSET) + CMD_CFM)
#define HC_STATUS_IND_VALUE ((HC_STATUS << CMD_OFFSET) + CMD_IND)
/* @} */

/* \name Firmware version */
/* @{ */
#define HC_FIRMWARE_REQ_VALUE ((HC_FIRMWARE << CMD_OFFSET) + CMD_REQ)
#define HC_FIRMWARE_CFM_VALUE ((HC_FIRMWARE << CMD_OFFSET) + CMD_CFM)
/* @} */

/* \name Hardware version */
/* @{ */
#define HC_HARDWARE_REQ_VALUE ((HC_HARDWARE << CMD_OFFSET) + CMD_REQ)
#define HC_HARDWARE_CFM_VALUE ((HC_HARDWARE << CMD_OFFSET) + CMD_CFM)
/* @} */

/* \name Module identifier */
/* @{ */
#define HC_IDENTITY_REQ_VALUE ((HC_IDENTITY << CMD_OFFSET) + CMD_REQ)
#define HC_IDENTITY_CFM_VALUE ((HC_IDENTITY << CMD_OFFSET) + CMD_CFM)
/* @} */

/* \name Parameter request */
/* @{ */
#define HC_PARAM_REQ_VALUE ((HC_PARAM << CMD_OFFSET) + CMD_REQ)
#define HC_PARAM_CFM_VALUE ((HC_PARAM << CMD_OFFSET) + CMD_CFM)
/* @} */

/* \name (Hash-)Key management */
/* @{ */
#define HC_KEY_REQ_VALUE ((HC_KEY << CMD_OFFSET) + CMD_REQ)
#define HC_KEY_CFM_VALUE ((HC_KEY << CMD_OFFSET) + CMD_CFM)
/* @} */

/* \name Macro transport */
/* @{ */
#define HC_MACRO_STORE_REQ_VALUE ((HC_MACRO_STORE << CMD_OFFSET) + CMD_REQ)
#define HC_MACRO_STORE_CFM_VALUE ((HC_MACRO_STORE << CMD_OFFSET) + CMD_CFM)
#define HC_MACRO_STORE_IND_VALUE ((HC_MACRO_STORE << CMD_OFFSET) + CMD_IND)
#define HC_MACRO_STORE_RES_VALUE ((HC_MACRO_STORE << CMD_OFFSET) + CMD_RES)

#define HC_MACRO_LOAD_REQ_VALUE ((HC_MACRO_LOAD << CMD_OFFSET) + CMD_REQ)
#define HC_MACRO_LOAD_CFM_VALUE ((HC_MACRO_LOAD << CMD_OFFSET) + CMD_CFM)
#define HC_MACRO_LOAD_IND_VALUE ((HC_MACRO_LOAD << CMD_OFFSET) + CMD_IND)
#define HC_MACRO_LOAD_RES_VALUE ((HC_MACRO_LOAD << CMD_OFFSET) + CMD_RES)

#define HC_MACRO_CLEAN_REQ_VALUE ((HC_MACRO_CLEAN << CMD_OFFSET) + CMD_REQ)
#define HC_MACRO_CLEAN_CFM_VALUE ((HC_MACRO_CLEAN << CMD_OFFSET) + CMD_CFM)
/* @} */

/* \name Event trigger */
/* @{ */
#define HC_EVENT_TRIGGER_REQ_VALUE ((HC_EVENT_TRIGGER << CMD_OFFSET) + CMD_REQ)
#define HC_EVENT_TRIGGER_CFM_VALUE ((HC_EVENT_TRIGGER << CMD_OFFSET) + CMD_CFM)
#define HC_EVENT_TRIGGER_IND_VALUE ((HC_EVENT_TRIGGER << CMD_OFFSET) + CMD_IND)
/* @} */

/* \name Temperature */
/* @{ */
#define HC_TEMPERATURE_REQ_VALUE ((HC_TEMPERATURE << CMD_OFFSET) + CMD_REQ)
#define HC_TEMPERATURE_CFM_VALUE ((HC_TEMPERATURE << CMD_OFFSET) + CMD_CFM)
#define HC_TEMPERATURE_IND_VALUE ((HC_TEMPERATURE << CMD_OFFSET) + CMD_IND)
/* @} */

/* \name Power */
/* @{ */
#define HC_TARGET_POWER_REQ_VALUE ((HC_TARGET_POWER << CMD_OFFSET) + CMD_REQ)
#define HC_TARGET_POWER_CFM_VALUE ((HC_TARGET_POWER << CMD_OFFSET) + CMD_CFM)
#define HC_TARGET_POWER_IND_VALUE ((HC_TARGET_POWER << CMD_OFFSET) + CMD_IND)
/* @} */

/* \name Target observe and control */
/* @{ */
#define HC_TARGET_RESET_REQ_VALUE ((HC_TARGET_RESET << CMD_OFFSET) + CMD_REQ)
#define HC_TARGET_RESET_CFM_VALUE ((HC_TARGET_RESET << CMD_OFFSET) + CMD_CFM)
/* @} */

/* \name Target observe and control */
/* @{ */
#define HC_TARGET_BOOT_REQ_VALUE ((HC_TARGET_BOOT << CMD_OFFSET) + CMD_REQ)
#define HC_TARGET_BOOT_CFM_VALUE ((HC_TARGET_BOOT << CMD_OFFSET) + CMD_CFM)
/* @} */

/* @} */

/**
    \brief HCI command type
*/
typedef enum
{
    /* HCI interface */
    HC_PROTOCOL_IND = HC_PROTOCOL_IND_VALUE,
    /* module restart */
    HC_RESET_REQ = HC_RESET_REQ_VALUE,
    HC_RESET_IND = HC_RESET_IND_VALUE,
    /* check hardware version */
    HC_STATUS_REQ = HC_STATUS_REQ_VALUE,
    HC_STATUS_CFM = HC_STATUS_CFM_VALUE,
    HC_STATUS_IND = HC_STATUS_IND_VALUE,
    /* check firmware version */
    HC_FIRMWARE_REQ = HC_FIRMWARE_REQ_VALUE,
    HC_FIRMWARE_CFM = HC_FIRMWARE_CFM_VALUE,
    /* check hardware version */
    HC_HARDWARE_REQ = HC_HARDWARE_REQ_VALUE,
    HC_HARDWARE_CFM = HC_HARDWARE_CFM_VALUE,
    /* check module identifier */
    HC_IDENTITY_REQ = HC_IDENTITY_REQ_VALUE,
    HC_IDENTITY_CFM = HC_IDENTITY_CFM_VALUE,
    /* handle parameter request */
    HC_PARAM_REQ = HC_PARAM_REQ_VALUE,
    HC_PARAM_CFM = HC_PARAM_CFM_VALUE,
    /* data key management */
    HC_KEY_REQ = HC_KEY_REQ_VALUE,
    HC_KEY_CFM = HC_KEY_CFM_VALUE,
    /* macro store/load */
    HC_MACRO_STORE_REQ = HC_MACRO_STORE_REQ_VALUE,
    HC_MACRO_STORE_CFM = HC_MACRO_STORE_CFM_VALUE,
    HC_MACRO_STORE_IND = HC_MACRO_STORE_IND_VALUE,
    HC_MACRO_STORE_RES = HC_MACRO_STORE_RES_VALUE,
    HC_MACRO_LOAD_REQ = HC_MACRO_LOAD_REQ_VALUE,
    HC_MACRO_LOAD_CFM = HC_MACRO_LOAD_CFM_VALUE,
    HC_MACRO_LOAD_IND = HC_MACRO_LOAD_IND_VALUE,
    HC_MACRO_LOAD_RES = HC_MACRO_LOAD_RES_VALUE,
    HC_MACRO_CLEAN_REQ = HC_MACRO_CLEAN_REQ_VALUE,
    HC_MACRO_CLEAN_CFM = HC_MACRO_CLEAN_CFM_VALUE,
    /* event trigger */
    HC_EVENT_TRIGGER_REQ = HC_EVENT_TRIGGER_REQ_VALUE,
    HC_EVENT_TRIGGER_CFM = HC_EVENT_TRIGGER_CFM_VALUE,
    HC_EVENT_TRIGGER_IND = HC_EVENT_TRIGGER_IND_VALUE,
    /* check temperature */
    HC_TEMPERATURE_REQ = HC_TEMPERATURE_REQ_VALUE,
    HC_TEMPERATURE_CFM = HC_TEMPERATURE_CFM_VALUE,
    HC_TEMPERATURE_IND = HC_TEMPERATURE_IND_VALUE,
    /* check target power */
    HC_TARGET_POWER_REQ = HC_TARGET_POWER_REQ_VALUE,
    HC_TARGET_POWER_CFM = HC_TARGET_POWER_CFM_VALUE,
    HC_TARGET_POWER_IND = HC_TARGET_POWER_IND_VALUE,
    /* target control and observation */
    HC_TARGET_RESET_REQ = HC_TARGET_RESET_REQ_VALUE,
    HC_TARGET_RESET_CFM = HC_TARGET_RESET_CFM_VALUE,
    HC_TARGET_BOOT_REQ = HC_TARGET_BOOT_REQ_VALUE,
    HC_TARGET_BOOT_CFM = HC_TARGET_BOOT_CFM_VALUE,
} host_command_t;

extern cmd_hci_status_result_t hci_commander_interpreter(chunk_t const *const _chunk);

#endif /* __SERIAL_COMMANDER_H__ */
