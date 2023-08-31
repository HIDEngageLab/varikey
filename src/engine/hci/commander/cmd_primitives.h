/**
 * \file cmd_primitives.h
 * \author Koch, Roman (koch.roman@googlemail.com)
 * \brief
 * \version 0.1
 * @date 2023-03-28
 *
 * @copyright Copyright (c) 2023
 *
 */
/**
	\brief Specifies message direction

	\internal
	\author Roman Koch, koch.roman@googlemail.com
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
