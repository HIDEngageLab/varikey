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

#include <string.h>
#include <pico/stdlib.h>
#include "../pulp/types.h"
#include "param_button.h"

#define DEFAULT_CLICK_MS 128
#define DEFAULT_PUSH_MS 384

param_button_t g_button = {{0xff, 0xff, 0xff, 0xff}};

/**
    \brief initialize field with default values
*/
extern void param_button_init(void)
{
    g_button.button.click_ms = DEFAULT_CLICK_MS;
    g_button.button.push_ms = DEFAULT_PUSH_MS;
}

/**
    \brief Deserialize vwheel parameter value
*/
extern void param_button_deserialize(uint8_t const *const _space)
{
    /* ATTENTION: NO CHECKS */
    g_button.button.click_ms = SETWORD(_space[0], _space[1]);
    g_button.button.push_ms = SETWORD(_space[2], _space[3]);
}

/**
    \brief Serialize vwheel parameter value
*/
extern void param_button_serialize(uint8_t *const _space)
{
    /* ATTENTION: NO CHECKS */
    _space[0] = HIBYTE(g_button.button.click_ms);
    _space[1] = LOBYTE(g_button.button.click_ms);
    _space[2] = HIBYTE(g_button.button.push_ms);
    _space[3] = LOBYTE(g_button.button.push_ms);
}
