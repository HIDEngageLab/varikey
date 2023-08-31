/**
 * \file images.h
 * \author Koch, Roman (koch.roman@googlemail.com)
 * \brief
 * \version 0.1
 * @date 2023-03-28
 *
 * @copyright Copyright (c) 2023
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