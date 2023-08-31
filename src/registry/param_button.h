/*
    GMC INSTRUMENTS, GMC-I Messtechnik GmbH
    Südwestpark 15, D-90449 Nürnberg, +4991186020, www.gossenmetrawatt.com
    Roman Koch, roman.koch@gossenmetrawatt.com, koch.roman@googlemail.com

    Copyright (c) 2019-2021 - All rights reserved
    Unauthorized copying of this file, via any medium is strictly prohibited
    Proprietary and confidential
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
