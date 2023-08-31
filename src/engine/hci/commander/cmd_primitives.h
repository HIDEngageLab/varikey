/**
 * \file cmd_primitives.h
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 *
 */
/**
	\brief Specifies message direction

	\internal
	\author Roman Koch, koch.roman@gmail.com
*/

#ifndef __CMD_PRIMITIVES_H__
#define __CMD_PRIMITIVES_H__

/** \brief Message primitives */
typedef enum
{
	CMD_REQ = 0x00,
	CMD_CFM = 0x01,
	CMD_IND = 0x02,
	CMD_RES = 0x03
} cmd_primitives_t;

#endif /* __CMD_PRIMITIVES_H__ */
