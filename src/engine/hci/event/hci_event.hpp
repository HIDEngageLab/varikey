/**
 * \file hci_event.hpp
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

/**
    \brief HCI event definition

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#ifndef __ENGINE_HCI_EVENT_HPP__
#define __ENGINE_HCI_EVENT_HPP__

#include "macros.hpp"

/* Really size is 5 bytes */
#define HIL_EVENT_VALUE_SIZE 6

/** \brief HCI event type */
typedef enum
{
    HIL_EVENT_KEY = 0x00,
    HIL_EVENT_WHEEL = 0x01,
    HIL_EVENT_DELAY = 0x02,
    HIL_EVENT_DEBUG = 0x03,
    HIL_EVENT_LED = 0x04,
    HIL_EVENT_POWER = 0x05,
    HIL_EVENT_UNDEFINED = 0xff,
} hci_event_type_t;

/** \brief HCI key identifier */
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
} hci_key_identifier_t;

/** \brief HCI key level */
typedef enum
{
    HIL_KEY_LEVEL_PRESS = 0x00,
    HIL_KEY_LEVEL_RELEASE = 0x01,
    HIL_KEY_LEVEL_CLICK = 0x02,
    HIL_KEY_LEVEL_PUSH = 0x03,
    HIL_KEY_LEVEL_UNDEFINED = 0xff,
} hci_key_level_t;

/** \brief HCI debug identifier */
typedef enum
{
    HIL_DBG_PIN1 = 0x0a,
    HIL_DBG_PIN2 = 0x0b,
    HIL_DBG_PIN3 = 0x0c,
    HIL_DBG_PIN4 = 0x0d,
} hci_debug_identifier_t;

/** \brief HCI debug level */
typedef enum
{
    HIL_DEBUG_LEVEL_LOW = 0x00,
    HIL_DEBUG_LEVEL_HIGH = 0x01,
    HIL_DEBUG_LEVEL_UNDEFINED = 0xff,
} hci_debug_level_t;

/** \brief HCI led identifier */
typedef enum
{
    HIL_LED_TEST1 = 0x0e,
    HIL_LED_TEST2 = 0x0f,
} hci_led_identifier_t;

/** \brief HCI led level */
typedef enum
{
    HIL_LED_LEVEL_OFF = 0x00,
    HIL_LED_LEVEL_ON = 0x01,
    HIL_LED_LEVEL_UNDEFINED = 0xff,
} hci_led_level_t;

/** \brief Voltages type */
typedef enum
{
    VOLTAGE_1V8 = 0x00,
    VOLTAGE_3V2 = 0x01,
    VOLTAGE_5V0 = 0x02,
    VOLTAGE_SVB = 0x03,
    VOLTAGE_UNDEFINED = 0xff,
} hci_power_voltage_t;

/** \brief HCI led level */
typedef enum
{
    HIL_POWER_BELOW = 0x00,
    HIL_POWER_ABOVE = 0x01,
    HIL_POWER_NORMAL = 0x02,
    HIL_POWER_UNDEFINED = 0xff,
} hci_power_t;

/** \brief HCI keyboard event */
typedef struct hil_event_key_structure
{
    hci_key_identifier_t id;
    hci_key_level_t level;
} hci_event_key_t;

/** \brief HCI wheel event */
typedef struct hci_event_wheel_structure
{
    float value;
} hci_event_wheel_t;

/** \brief HCI delay event */
typedef struct hci_event_delay_structure
{
    float value;
} hci_event_delay_t;

/** \brief HCI debug event */
typedef struct hci_event_debug_structure
{
    hci_debug_identifier_t id;
    hci_debug_level_t level;
} hci_event_debug_t;

/** \brief HCI led event */
typedef struct hci_event_led_structure
{
    hci_led_identifier_t id;
    hci_led_level_t level;
} hci_event_led_t;

/** \brief HCI power event */
typedef struct hci_event_power_structure
{
    hci_power_voltage_t voltage;
    hci_power_t level;
    float value;
    float limit_low;
    float limit_high;
} hci_event_power_t;

/** \brief HCI event union */
typedef union
{
    hci_event_key_t key;
    hci_event_wheel_t wheel;
    hci_event_delay_t delay;
    hci_event_debug_t debug;
    hci_event_led_t led;
    hci_event_power_t power;
} hci_event_common_t;

typedef struct hil_event_typed_structure
{
    hci_event_type_t type;
    hci_event_common_t common;
} hci_event_typed_t;

typedef union hci_event_union
{
    uint8_t value[HIL_EVENT_VALUE_SIZE];
    hci_event_typed_t typed;
} hci_event_t;

typedef struct hci_event_timed_structure
{
    uint64_t timestamp;
    hci_event_t event;
} hci_event_timed_t;

#endif /* __ENGINE_HCI_EVENT_HPP__ */
