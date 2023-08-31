/**
 * \file images.c
 * \author Koch, Roman (koch.roman@googlemail.com)
 * \brief
 *
 * @copyright Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 *
 */

#include "images.h"
#include "image_frame.h"
#include "image_gmc.h"
#include "image_heart.h"

const image_t FRAME = {.width = 128, .height = 32, .data = IMAGE_FRAME};
const image_t LOGO = {.width = 32, .height = 32, .data = IMAGE_GMC};
const image_t HEART = {.width = 32, .height = 32, .data = IMAGE_HEART};
