/**
 * \file test_checksum.cpp
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

static uint8_t a[10] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a};
static chunk_t b = {a, 10};

static const uint16_t INITAL_VALUE = 0;

static const uint16_t RESULT_SUM = 55;
static const uint16_t RESULT_CRC = 0xcd4b;
static const uint16_t RESULT_CRC_REFLECTED = 0x94c5;
static const uint16_t RESULT_CRC_POST = 0xcd4b;
static const uint16_t RESULT_CRC_REFLECTED_POST = 0x94c5;
static const uint32_t RESULT_HASH = 0xb384c08b;

void test_checksum_sum(void)
{
    const uint16_t result_value = checksum_sum(&b, INITAL_VALUE);
    printf("checksum sum: %04x %d\n", result_value, result_value);
    TEST_ASSERT_MESSAGE(result_value == RESULT_SUM, "wrong checksum");
}

void test_checksum_crc(void)
{
    const uint16_t result_value = checksum_crc(&b, INITAL_VALUE);
    printf("checksum crc: %04x\n", result_value);
    TEST_ASSERT_MESSAGE(result_value == RESULT_CRC, "wrong crc");
}

void test_checksum_crc_reflected(void)
{
    const uint16_t result_value = checksum_crc_reflected(&b, INITAL_VALUE);
    printf("checksum crc reflected: %04x\n", result_value);
    TEST_ASSERT_MESSAGE(result_value == RESULT_CRC_REFLECTED, "wrong reflected crc");
}

void test_checksum_crc_byte(void)
{
    uint16_t result_value = INITAL_VALUE;
    const size_t ARRAY_SIZE = sizeof(a) / sizeof(a[0]);
    for (size_t i = 0; i < ARRAY_SIZE; ++i)
    {
        result_value = checksum_crc_byte(a[i], result_value);
    }

    printf("checksum crc byte: %04x\n", result_value);
    TEST_ASSERT_MESSAGE(result_value == RESULT_CRC, "wrong crc byte by byte");
}

void test_checksum_crc_post(void)
{
    const uint16_t crc_result_value = checksum_crc(&b, INITAL_VALUE);
    printf("checksum crc: %04x\n", crc_result_value);
    TEST_ASSERT_MESSAGE(crc_result_value == RESULT_CRC, "wrong crc");

    const uint16_t post_result_value = checksum_crc_postprocess(crc_result_value);
    printf("checksum post: %04x\n", post_result_value);
    TEST_ASSERT_MESSAGE(post_result_value == RESULT_CRC_POST, "wrong post value");
}

void test_checksum_crc_reflected_post(void)
{
    const uint16_t crc_result_value = checksum_crc_reflected(&b, INITAL_VALUE);
    printf("checksum crc: %04x\n", crc_result_value);
    TEST_ASSERT_MESSAGE(crc_result_value == RESULT_CRC_REFLECTED, "wrong crc value");

    const uint16_t post_result_value = checksum_crc_postprocess(crc_result_value);
    printf("checksum post: %04x\n", post_result_value);
    TEST_ASSERT_MESSAGE(post_result_value == RESULT_CRC_REFLECTED_POST, "bla blub test assert");
}

void test_checksum_hash(void)
{
    const uint32_t result_value = checksum_hash(&b);
    printf("checksum hash: %08x\n", result_value);
    TEST_ASSERT_MESSAGE(result_value == RESULT_HASH, "wrong hash value");
}


extern int test_checksum(const uint16_t _identifier)
{
    UNITY_BEGIN();

    switch (_identifier)
    {
    case 0:
        RUN_TEST(test_checksum_sum);
        break;
    case 1:
        RUN_TEST(test_checksum_hash);
        break;
    case 2:
        RUN_TEST(test_checksum_crc);
        break;
    case 3:
        RUN_TEST(test_checksum_crc_reflected);
        break;
    case 4:
        RUN_TEST(test_checksum_crc_byte);
        break;
    case 5:
        RUN_TEST(test_checksum_crc_post);
        break;
    case 6:
        RUN_TEST(test_checksum_crc_reflected_post);
        break;
    default:
        printf("wrong identifier: %d\n", _identifier);
        RUN_TEST(test_unknown);
        break;
    }

    return UNITY_END();
}
