/**
 * \file cmd_macro_load.hpp
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */
/**
    \brief Load macro

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#ifndef __CMD_MACRO_LOAD_HPP__
#define __CMD_MACRO_LOAD_HPP__

#include "chunk.h"

extern void cmd_macro_load_request(chunk_t const *_chunk);
extern void cmd_macro_load_response(chunk_t const *_chunk);

#endif /* __CMD_MACRO_LOAD_HPP__ */
