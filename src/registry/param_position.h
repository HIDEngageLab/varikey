/**
 * \file param_position.h
 * \author Koch, Roman (koch.roman@googlemail.com)
 * \brief
 *
 * @copyright Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 *
 */
/**
    \brief Parameter "position"

    \internal
    \author Roman Koch, koch.roman@googlemail.com
*/

#ifndef __PARAM_POSITION_H__
#define __PARAM_POSITION_H__

#include "parameter.h"

/**
    \brief Position parameter

    Parameter with two float values for latitude and longitude.
*/
typedef union
{
    uint8_t byte[sizeof(float) * 2];
    /** \brief Node position details */
    struct param_position_struct
    {
        float latitude;
        float longitude;
    } coordinates;
} param_position_t;

extern param_position_t g_position;

extern void param_position_init(void);

extern void param_position_deserialize(uint8_t const *const _space);
extern void param_position_serialize(uint8_t *const _space);

#endif /* __PARAM_POSITION_H__ */
