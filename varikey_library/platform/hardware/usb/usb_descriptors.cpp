// SPDX-FileCopyrightText: 2019 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: Hardware usb descriptors functionality
// SPDX-FileType: SOURCE

#include <tusb.h>

#include "engine.hpp"
#include "macros.hpp"
#include "param_serial_number.hpp"
#include "platform_defines.hpp"
#include "revision.h"
#include "usb_descriptors.hpp"

#include "chunk.h"
#include "hid_handler.hpp"
#include "hid_report.hpp"

#define _PRINT_EXTENDED_OUTPUT

#define TUD_HID_REPORT_DESC_CUSTOM(...)                      \
    HID_USAGE_PAGE_N(HID_USAGE_PAGE_VENDOR, 2),              \
        HID_USAGE(0xA0),                                     \
        HID_COLLECTION(HID_COLLECTION_APPLICATION),          \
        __VA_ARGS__                                          \
            HID_USAGE(0x01),                                 \
        HID_LOGICAL_MIN(0x00),                               \
        HID_LOGICAL_MAX(0xFF),                               \
        HID_REPORT_SIZE(8),                                  \
        HID_REPORT_COUNT(3),                                 \
        HID_FEATURE(HID_DATA | HID_VARIABLE | HID_ABSOLUTE), \
        HID_USAGE(0x02),                                     \
        HID_LOGICAL_MIN(0x00),                               \
        HID_LOGICAL_MAX(0xFF),                               \
        HID_REPORT_SIZE(8),                                  \
        HID_REPORT_COUNT(12),                                \
        HID_FEATURE(HID_DATA | HID_VARIABLE | HID_ABSOLUTE), \
        HID_COLLECTION_END

#define _PID_MAP(itf, n) ((CFG_TUD_##itf) << (n))
#define USB_PID ((platform::defines::usb::PID & platform::defines::usb::PID_MASK) | \
                 _PID_MAP(CDC, 0) | _PID_MAP(MSC, 1) | _PID_MAP(HID, 2) |           \
                 _PID_MAP(MIDI, 3) | _PID_MAP(VENDOR, 4))

#define USB_VID (platform::defines::usb::VID)

#define USB_BCD 0x0200

tusb_desc_device_t const desc_device = {
    .bLength = sizeof(tusb_desc_device_t),
    .bDescriptorType = TUSB_DESC_DEVICE,
    .bcdUSB = USB_BCD,
    .bDeviceClass = 0x00,
    .bDeviceSubClass = 0x00,
    .bDeviceProtocol = 0x00,
    .bMaxPacketSize0 = CFG_TUD_ENDPOINT0_SIZE,

    .idVendor = USB_VID,
    .idProduct = USB_PID,
    .bcdDevice = 0x0100,

    .iManufacturer = 0x01,
    .iProduct = 0x02,
    .iSerialNumber = 0x03,

    .bNumConfigurations = 0x01};

uint8_t const *tud_descriptor_device_cb(void)
{
    return (uint8_t const *)&desc_device;
}

uint8_t const desc_hid_report[] = {
    TUD_HID_REPORT_DESC_KEYBOARD(HID_REPORT_ID(static_cast<uint8_t>(platform::usb::COMMAND::KEYBOARD))),
    TUD_HID_REPORT_DESC_MOUSE(HID_REPORT_ID(static_cast<uint8_t>(platform::usb::COMMAND::MOUSE))),
    TUD_HID_REPORT_DESC_CONSUMER(HID_REPORT_ID(static_cast<uint8_t>(platform::usb::COMMAND::CONSUMER))),
    TUD_HID_REPORT_DESC_CUSTOM(HID_REPORT_ID(static_cast<uint8_t>(platform::usb::COMMAND::CUSTOM))),
};

uint8_t const *tud_hid_descriptor_report_cb(uint8_t instance)
{
    (void)instance;
    return desc_hid_report;
}

enum
{
    ITF_NUM_HID,
    ITF_NUM_TOTAL
};

#define CONFIG_TOTAL_LEN (TUD_CONFIG_DESC_LEN + TUD_HID_DESC_LEN)

#define EPNUM_HID 0x81

// HID buffer size Should be sufficient to hold ID (if any) + Data
#define CFG_TUD_HID_EP_BUFSIZE 64

