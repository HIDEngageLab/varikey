/**
 * \file cmd_target.hpp
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */
/**
    \brief Module target

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#ifndef __CMD_TARGET_HPP__
#define __CMD_TARGET_HPP__

#include "chunk.h"
#include "cmd_target_power_msg.hpp"

extern void cmd_target_power_request(chunk_t const *const _chunk);
extern void cmd_target_power_indication(cmd_power_voltage_t const _voltage, float const _value);

extern void cmd_target_reset_request(chunk_t const *const _chunk);
extern void cmd_target_boot_request(chunk_t const *const _chunk);

#endif /* __CMD_TARGET_HPP__ */
