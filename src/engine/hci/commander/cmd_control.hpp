/**
 * \file cmd_control.hpp
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */
/**
    \brief Module control

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#ifndef __CMD_CONTROL_HPP__
#define __CMD_CONTROL_HPP__

#include "chunk.h"
#include "cmd_control_reset_msg.hpp"
#include "cmd_control_status_msg.hpp"

extern void cmd_control_reset_request(chunk_t const *const _chunk);
extern void cmd_control_reset_indication(cmd_reset_result_t const _result);
extern void cmd_control_status_request(chunk_t const *const _chunk);
extern void cmd_control_status_indication(cmd_mode_t const _mode, cmd_operation_t const _operation);
extern void cmd_control_temperature_request(chunk_t const *const _chunk);

#endif /* __CMD_CONTROL_HPP__ */
