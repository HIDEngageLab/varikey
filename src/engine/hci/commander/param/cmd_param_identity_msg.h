/**
 * \file cmd_param_identity_msg.h
 * \author Koch, Roman (koch.roman@googlemail.com)
 * \brief
 * \version 0.1
 * @date 2023-03-28
 *
 * @copyright Copyright (c) 2023
 *
 */
/**
    \brief Identifier message

    \internal
    \author Roman Koch, koch.roman@googlemail.com
*/

#ifndef __CMD_PARAM_IDENTITY_MSG_H__
#define __CMD_PARAM_IDENTITY_MSG_H__

#include "types.h"

typedef struct chunk_struct chunk_t;

/** \brief Identity part type */
typedef enum
{
    CMD_IDENTITY_SERIAL = 0x00,
    CMD_IDENTITY_PLATFORM = 0x03,
    CMD_IDENTITY_ILLEGAL = 0xff,
} cmd_identity_part_t;

/** \brief Identity request result */
typedef enum
{
    CMD_IDENTITY_SUCCESS = SUCCESS,
    CMD_IDENTITY_FAILURE = FAILURE,
    CMD_IDENTITY_UNSUPPORTED = 0x02,
} cmd_identity_result_t;

/** \brief Identity parameter */
typedef struct
{
    cmd_identity_part_t part;
    cmd_identity_result_t result;
    chunk_t value;
} cmd_identity_msg_t;

extern void cmd_param_identity_req(chunk_t const *_chunk, cmd_identity_msg_t *const _msg);
extern void cmd_param_identity_cfm(cmd_identity_msg_t *const _msg);

#endif /* __CMD_PARAM_IDENTITY_MSG_H__ */
