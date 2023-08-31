/**
 * \file cmd_control.h
 * \author Koch, Roman (koch.roman@googlemail.com)
 * \brief
 *
 * @copyright Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 *
 */
/**
    \brief Module control

    \internal
    \author Roman Koch, koch.roman@googlemail.com
*/

#ifndef __CMD_CONTROL_H__
#define __CMD_CONTROL_H__

#include "chunk.h"
#include "cmd_control_reset_msg.h"
#include "cmd_control_status_msg.h"

extern void cmd_control_reset_request(chunk_t const *const _chunk);
extern void cmd_control_reset_indication(cmd_reset_result_t const _result);
extern void cmd_control_status_request(chunk_t const *const _chunk);
extern void cmd_control_status_indication(cmd_mode_t const _mode, cmd_operation_t const _operation);
extern void cmd_control_temperature_request(chunk_t const *const _chunk);

#endif /* __CMD_CONTROL_H__ */
