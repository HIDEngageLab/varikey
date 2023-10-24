/**
 * \file cmd_macro_session.hpp
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */
/**
    \brief Macro handling

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#ifndef __CMD_MACRO_SESSION_HPP__
#define __CMD_MACRO_SESSION_HPP__

#include <pico/time.h>

#include "storage_interface.hpp"

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

#endif /* __CMD_MACRO_SESSION_HPP__ */
