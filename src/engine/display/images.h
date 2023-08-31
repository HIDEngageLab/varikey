/**
 * \file images.h
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * @copyright Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 *
 */

#ifndef __IMAGES_H__
#define __IMAGES_H__

#include <stdint.h>

typedef struct
{
    uint8_t const width;
    uint8_t const height;
    uint8_t const *data;
} image_t;

enum
{
    KEYPAD_ICON_FRAME = 1,
    KEYPAD_ICON_LOGO,
    KEYPAD_ICON_HEART,
};

extern const image_t FRAME;
extern const image_t LOGO;
extern const image_t HEART;

#endif // __IMAGES_H__