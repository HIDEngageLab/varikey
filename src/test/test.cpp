/**
 * \file test.cpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#include <hardware/flash.h>
#include <pico/bootrom.h>
#include <pico/stdlib.h>
#include <pico/time.h>
#include <stdio.h>

#include "unit_test.hpp"

#define TEST_PARAMETER_FLASH_START 0x10100000

struct test_parameter_struct
{
    uint16_t group;
    uint16_t identifier;
} __attribute__((packed));

test_parameter_struct * test_parameter = reinterpret_cast<test_parameter_struct *>(TEST_PARAMETER_FLASH_START);

int main(void)
{
    stdio_init_all();

    printf("test group:      %d\n", test_parameter->group);
    printf("test identifier: %d\n", test_parameter->identifier);

    int number_failed = 0xff;

    switch (test_parameter->group)
    {
    case 0:
        number_failed = test_checksum(test_parameter->identifier);
        break;
    default:
        printf("FAILED: ");
        printf("unknown group\n");
        break;
    }

    if (number_failed)
    {
        printf("FAILED: ");
        printf("test_checksum %d\n", number_failed);
    }
    else
    {
        printf("PASSED: ");
        printf("test_checksum\n");
    }

    printf("__UNIT_TEST_DONE__\n");

    /* reboot rp2040 in bootsel mode */
    reset_usb_boot((0x00000001 << PICO_DEFAULT_LED_PIN), 0);
}