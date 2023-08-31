/**
 * @file param_button.h
 * @author Roman Koch, koch.roman@gmail.com
 * @brief 
 * @version 0.1
 * 
 * @copyright Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 * 
 */
/**
    \brief Parameter "vwheel"

    \internal
    \author Roman Koch, koch.roman@googlemail.com
*/

#ifndef _PARAM_BUTTON_H_
#define _PARAM_BUTTON_H_

#include "parameter.h"

/**
    \brief Button parameter

    Parameter with two short values for button click and push times in ms.
*/
typedef union
{
    uint8_t byte[sizeof(uint16_t) * 2];
    /** \brief Node vwheel details */
    struct param_button_struct
    {
        uint16_t click_ms;
        uint16_t push_ms;
    } button;
} param_button_t;

extern param_button_t g_button;

extern void param_button_init(void);

extern void param_button_deserialize(uint8_t const *const _space);
extern void param_button_serialize(uint8_t *const _space);

#endif /* _PARAM_BUTTON_H_ */
