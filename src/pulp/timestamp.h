/**
 * \file timestamp.h
 * \author Koch, Roman (koch.roman@googlemail.com)
 * \brief
 * \version 0.1
 * @date 2023-03-28
 *
 * @copyright Copyright (c) 2023
 *
 */
/**
	\brief Timestamp

	\internal
	\author Roman Koch, koch.roman@googlemail.com
*/

#ifndef __PULP_TIMESTAMP_H__
#define __PULP_TIMESTAMP_H__

#include <stdint.h>

extern void timestamp_reset(void);
extern uint64_t timestamp(void);

#endif /* __PULP_TIMESTAMP_H__ */
