/**
 * \file unit_test.hpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 * 
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <stdint.h>

extern int test_checksum(const uint16_t _identifier);
extern int test_random(const uint16_t _identifier);

extern void test_unknown(void);
