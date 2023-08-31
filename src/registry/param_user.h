/**
 * \file param_user.h
 * \author Koch, Roman (koch.roman@googlemail.com)
 * \brief
 * \version 0.1
 * @date 2023-03-28
 *
 * @copyright Copyright (c) 2023
 *
 */
/**
	\brief Parameter "user register"

	\internal
	\author Roman Koch, koch.roman@googlemail.com
*/

#ifndef __PARAM_USER_H__
#define __PARAM_USER_H__

#include "parameter.h"

#define PARAMETER_USER_SIZE 2

/** \brief Test register for maintainer */
typedef struct param_user_register_struct
{
	uint8_t value[PARAMETER_USER_SIZE];
} param_user_register_t;

/** \brief Global user register parameter */
extern param_user_register_t g_user_register;

extern void param_user_init(void);

extern void param_user_deserialize(uint8_t const *const _chunk);
extern void param_user_serialize(uint8_t *const _space);

#endif /* __PARAM_USER_H__ */
