/**
 * \file engine.h
 * \author Koch, Roman (koch.roman@googlemail.com)
 * \brief
 *
 * @copyright Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 *
 */

#ifndef __ENGINE_H__
#define __ENGINE_H__

#include "chunk.h"

/** \brief HIL mode */
typedef enum
{
	ENGINE_MODE_IDLE = 0x00,
	ENGINE_MODE_ACTIVE = 0x01,
	ENGINE_MODE_PENDING = 0x02,
	ENGINE_MODE_UNDEFINED = 0xff,
} engine_mode_t;

extern void engine_init(void);
extern void engine_start(void);
extern void engine_stop(void);
extern void engine_shutdown(void);

extern void engine_perform(void);
extern void engine_tick(void);

extern engine_mode_t engine_mode_get(void);

#endif /* __ENGINE_H__ */
