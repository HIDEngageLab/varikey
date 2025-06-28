/**
 * \file adp5585.cpp
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#include <stdint.h>
#include <stdio.h>

#include <hardware/i2c.h>
#include <pico/assert.h>

#include "keymatrix_chip.hpp"

/* register map */
#define ADP5585_ID 0x00
#define ADP5585_INT_STATUS 0x01
#define ADP5585_STATUS 0x02
#define ADP5585_FIFO_1 0x03
#define ADP5585_FIFO_2 0x04
#define ADP5585_FIFO_3 0x05
#define ADP5585_FIFO_4 0x06
#define ADP5585_FIFO_5 0x07
#define ADP5585_FIFO_6 0x08
#define ADP5585_FIFO_7 0x09
#define ADP5585_FIFO_8 0x0A
#define ADP5585_FIFO_9 0x0B
#define ADP5585_FIFO_10 0x0C
#define ADP5585_FIFO_11 0x0D
#define ADP5585_FIFO_12 0x0E
#define ADP5585_FIFO_13 0x0F
#define ADP5585_FIFO_14 0x10
#define ADP5585_FIFO_15 0x11
#define ADP5585_FIFO_16 0x12
#define ADP5585_GPI_INT_STAT_A 0x13
#define ADP5585_GPI_INT_STAT_B 0x14
#define ADP5585_GPI_STATUS_A 0x15
#define ADP5585_GPI_STATUS_B 0x16
#define ADP5585_RPULL_CONFIG_A 0x17
#define ADP5585_RPULL_CONFIG_B 0x18
#define ADP5585_RPULL_CONFIG_C 0x19
#define ADP5585_RPULL_CONFIG_D 0x1A
#define ADP5585_GPI_INT_LEVEL_A 0x1B
#define ADP5585_GPI_INT_LEVEL_B 0x1C
#define ADP5585_GPI_EVENT_EN_A 0x1D
#define ADP5585_GPI_EVENT_EN_B 0x1E
#define ADP5585_GPI_INTERRUPT_EN_A 0x1F
#define ADP5585_GPI_INTERRUPT_EN_B 0x20
#define ADP5585_DEBOUNCE_DIS_A 0x21
#define ADP5585_DEBOUNCE_DIS_B 0x22
#define ADP5585_GPO_DATA_OUT_A 0x23
#define ADP5585_GPO_DATA_OUT_B 0x24
#define ADP5585_GPO_OUT_MODE_A 0x25
#define ADP5585_GPO_OUT_MODE_B 0x26
#define ADP5585_GPIO_DIRECTION_A 0x27
#define ADP5585_GPIO_DIRECTION_B 0x28
#define ADP5585_RESET1_EVENT_A 0x29
#define ADP5585_RESET1_EVENT_B 0x2A
#define ADP5585_RESET1_EVENT_C 0x2B
#define ADP5585_RESET2_EVENT_A 0x2C
#define ADP5585_RESET2_EVENT_B 0x2D
#define ADP5585_RESET_CFG 0x2E
#define ADP5585_PWM_OFFT_LOW 0x2F
#define ADP5585_PWM_OFFT_HIGH 0x30
#define ADP5585_PWM_ONT_LOW 0x31
#define ADP5585_PWM_ONT_HIGH 0x32
#define ADP5585_PWM_CFG 0x33
#define ADP5585_LOGIC_CFG 0x34
#define ADP5585_LOGIC_FF_CFG 0x35
#define ADP5585_LOGIC_INT_EVENT_EN 0x36
#define ADP5585_POLL_TIME_CFG 0x37
#define ADP5585_PIN_CONFIG_A 0x38
#define ADP5585_PIN_CONFIG_B 0x39
#define ADP5585_PIN_CONFIG_C 0x3A
#define ADP5585_GENERAL_CFG 0x3B
#define ADP5585_INT_EN 0x3C

