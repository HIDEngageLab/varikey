/**
 * \file cmd_macro_session.h
 * \author Koch, Roman (koch.roman@googlemail.com)
 * \brief
 * \version 0.1
 * @date 2023-03-28
 *
 * @copyright Copyright (c) 2023
 *
 */
/**
    \brief Macro handling

    \internal
    \author Roman Koch, koch.roman@googlemail.com
*/

#ifndef __CMD_MACRO_SESSION_H__
#define __CMD_MACRO_SESSION_H__

#include <pico/time.h>

#include "storage_interface.h"

typedef enum
{
    SESSION_IDLE = 0,
    SESSION_ACTIVE,
} session_state_t;

typedef struct session_struct
{
    session_state_t state;
    uint8_t retry_counter;
    alarm_id_t timeout_id;
    storage_transport_t data;
} session_t;

#endif /* __CMD_MACRO_SESSION_H__ */
