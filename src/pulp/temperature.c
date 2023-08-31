/**
 * \file temperature.c
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 *
 */
/**
    \brief Handle internal temperature sensor

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#include <hardware/adc.h>
#include <pico/stdlib.h>

#include "temperature.h"

typedef enum
{
    UNDEFINED,
    ENABLED
} status_t;

status_t status = UNDEFINED;

/**
 * \brief Initialize ADC and internal temperature sensor
 */
extern void temperature_init(void)
{
    assert(status == UNDEFINED);
    status = ENABLED;

    adc_init();
    adc_set_temp_sensor_enabled(true);
    adc_select_input(4);
    // adc_disable();
}

/**
    \brief Return ADC value
*/
extern uint16_t temperature_get_raw_value(void)
{
    assert(status == ENABLED);
    (void)adc_read();
    return adc_read();
}

/**
 * \brief Get current chip temperature from internal sensor
 *
 * \return scaled float temperature value
 */
extern float temperature_get(void)
{
    uint16_t raw = temperature_get_raw_value();
    const float conversion = 3.3f / (1 << 12);
    float voltage = raw * conversion;
    float temperature = 27.0 - (voltage - 0.706) / 0.001721;
    return temperature;
}

/**
 * \brief create random byte
 */
extern uint8_t temperature_create_random_byte(void)
{
    assert(status == ENABLED);
    uint8_t result = 0;
    uint8_t mask = 1;

    for (int i = 0; i < 11; ++i)
    {
        uint16_t tmp = temperature_get_raw_value();

        if (tmp & 1)
        {
            result |= mask;
        }
        else
        {
            result &= ~mask;
        }

        if (mask == 0x80)
        {
            mask = 1;
        }
        else
        {
            mask <<= 1;
        }
    }

    return result;
}