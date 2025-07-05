// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: Hardware rp2040 temperature functionality
// SPDX-FileType: SOURCE

#include <hardware/adc.h>
#include <pico/stdlib.h>

#include "rp2040_temperature.hpp"

namespace platform::soc
{
    typedef enum
    {
        UNDEFINED,
        ENABLED
    } status_t;

    static status_t status = UNDEFINED;

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

    const uint16_t RP2040Temperature::get_raw_value(void) const
    {
        assert(status == ENABLED);
        (void)adc_read();
        return adc_read();
    }

    const float RP2040Temperature::get_value(void) const
    {
        uint16_t raw = get_raw_value();
        const float conversion = 3.3f / (1 << 12);
        float voltage = raw * conversion;
        float value = 27.0 - (voltage - 0.706) / 0.001721;
        return value;
    }
}
