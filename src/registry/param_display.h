/**
 * \file param_display.h
 * \author Koch, Roman (koch.roman@googlemail.com)
 * \brief
 * \version 0.1
 * @date 2023-03-28
 *
 * @copyright Copyright (c) 2023
 *
 */
/**
    \brief Parameter "wheel"

    \internal
    \author Roman Koch, koch.roman@googlemail.com
*/

#ifndef __PARAM_DISPLAY_H__
#define __PARAM_DISPLAY_H__

#include "parameter.h"

/**
    \brief Button parameter

    Parameter with two short values for button click and push times in ms.
*/
typedef union
{
    uint8_t byte[sizeof(uint16_t) * 2];
    /** \brief Node wheel details */
    struct param_display_struct
    {
        uint16_t click_ms;
        uint16_t push_ms;
    } display;
} param_display_t;

extern param_display_t g_display;

extern void param_display_init(void);

extern void param_display_deserialize(uint8_t const *const _space);
extern void param_display_serialize(uint8_t *const _space);

#endif /* __PARAM_DISPLAY_H__ */