/* ADP5585_ID */
#define ADP5585_DEVICE_ID_MASK 0xFF
#define ADP5585_MAN_ID_MASK 0xF0
#define ADP5585_MAN_ID_SHIFT 4
#define ADP5585_MAN_ID 0x02
#define ADP5585_REV_ID_MASK 0x0F

/* ADP5585_INT_STATUS */
#define LOGIC_INT (1 << 4)
#define OVRFLOW_INT (1 << 2)
#define GPI_INT (1 << 1)
#define EVENT_INT (1 << 0)

/* ADP5585_STATUS */
#define LOGIC_STAT (1 << 6)
#define KEC 0xF

/* ADP5585_POLL_TIME_CFG */
#define KEY_POLL_MASK (0x03)
#define KEY_POLL(x) ((x) & 0x03)

/* ADP5585_PIN_CONFIG_A */
#define R4_CFG_MASK (1u << 4)
#define R3_CFG_MASK (1u << 3)
#define R2_CFG_MASK (1u << 2)
#define R1_CFG_MASK (1u << 1)
#define R0_CFG_MASK (1u << 0)

/* ADP5585_PIN_CONFIG_B */
#define C4_CFG_MASK (1u << 4)
#define C3_CFG_MASK (1u << 3)
#define C2_CFG_MASK (1u << 2)
#define C1_CFG_MASK (1u << 1)
#define C0_CFG_MASK (1u << 0)

/* ADP5585_PIN_CONFIG_C */
#define PULL_SELECT (1u << 7)

/* ADP5585_GPI_EVENT_EN_A */
#define GPI_6_EVENT_EN (1u << 5)
#define GPI_5_EVENT_EN (1u << 4)
#define GPI_4_EVENT_EN (1u << 3)
#define GPI_3_EVENT_EN (1u << 2)
#define GPI_2_EVENT_EN (1u << 1)
#define GPI_1_EVENT_EN (1u << 0)

/* ADP5585_GPI_EVENT_EN_B */
#define GPI_11_EVENT_EN (1u << 4)
#define GPI_10_EVENT_EN (1u << 3)
#define GPI_9_EVENT_EN (1u << 2)
#define GPI_8_EVENT_EN (1u << 1)
#define GPI_7_EVENT_EN (1u << 0)

/* ADP5585_GENERAL_CFG */
#define OSC_EN (1 << 7)
#define OSC_FREQ(x) (((x) & 0x03) << 5)
#define OSC_FREQ_MASK(x) (0x03 << 5)
#define INT_CFG (1 << 1)
#define RST_CFG (1 << 0)

/* ADP5585_INT_EN */
#define LOGIC_IEN (1u << 4)
#define OVRFLOW_IEN (1u << 2)
#define GPI_IEN (1u << 1)
#define EVENT_IEN (1u << 0)

namespace platform
{
    namespace hardware
    {

        int adp5585_i2c_address = -1;

        /*
            Attention: potentially not portable structure

            +- - - - - - - -+---    value
            +-+- - - - - - -+
              |             +---    identifier
              +-----------------    state
        */
        typedef struct
        {
            union
            {
                uint8_t value;
                struct
                {
                    uint8_t identifier : 7;
                    uint8_t state : 1;
                } event;
            };
        } event_t;

        uint8_t manufacturer;
        uint8_t revision;

        /*
            single read:
            start address write ack register ack start address read ack data ack stop

            multiple read (not implemented):
            start address write ack register ack start address read ack data ack ... data ack stop
        */
        static void read_byte(uint8_t const _register, uint8_t *_value)
        {
            int number_bytes;

            number_bytes = i2c_write_blocking(i2c_default, adp5585_i2c_address, &_register, 1, true);
            assert(number_bytes != PICO_ERROR_GENERIC);
            assert(number_bytes == 1);

            number_bytes = i2c_read_blocking(i2c_default, adp5585_i2c_address, _value, 1, false);
            assert(number_bytes != PICO_ERROR_GENERIC);
            assert(number_bytes == 1);
        }

