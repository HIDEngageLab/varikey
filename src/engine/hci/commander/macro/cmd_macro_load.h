/**
 * \file cmd_macro_load.h
 * \author Koch, Roman (koch.roman@googlemail.com)
 * \brief
 *
 * @copyright Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 *
 */
/**
    \brief Load macro

    \internal
    \author Roman Koch, koch.roman@googlemail.com
*/

#ifndef __CMD_MACRO_LOAD_H__
#define __CMD_MACRO_LOAD_H__

#include "chunk.h"

extern void cmd_macro_load_request(chunk_t const *_chunk);
extern void cmd_macro_load_response(chunk_t const *_chunk);

#endif /* __CMD_MACRO_LOAD_H__ */
