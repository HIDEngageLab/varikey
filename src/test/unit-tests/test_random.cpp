/**
 * \file test_random.cpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#include <pico/stdlib.h>
#include <stdint.h>
#include <stdio.h>

#include "unit_test.hpp"
#include "unity.h"

#include "checksum.hpp"
#include "chunk.h"
#include "platform.hpp"
#include "random.hpp"

static uint8_t a8[8];
static chunk_t c8 = {a8, 8};
static uint8_t a11[11];
static chunk_t c11 = {a11, 11};
static uint8_t a32[32];
static chunk_t c32 = {a32, 32};

static const int NUMBER_OF_SEQUENCES = 100;
uint16_t pool[NUMBER_OF_SEQUENCES];

void test_random_sequence_8(void)
{
    platform::initialize();
    platform::random_generator.init();
    platform::random_generator.create_sequence(&c8);
    printf("sequence 8: [");
    for (size_t i = 0; i < 8; ++i)
    {
        printf("%02x ", c8.space[i]);
    }
    printf("]\n");
    platform::random_generator.shutdown();
    //platform::shutdown();
    TEST_ASSERT_MESSAGE(1, "done");
}

void test_random_sequence_11(void)
{
    platform::initialize();
    platform::random_generator.init();
    platform::random_generator.create_sequence(&c11);
    printf("sequence 11: [");
    for (size_t i = 0; i < 11; ++i)
    {
        printf("%02x ", c11.space[i]);
    }
    printf("]\n");
    platform::random_generator.shutdown();
    TEST_ASSERT_MESSAGE(1, "done");
}

void test_random_sequence_32(void)
{
    platform::initialize();
    platform::random_generator.init();
    platform::random_generator.create_sequence(&c32);
    printf("sequence 32: [");
    for (size_t i = 0; i < 32; ++i)
    {
        printf("%02x ", c32.space[i]);
    }
    printf("]\n");
    platform::random_generator.shutdown();
    TEST_ASSERT_MESSAGE(1, "done");
}

void test_random_many_sequencs(void)
{
    platform::initialize();
    platform::random_generator.init();

    for (int i = 0; i < NUMBER_OF_SEQUENCES; ++i)
    {
        platform::random_generator.create_sequence(&c8);
        pool[i] = checksum_crc(&c8, 0);
    }
    int equal = 0;
    for (int i = 0; i < NUMBER_OF_SEQUENCES; ++i)
    {
        for (int j = i + 1; j < NUMBER_OF_SEQUENCES; ++j)
        {
            if (pool[i] == pool[j])
            {
                equal++;
            }
        }
    }
    printf("equal sequences: %d\n", equal);
    platform::random_generator.shutdown();
    TEST_ASSERT_MESSAGE(equal == 0, "equal sequences created");
}

extern int test_random(const uint16_t _identifier)
{
    UNITY_BEGIN();

    switch (_identifier)
    {
    case 0:
        RUN_TEST(test_random_sequence_8);
        break;
    case 1:
        RUN_TEST(test_random_sequence_11);
        break;
    case 2:
        RUN_TEST(test_random_sequence_32);
        break;
    case 3:
        RUN_TEST(test_random_many_sequencs);
        break;
    default:
        printf("wrong identifier: %d\n", _identifier);
        RUN_TEST(test_unknown);
        break;
    }

    return UNITY_END();
}
