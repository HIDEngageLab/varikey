/**
 * \file cmd_param.hpp
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */
/**
    \brief Module configuration

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#ifndef __CMD_PARAM_HPP__
#define __CMD_PARAM_HPP__

#include "chunk.h"

extern void cmd_param_firmware_request(chunk_t const *_chunk);
extern void cmd_param_hardware_request(chunk_t const *_chunk);
extern void cmd_param_identifier_request(chunk_t const *_chunk);
extern void cmd_param_parameter_request(chunk_t const *_chunk);

#endif /* __CMD_PARAM_HPP__ */
