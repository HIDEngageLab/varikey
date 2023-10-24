/**
 * \file image_type.hpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#ifndef __IMAGE_TYPE_HPP__
#define __IMAGE_TYPE_HPP__

#include <stdint.h>

typedef struct
{
    uint8_t const width;
    uint8_t const height;
    uint8_t const *data;
} image_t;

#endif // __IMAGE_TYPE_HPP__