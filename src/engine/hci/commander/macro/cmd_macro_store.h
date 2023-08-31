/**
 * \file cmd_macro_store.h
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * @copyright Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 *
 */
/**
    \brief Store macro

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#ifndef __CMD_MACRO_STORE_H__
#define __CMD_MACRO_STORE_H__

#include "chunk.h"

extern void cmd_macro_store_request(chunk_t const *_chunk);
extern void cmd_macro_store_response(chunk_t const *_chunk);

#endif /* __CMD_MACRO_STORE_H__ */
