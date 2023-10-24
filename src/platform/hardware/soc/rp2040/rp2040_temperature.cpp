/**
 * \file rp2040_temperature.cpp
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

/**
    \brief Handle internal temperature sensor

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#include <hardware/adc.h>
#include <pico/stdlib.h>

#include "rp2040_temperature.hpp"

namespace platform
{
    namespace soc
    {
        typedef enum
        {
            UNDEFINED,
            ENABLED
        } status_t;

        status_t status = UNDEFINED;

        /**
         * \brief Initialize ADC and internal temperature sensor
         */
        void RP2040Temperature::initialize(void)
        {
            assert(status == UNDEFINED);
            status = ENABLED;


            adc_init();
            adc_set_temp_sensor_enabled(true);
            adc_select_input(4);
            // adc_disable();
        }

        void RP2040Temperature::shutdown()
        {
        }

        /**
            \brief Return ADC value
        */
        uint16_t RP2040Temperature::get_raw_value(void)
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
        float RP2040Temperature::get_value(void)
        {
            uint16_t raw = get_raw_value();
            const float conversion = 3.3f / (1 << 12);
            float voltage = raw * conversion;
            float value = 27.0 - (voltage - 0.706) / 0.001721;
            return value;
        }
    }
}
