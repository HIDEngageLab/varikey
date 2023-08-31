/**
 * \file hil_event.h
 * \author Koch, Roman (koch.roman@googlemail.com)
 * \brief
 *
 * @copyright Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 *
 */
/**
    \brief HIL event definition

    \internal
    \author Roman Koch, koch.roman@googlemail.com
*/

#ifndef _COMPOSED_HID_HIL_EVENT_H_
#define _COMPOSED_HID_HIL_EVENT_H_

#include "macros.h"

/* Really size is 5 bytes */
#define HIL_EVENT_VALUE_SIZE 6

/** \brief HIL event type */
typedef enum
{
    HIL_EVENT_KEY = 0x00,
    HIL_EVENT_WHEEL = 0x01,
    HIL_EVENT_DELAY = 0x02,
    HIL_EVENT_DEBUG = 0x03,
    HIL_EVENT_LED = 0x04,
    HIL_EVENT_POWER = 0x05,
    HIL_EVENT_UNDEFINED = 0xff,
} hil_event_type_t;

/** \brief HIL key identifier */
typedef enum
{
    HIL_BTN_S0 = 0x00,
    HIL_BTN_S1 = 0x01,
    HIL_BTN_S2 = 0x02,
    HIL_BTN_S3 = 0x03,
    HIL_BTN_S4 = 0x04,
    HIL_BTN_S5 = 0x05,
    HIL_BTN_S6 = 0x06,
    HIL_BTN_S7 = 0x07,
    HIL_BTN_S8 = 0x08,
    HIL_BTN_S9 = 0x09,
} hil_key_identifier_t;

/** \brief HIL key level */
typedef enum
{
    HIL_KEY_LEVEL_PRESS = 0x00,
    HIL_KEY_LEVEL_RELEASE = 0x01,
    HIL_KEY_LEVEL_CLICK = 0x02,
    HIL_KEY_LEVEL_PUSH = 0x03,
    HIL_KEY_LEVEL_UNDEFINED = 0xff,
} hil_key_level_t;

/** \brief HIL debug identifier */
typedef enum
{
    HIL_DBG_PIN1 = 0x0a,
    HIL_DBG_PIN2 = 0x0b,
    HIL_DBG_PIN3 = 0x0c,
    HIL_DBG_PIN4 = 0x0d,
} hil_debug_identifier_t;

/** \brief HIL debug level */
typedef enum
{
    HIL_DEBUG_LEVEL_LOW = 0x00,
    HIL_DEBUG_LEVEL_HIGH = 0x01,
    HIL_DEBUG_LEVEL_UNDEFINED = 0xff,
} hil_debug_level_t;

/** \brief HIL led identifier */
typedef enum
{
    HIL_LED_TEST1 = 0x0e,
    HIL_LED_TEST2 = 0x0f,
} hil_led_identifier_t;

/** \brief HIL led level */
typedef enum
{
    HIL_LED_LEVEL_OFF = 0x00,
    HIL_LED_LEVEL_ON = 0x01,
    HIL_LED_LEVEL_UNDEFINED = 0xff,
} hil_led_level_t;

/** \brief Voltages type */
typedef enum
{
    VOLTAGE_1V8 = 0x00,
    VOLTAGE_3V2 = 0x01,
    VOLTAGE_5V0 = 0x02,
    VOLTAGE_SVB = 0x03,
    VOLTAGE_UNDEFINED = 0xff,
} hil_power_voltage_t;

/** \brief HIL led level */
typedef enum
{
    HIL_POWER_BELOW = 0x00,
    HIL_POWER_ABOVE = 0x01,
    HIL_POWER_NORMAL = 0x02,
    HIL_POWER_UNDEFINED = 0xff,
} hil_power_t;

/** \brief HIL keyboard event */
typedef struct hil_event_key_structure
{
    hil_key_identifier_t id;
    hil_key_level_t level;
} hil_event_key_t;

/** \brief HIL wheel event */
typedef struct hil_event_wheel_structure
{
    float value;
} hil_event_wheel_t;

/** \brief HIL delay event */
typedef struct hil_event_delay_structure
{
    float value;
} hil_event_delay_t;

/** \brief HIL debug event */
typedef struct hil_event_debug_structure
{
    hil_debug_identifier_t id;
    hil_debug_level_t level;
} hil_event_debug_t;

/** \brief HIL led event */
typedef struct hil_event_led_structure
{
    hil_led_identifier_t id;
    hil_led_level_t level;
} hil_event_led_t;

/** \brief HIL power event */
typedef struct hil_event_power_structure
{
    hil_power_voltage_t voltage;
    hil_power_t level;
    float value;
    float limit_low;
    float limit_high;
} hil_event_power_t;

/** \brief HIL event union */
typedef union
{
    hil_event_key_t key;
    hil_event_wheel_t wheel;
    hil_event_delay_t delay;
    hil_event_debug_t debug;
    hil_event_led_t led;
    hil_event_power_t power;
} hil_event_common_t;

typedef struct hil_event_typed_structure
{
    hil_event_type_t type;
    hil_event_common_t common;
} hil_event_typed_t;

typedef union hil_event_union
{
    uint8_t value[HIL_EVENT_VALUE_SIZE];
    hil_event_typed_t typed;
} hil_event_t;

typedef struct hil_event_timed_structure
{
    uint64_t timestamp;
    hil_event_t event;
} hil_event_timed_t;

#endif /* _COMPOSED_HID_HIL_EVENT_H_ */
