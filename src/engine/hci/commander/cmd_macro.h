/**
 * \file cmd_macro.h
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 *
 */
/**
    \brief Macro handling

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#ifndef __CMD_MACRO_H__
#define __CMD_MACRO_H__

#include "chunk.h"
#include "hil_event.h"

extern void cmd_macro_key_request(chunk_t const *_chunk);
extern void cmd_macro_clean_request(chunk_t const *_chunk);

#endif /* __CMD_MACRO_H__ */
