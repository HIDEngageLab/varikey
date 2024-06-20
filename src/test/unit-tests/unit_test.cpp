/**
 * \file unit_test.cpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 * 
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#include "unit_test.hpp"
#include "unity.h"

void setUp(void)
{
}

void tearDown(void)
{
}

extern void test_unknown(void)
{
    TEST_ASSERT_MESSAGE(0, "unknown test");
}