        /*
            single write:
            start address write ack register ack data ack stop

            multiple write (not implemented):
            start address write ack register ack write ack ... write ack stop
        */
        static void write_byte(uint8_t const _register, uint8_t const _value)
        {
            uint8_t const buffer[] = {_register, _value};
            int number_bytes = i2c_write_blocking(i2c_default, adp5585_i2c_address, buffer, 2, false);
            assert(number_bytes != PICO_ERROR_GENERIC);
            assert(number_bytes == 2);
        }

        static void read_id(uint8_t *_manufacturer, uint8_t *_revision)
        {
            uint8_t buffer;
            read_byte(ADP5585_ID, &buffer);

            *_manufacturer = (buffer & ADP5585_MAN_ID_MASK) >> ADP5585_MAN_ID_SHIFT;
            *_revision = (buffer & ADP5585_REV_ID_MASK);
        }

        static void read_int_status(uint8_t *value)
        {
            uint8_t buffer;
            read_byte(ADP5585_INT_STATUS, &buffer);

            *value = buffer & 0x1f;
        }

        static void write_int_clear()
        {
            uint8_t const value = EVENT_INT | GPI_INT | OVRFLOW_INT | LOGIC_INT;
            write_byte(ADP5585_INT_STATUS, value);
        }

        static void init_keypad_rows()
        {
            uint8_t const value = R4_CFG_MASK | R3_CFG_MASK | R2_CFG_MASK | R1_CFG_MASK | R0_CFG_MASK;
            write_byte(ADP5585_PIN_CONFIG_A, value);
        }

        static void init_keypad_cols()
        {
            /* leave C4_CFG_MASK, C3_CFG_MASK, C2_CFG_MASK as GPIO */
            uint8_t const value = C1_CFG_MASK | C0_CFG_MASK;
            write_byte(ADP5585_PIN_CONFIG_B, value);
        }

        static void init_keypad_buttons()
        {
            uint8_t const value = GPI_11_EVENT_EN | GPI_10_EVENT_EN | GPI_9_EVENT_EN;
            write_byte(ADP5585_GPI_EVENT_EN_B, value);
        }

        static void init_interrupts()
        {
            uint8_t const value = OVRFLOW_IEN | EVENT_IEN;
            write_byte(ADP5585_INT_EN, value);
        }

        static int read_number_of_events()
        {
            uint8_t buffer;
            read_byte(ADP5585_STATUS, &buffer);

            return (buffer & 0x0f);
        }

        static void start_scanner()
        {
            uint8_t const value = OSC_EN; // | OSC_FREQ(0x03) | INT_CFG;
            write_byte(ADP5585_GENERAL_CFG, value);
        }

        static void stop_scanner()
        {
            write_byte(ADP5585_GENERAL_CFG, 0);
        }

        static void pop_event(uint8_t *const state, uint8_t *const identifier)
        {
            event_t buffer;
            read_byte(ADP5585_FIFO_1, &buffer.value);

            *state = buffer.event.state;
            *identifier = buffer.event.identifier;
        }

        extern void platform_adp5585_init(int const _address)
        {
            adp5585_i2c_address = _address;

            read_id(&manufacturer, &revision);
            // printf("keypad manufacturer:%d, revision:%d\n", manufacturer, revision);

            uint8_t ints;
            read_int_status(&ints);
            // printf("ints:%d\n", ints);

            init_keypad_rows();
            init_keypad_cols();
            init_keypad_buttons();
            init_interrupts();

            start_scanner();
        }

        extern bool platform_adp5585_has_event(void)
        {
            uint8_t event_count;
            read_byte(ADP5585_STATUS, &event_count);

            return (event_count > 0) ? true : false;
        }

        extern void platform_adp5585_get_event(uint8_t *const _state, uint8_t *const _identifier)
        {
            pop_event(_state, _identifier);
            write_int_clear();
        }

    }
}