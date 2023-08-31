# Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
# All rights reserved
#
# SPDX-License-Identifier: MIT

cmake_minimum_required(VERSION 3.22)

set(PICO_SDK_FETCH_FROM_GIT on)
include(build/pico_sdk_import.cmake)
include(build/pico_extras_import_optional.cmake)

project(varikey
VERSION 1.0.0.0
DESCRIPTION "Custom composed HID device"
LANGUAGES C CXX ASM)

set(HARDWARE_NUMBER 0)
set(HARDWARE_VARIANT 1)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_compile_options(-Wall
-Wno-format # int != int32_t as far as the compiler is concerned because gcc has int32_t as long int
-Wno-unused-function # we have some for the docs that aren't called
-Wno-maybe-uninitialized
)

configure_file(${PROJECT_SOURCE_DIR}/build/revision.h.in ${PROJECT_SOURCE_DIR}/src/revision.h @ONLY)

add_executable(${PROJECT_NAME})

pico_generate_pio_header(${PROJECT_NAME} "${PROJECT_SOURCE_DIR}/src/engine/platform/ws2812.pio")

if(NOT EXISTS "${PROJECT_SOURCE_DIR}/src/build_number.h")
        execute_process(
                COMMAND ${CMAKE_COMMAND} -P "${PROJECT_SOURCE_DIR}/build/build_number_inc.cmake"
                WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/build/"
        )
else()
        add_custom_command(        
                TARGET ${PROJECT_NAME}
                COMMAND ${CMAKE_COMMAND} -P "${PROJECT_SOURCE_DIR}/build/build_number_inc.cmake"
                WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/build/"
        )
endif()

target_sources(${PROJECT_NAME} PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/src/composed_hid.c
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/display/fonts.c
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/display/image_frame.c
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/display/image_gmc.c
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/display/image_heart.c
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/display/images.c
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/display/resources/font_big.c
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/display/resources/font_huge.c
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/display/resources/font_normal.c
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/display/resources/font_small.c
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/display/resources/font_symbol.c
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/display/resources/image_add_circle_16.c
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/display/resources/image_add_circle_24.c
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/display/resources/image_add_circle_32.c
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/display/resources/image_add_circle_8.c
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/display/resources/image_add_square_16.c
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/display/resources/image_add_square_24.c
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/display/resources/image_add_square_32.c
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/display/resources/image_add_square_8.c
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/engine.c
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/hci/commander/cmd_control.c
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/hci/commander/cmd_event_trigger.c
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/hci/commander/cmd_macro.c
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/hci/commander/cmd_param.c
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/hci/commander/cmd_target.c
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/hci/commander/commander.c
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/hci/commander/control/cmd_control_reset_msg.c
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/hci/commander/control/cmd_control_status_msg.c
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/hci/commander/control/cmd_control_temperature_msg.c
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/hci/commander/control/cmd_hci_status_msg.c
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/hci/commander/event/cmd_event_msg.c
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/hci/commander/macro/cmd_macro_clean_msg.c
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/hci/commander/macro/cmd_macro_key_msg.c
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/hci/commander/macro/cmd_macro_load_msg.c
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/hci/commander/macro/cmd_macro_load.c
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/hci/commander/macro/cmd_macro_store_msg.c
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/hci/commander/macro/cmd_macro_store.c
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/hci/commander/param/cmd_param_firmware_msg.c
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/hci/commander/param/cmd_param_hardware_msg.c
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/hci/commander/param/cmd_param_identity_msg.c
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/hci/commander/param/cmd_param_param_msg.c
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/hci/commander/target/cmd_target_boot_msg.c
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/hci/commander/target/cmd_target_power_msg.c
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/hci/commander/target/cmd_target_reset_msg.c
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/hci/serial/serial_frame.c
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/hci/serial/serial_msg.c
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/hci/serial/serial.c
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/hci/serial/usart.c
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/keyboard/event/hil_event_queue.c
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/keyboard/keyboard.c
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/keyboard/usb_descriptors.c
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/platform/adp5585.c
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/platform/backlight.c
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/platform/display.c
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/platform/keypad.c
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/platform/platform.c
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/platform/ssd1306.c
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/platform/ws2812.c
        ${CMAKE_CURRENT_LIST_DIR}/src/pulp/bytering.c
        ${CMAKE_CURRENT_LIST_DIR}/src/pulp/checksum.c
        ${CMAKE_CURRENT_LIST_DIR}/src/pulp/random.c
        ${CMAKE_CURRENT_LIST_DIR}/src/pulp/temperature.c
        ${CMAKE_CURRENT_LIST_DIR}/src/pulp/ticker.c
        ${CMAKE_CURRENT_LIST_DIR}/src/pulp/timestamp.c
        ${CMAKE_CURRENT_LIST_DIR}/src/pulp/types.c
        ${CMAKE_CURRENT_LIST_DIR}/src/registry/param_backlight.c
        ${CMAKE_CURRENT_LIST_DIR}/src/registry/param_display.c
        ${CMAKE_CURRENT_LIST_DIR}/src/registry/param_features.c
        ${CMAKE_CURRENT_LIST_DIR}/src/registry/param_key.c
        ${CMAKE_CURRENT_LIST_DIR}/src/registry/param_maintainer.c
        ${CMAKE_CURRENT_LIST_DIR}/src/registry/param_position.c
        ${CMAKE_CURRENT_LIST_DIR}/src/registry/param_serial_number.c
        ${CMAKE_CURRENT_LIST_DIR}/src/registry/param_user.c
        ${CMAKE_CURRENT_LIST_DIR}/src/registry/parameter.c
        ${CMAKE_CURRENT_LIST_DIR}/src/registry/registry_interface.c
        ${CMAKE_CURRENT_LIST_DIR}/src/registry/registry.c
        ${CMAKE_CURRENT_LIST_DIR}/src/storage/storage_interface.c
        ${CMAKE_CURRENT_LIST_DIR}/src/storage/storage_queue.c
)

target_include_directories(${PROJECT_NAME} PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/
        ${CMAKE_CURRENT_LIST_DIR}/build/
        ${CMAKE_CURRENT_LIST_DIR}/src/
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/display/
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/display/resources/
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/hci/
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/hci/commander/
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/hci/commander/control/
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/hci/commander/event/
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/hci/commander/macro/
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/hci/commander/param/
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/hci/commander/target/
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/hci/serial/
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/keyboard/
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/keyboard/event/
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/platform/
        ${CMAKE_CURRENT_LIST_DIR}/src/pulp/
        ${CMAKE_CURRENT_LIST_DIR}/src/registry/
        ${CMAKE_CURRENT_LIST_DIR}/src/storage/
)

# Uncomment this line to enable fix for Errata RP2040-E5 (the fix requires use of GPIO 15)
# target_compile_definitions(dev_hid_composite PUBLIC PICO_RP2040_USB_DEVICE_ENUMERATION_FIX=1)
target_link_libraries(${PROJECT_NAME} PUBLIC
        hardware_adc
        hardware_flash
        hardware_i2c
        hardware_spi
        hardware_sync
        hardware_pio
        hardware_exception
        pico_stdlib
        tinyusb_board
        tinyusb_device
)

# add url via pico_set_program_url
# example_auto_set_url(${PROJECT_NAME})

# pico_enable_stdio_usb(${PROJECT_NAME} 0)
pico_enable_stdio_uart(${PROJECT_NAME} 1)
pico_add_extra_outputs(${PROJECT_NAME})
