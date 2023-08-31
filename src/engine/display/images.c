/**
 * \file images.c
 * \author Koch, Roman (koch.roman@googlemail.com)
 * \brief
 * \version 0.1
 * @date 2023-03-28
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "images.h"
#include "image_frame.h"
#include "image_gmc.h"
#include "image_heart.h"

const image_t FRAME = {.width = 128, .height = 32, .data = IMAGE_FRAME};
const image_t LOGO = {.width = 32, .height = 32, .data = IMAGE_GMC};
const image_t HEART = {.width = 32, .height = 32, .data = IMAGE_HEART};