uint8_t const desc_configuration[] = {
    // Config number, interface count, string index, total length, attribute, power in mA
    TUD_CONFIG_DESCRIPTOR(1, ITF_NUM_TOTAL, 0, CONFIG_TOTAL_LEN, TUSB_DESC_CONFIG_ATT_REMOTE_WAKEUP, 100),

    // Interface number, string index, protocol, report descriptor len, EP In address, size & polling interval
    TUD_HID_DESCRIPTOR(ITF_NUM_HID, 0, HID_ITF_PROTOCOL_NONE, sizeof(desc_hid_report), EPNUM_HID, CFG_TUD_HID_EP_BUFSIZE, 5),
    // TUD_HID_DESCRIPTOR(ITF_NUM_HID, 0, HID_ITF_PROTOCOL_NONE, 4, EPNUM_HID, CFG_TUD_HID_EP_BUFSIZE, 5),
};

uint8_t desc_other_speed_config[CONFIG_TOTAL_LEN];

tusb_desc_device_qualifier_t const desc_device_qualifier =
    {
        .bLength = sizeof(tusb_desc_device_qualifier_t),
        .bDescriptorType = TUSB_DESC_DEVICE_QUALIFIER,
        .bcdUSB = USB_BCD,

        .bDeviceClass = 0x00,
        .bDeviceSubClass = 0x00,
        .bDeviceProtocol = 0x00,

        .bMaxPacketSize0 = CFG_TUD_ENDPOINT0_SIZE,
        .bNumConfigurations = 0x01,
        .bReserved = 0x00};

uint8_t const *tud_descriptor_device_qualifier_cb(void)
{
    return (uint8_t const *)&desc_device_qualifier;
}

uint8_t const *tud_descriptor_other_speed_configuration_cb(uint8_t index)
{
    (void)index; // for multiple configurations

    // other speed config is basically configuration with type = OTHER_SPEED_CONFIG
    memcpy(desc_other_speed_config, desc_configuration, CONFIG_TOTAL_LEN);
    desc_other_speed_config[1] = TUSB_DESC_OTHER_SPEED_CONFIG;

    // this code use the same configuration for both high and full speed mode
    return desc_other_speed_config;
}

uint8_t const *tud_descriptor_configuration_cb(uint8_t index)
{
    (void)index; // for multiple configurations

    // This example use the same configuration for both high and full speed mode
    return desc_configuration;
}

static const size_t DESCRIPTOR_SIZE = 32;
static uint16_t _desc_str[DESCRIPTOR_SIZE];

uint16_t const *tud_descriptor_string_cb(uint8_t index, uint16_t lang_id)
{
    (void)lang_id;

    auto send_report = [](char const *const str)
    {
        const size_t size = strnlen(str, DESCRIPTOR_SIZE - 1);
        // Convert ASCII string into UTF-16
        for (uint8_t i = 0; i < size; i++)
        {
            _desc_str[1 + i] = str[i];
        }
        // first byte is length (including header), second byte is string type
        _desc_str[0] = (TUSB_DESC_STRING << 8) | (2 * size + 2);
    };

    switch (index)
    {
    case 0:
    {
        // supported language is English (0x0409)
        const char language[] = {0x09, 0x04, 0x00};
        send_report(language);
        break;
    }
    case 1:
        // Manufacturer
        send_report(identity::hardware::PLATFORM);
        break;
    case 2:
        // Product
        send_report(identity::firmware::PRODUCT);
        break;
    case 3:
    {
        // Serials, should use chip ID
        char serial[registry::parameter::serial_number::SIZE * 2 + 1];
        for (size_t i = 0; i < registry::parameter::serial_number::SIZE; ++i)
        {
            sprintf(&serial[i * 2], "%02x", registry::parameter::serial_number::g_register.value[i]);
        }
        serial[registry::parameter::serial_number::SIZE * 2] = 0;
        send_report(serial);
        break;
    }
    default:

        return NULL;
    }

    return _desc_str;
}

void tud_mount_cb(void)
{
    engine::mount();
}

void tud_umount_cb(void)
{
    engine::unmount();
}

void tud_suspend_cb(bool remote_wakeup_en)
{
    engine::suspend(remote_wakeup_en);
}

void tud_resume_cb(void)
{
    engine::resume();
}

void tud_hid_report_complete_cb(uint8_t instance, uint8_t const *report, uint16_t len)
{
    (void)instance;
    (void)len;

#if defined(PRINT_EXTENDED_OUTPUT)
    printf("tud_hid_report_complete_cb\n");
    for (int i = 0; i < len; ++i)
    {
        printf("0x%x\n", report[i]);
    }
    printf("\n");
#endif
}

void tud_hid_set_report_cb(uint8_t instance,
                           uint8_t _report_id,
                           hid_report_type_t report_type,
                           uint8_t const *buffer,
                           uint16_t bufsize)
{
    (void)instance;

    if (bufsize < 1)
        return;

    if (report_type == HID_REPORT_TYPE_FEATURE)
    {
#if defined(PRINT_EXTENDED_OUTPUT)
        printf("###### HID_REPORT_TYPE_FEATURE\n");
#endif
    }
    else if (report_type == HID_REPORT_TYPE_OUTPUT)
    {
#if defined(PRINT_EXTENDED_OUTPUT)
        printf("###### HID_REPORT_TYPE_OUTPUT\n");
#endif
        const_chunk_t chunk{.space = buffer, .size = bufsize};
        engine::hid::set_report_handler(_report_id, chunk);
    }
    else if (HID_REPORT_TYPE_INPUT)
    {
#if defined(PRINT_EXTENDED_OUTPUT)
        printf("###### HID_REPORT_TYPE_INPUT\n");
#endif
    }
    else if (HID_REPORT_TYPE_INVALID)
    {
#if defined(PRINT_EXTENDED_OUTPUT)
        printf("###### HID_REPORT_TYPE_INVALID\n");
#endif
    }
    else
    {
#if defined(PRINT_EXTENDED_OUTPUT)
        printf("###### unknown report type\n");
#endif
    }

#if defined(PRINT_EXTENDED_OUTPUT)
    printf("tud_hid_set_report_cb\n");

    printf("report_id 0x%x\n", _report_id);
    printf("report_type 0x%x\n", report_type);
    for (int i = 0; i < bufsize; ++i)
    {
        printf("0x%x\n", buffer[i]);
    }
    printf("\n");
#endif
}

uint16_t tud_hid_get_report_cb(uint8_t instance,
                               uint8_t report_id,
                               hid_report_type_t report_type,
                               uint8_t *buffer,
                               uint16_t bufsize)
{
    (void)instance;

    if (report_type == HID_REPORT_TYPE_FEATURE)
    {
#if defined(PRINT_EXTENDED_OUTPUT)
        printf("##### HID_REPORT_TYPE_FEATURE\n");
#endif
        chunk_t chunk{.space = buffer, .size = bufsize};
        engine::hid::get_report_handler(report_id, chunk);
    }
    else if (report_type == HID_REPORT_TYPE_INPUT)
    {
#if defined(PRINT_EXTENDED_OUTPUT)
        printf("##### HID_REPORT_TYPE_INPUT\n");
#endif
    }
    else if (report_type == HID_REPORT_TYPE_OUTPUT)
    {
#if defined(PRINT_EXTENDED_OUTPUT)
        printf("##### HID_REPORT_TYPE_OUTPUT\n");
#endif
    }
    else
    {
#if defined(PRINT_EXTENDED_OUTPUT)
        printf("###### unknown report type\n");
#endif
    }

#if defined(PRINT_EXTENDED_OUTPUT)
    printf("tud_hid_get_report_cb\n");

    printf("report_id 0x%x\n", report_id);
    printf("report_type 0x%x\n", report_type);
    for (int i = 0; i < bufsize; ++i)
    {
        printf("0x%x\n", buffer[i]);
    }
    printf("\n");
#endif

    return bufsize;
}

namespace platform::usb
{
    extern void sent_keycode(const uint8_t _modifier, const uint8_t _code)
    {
        uint8_t keycode[6] = {0};
        keycode[0] = _code;

        tud_hid_keyboard_report(static_cast<uint8_t>(platform::usb::COMMAND::KEYBOARD), _modifier, keycode);
    }

    extern void sent_keycode()
    {
        tud_hid_keyboard_report(static_cast<uint8_t>(platform::usb::COMMAND::KEYBOARD), 0, NULL);
    }
}
