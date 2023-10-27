# Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
# SPDX-License-Identifier: MIT

cmake_minimum_required(VERSION 3.22)

set(PICO_SDK_FETCH_FROM_GIT on)
include(build/pico_sdk_import.cmake)
include(build/pico_extras_import_optional.cmake)

project(varikey
VERSION 1.0.0.0
DESCRIPTION "Custom composed HID device"
LANGUAGES C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

pico_sdk_init()

add_compile_options(-Wall
-Wno-format # int != int32_t as far as the compiler is concerned because gcc has int32_t as long int
-Wno-unused-function # we have some for the docs that aren't called
-Wno-maybe-uninitialized
)

if (NOT HARDWARE_PLATFORM)
        message("platform is not defined, default is VARIKEY")
        set(HARDWARE_PLATFORM "VARIKEY")
        #set(HARDWARE_PLATFORM "GOSSENMETRAWATT")
endif()
if (${HARDWARE_PLATFORM} STREQUAL "GOSSENMETRAWATT")
        set(HARDWARE_IDENTIFIER 2)
        set(HARDWARE_NUMBER 1)
        set(HARDWARE_VARIANT 0)
elseif (${HARDWARE_PLATFORM} STREQUAL "VARIKEY")
        set(HARDWARE_IDENTIFIER 1)
        set(HARDWARE_NUMBER 1)
        set(HARDWARE_VARIANT 0)
else()
        set(HARDWARE_IDENTIFIER 1)
        set(HARDWARE_NUMBER 1)
        set(HARDWARE_VARIANT 0)
endif()
message("hardware is ${HARDWARE_PLATFORM} (internal ID:${HARDWARE_IDENTIFIER} NUM:${HARDWARE_NUMBER} VAR:${HARDWARE_VARIANT})")

if (NOT FIRMWARE_PRODUCT)
        message("product is not defined, default is KEYPAD_10_BOTTONS_WHEEL_DISPLAY_BACKLIGHT_0100")
        set(FIRMWARE_PRODUCT "KEYPAD_10BWDB")
        #set(FIRMWARE_PRODUCT "KEYPAD_DEMO")
endif()
if (${FIRMWARE_PRODUCT} STREQUAL "KEYPAD_10BWDB")
        set(FIRMWARE_IDENTIFIER 2)
elseif (${FIRMWARE_PRODUCT} STREQUAL "KEYPAD_DEMO")
        set(FIRMWARE_IDENTIFIER 1)
else()
        set(FIRMWARE_IDENTIFIER 1)
endif()
message("product is ${FIRMWARE_PRODUCT} (internal ID:${FIRMWARE_IDENTIFIER} REV:${PROJECT_VERSION})")


configure_file(${PROJECT_SOURCE_DIR}/build/revision.h.in ${PROJECT_SOURCE_DIR}/src/revision.h @ONLY)

set(EXECUTABLE_NAME "${PROJECT_NAME}_${FIRMWARE_PRODUCT}_${HARDWARE_PLATFORM}_${HARDWARE_NUMBER}${HARDWARE_VARIANT}")

add_executable(${EXECUTABLE_NAME})

pico_generate_pio_header(${EXECUTABLE_NAME} "${PROJECT_SOURCE_DIR}/src/platform/hardware/backlight/ws2812.pio")

if(NOT EXISTS "${PROJECT_SOURCE_DIR}/src/build_number.h")
        execute_process(
                COMMAND ${CMAKE_COMMAND} -P "${PROJECT_SOURCE_DIR}/build/build_number_inc.cmake"
                WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/build/"
        )
else()
        add_custom_command(        
                TARGET ${EXECUTABLE_NAME}
                COMMAND ${CMAKE_COMMAND} -P "${PROJECT_SOURCE_DIR}/build/build_number_inc.cmake"
                WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/build/"
        )
endif()

target_sources(${EXECUTABLE_NAME} PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/src/composed_hid.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/backlight/backlight3.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/engine.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/hci/commander/cmd_control.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/hci/commander/cmd_event_trigger.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/hci/commander/cmd_macro.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/hci/commander/cmd_param.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/hci/commander/cmd_target.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/hci/commander/commander.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/hci/commander/control/cmd_control_reset_msg.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/hci/commander/control/cmd_control_status_msg.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/hci/commander/control/cmd_control_temperature_msg.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/hci/commander/control/cmd_hci_status_msg.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/hci/commander/event/cmd_event_msg.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/hci/commander/macro/cmd_macro_clean_msg.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/hci/commander/macro/cmd_macro_key_msg.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/hci/commander/macro/cmd_macro_load_msg.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/hci/commander/macro/cmd_macro_load.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/hci/commander/macro/cmd_macro_store_msg.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/hci/commander/macro/cmd_macro_store.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/hci/commander/param/cmd_param_firmware_msg.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/hci/commander/param/cmd_param_hardware_msg.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/hci/commander/param/cmd_param_identity_msg.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/hci/commander/param/cmd_param_param_msg.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/hci/commander/target/cmd_target_boot_msg.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/hci/commander/target/cmd_target_power_msg.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/hci/commander/target/cmd_target_reset_msg.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/hci/event/hci_event_queue.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/hci/serial/serial_frame.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/hci/serial/serial_msg.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/hci/serial/serial.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/hci/serial/usart.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/keyboard/keypad.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/platform/board/board_gossenmetrawatt_1_0.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/platform/board/board_keypad.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/platform/board/board_varikey_1_0.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/platform/board/board.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/platform/hardware/backlight/backlight_ws2812.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/platform/hardware/backlight/ws2812.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/platform/hardware/display/display_oled_128x32.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/platform/hardware/display/display.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/platform/hardware/display/resources/font_big.c
        ${CMAKE_CURRENT_LIST_DIR}/src/platform/hardware/display/resources/font_huge.c
        ${CMAKE_CURRENT_LIST_DIR}/src/platform/hardware/display/resources/font_normal.c
        ${CMAKE_CURRENT_LIST_DIR}/src/platform/hardware/display/resources/font_small.c
        ${CMAKE_CURRENT_LIST_DIR}/src/platform/hardware/display/resources/font_symbol.c
        ${CMAKE_CURRENT_LIST_DIR}/src/platform/hardware/display/resources/image_add_circle_16.c
        ${CMAKE_CURRENT_LIST_DIR}/src/platform/hardware/display/resources/image_add_circle_24.c
        ${CMAKE_CURRENT_LIST_DIR}/src/platform/hardware/display/resources/image_add_circle_32.c
        ${CMAKE_CURRENT_LIST_DIR}/src/platform/hardware/display/resources/image_add_circle_8.c
        ${CMAKE_CURRENT_LIST_DIR}/src/platform/hardware/display/resources/image_add_square_16.c
        ${CMAKE_CURRENT_LIST_DIR}/src/platform/hardware/display/resources/image_add_square_24.c
        ${CMAKE_CURRENT_LIST_DIR}/src/platform/hardware/display/resources/image_add_square_32.c
        ${CMAKE_CURRENT_LIST_DIR}/src/platform/hardware/display/resources/image_add_square_8.c
        ${CMAKE_CURRENT_LIST_DIR}/src/platform/hardware/display/resources/image_frame.c
        ${CMAKE_CURRENT_LIST_DIR}/src/platform/hardware/display/resources/image_gmc.c
        ${CMAKE_CURRENT_LIST_DIR}/src/platform/hardware/display/resources/image_heart.c
        ${CMAKE_CURRENT_LIST_DIR}/src/platform/hardware/display/resources/image_varikey.c
        ${CMAKE_CURRENT_LIST_DIR}/src/platform/hardware/display/ssd1306.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/platform/hardware/keypad/adp5585.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/platform/hardware/keypad/keypad_adp5585.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/platform/hardware/soc/rp2040/rp2040_soc.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/platform/hardware/soc/rp2040/rp2040_temperature.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/platform/hardware/soc/rp2040/rp2040_ticker.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/platform/hardware/soc/rp2040/rp2040_timestamp.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/platform/hardware/soc/rp2040/rp2040_watchdog.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/platform/hardware/usb/usb_descriptors.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/platform/hardware/usb/usb_device.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/pulp/bytering.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/pulp/checksum.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/pulp/macros.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/pulp/random.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/registry/param_adc.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/registry/param_backlight.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/registry/param_button.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/registry/param_display.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/registry/param_features.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/registry/param_key.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/registry/param_maintainer.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/registry/param_position.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/registry/param_serial_number.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/registry/param_user.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/registry/parameter.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/registry/registry_interface.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/registry/registry.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/storage/storage_interface.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/storage/storage_queue.cpp
)

target_include_directories(${EXECUTABLE_NAME} PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/
        ${CMAKE_CURRENT_LIST_DIR}/build/
        ${CMAKE_CURRENT_LIST_DIR}/src/
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/backlight/
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/display/
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/display/resources/
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/hci/
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/hci/commander/
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/hci/commander/control/
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/hci/commander/event/
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/hci/commander/macro/
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/hci/commander/param/
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/hci/commander/target/
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/hci/event/
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/hci/serial/
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/keyboard/
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/keyboard/event/
        ${CMAKE_CURRENT_LIST_DIR}/src/platform/
        ${CMAKE_CURRENT_LIST_DIR}/src/platform/board/
        ${CMAKE_CURRENT_LIST_DIR}/src/platform/hardware/
        ${CMAKE_CURRENT_LIST_DIR}/src/platform/hardware/backlight/
        ${CMAKE_CURRENT_LIST_DIR}/src/platform/hardware/button/
        ${CMAKE_CURRENT_LIST_DIR}/src/platform/hardware/display/
        ${CMAKE_CURRENT_LIST_DIR}/src/platform/hardware/display/resources/
        ${CMAKE_CURRENT_LIST_DIR}/src/platform/hardware/keypad/
        ${CMAKE_CURRENT_LIST_DIR}/src/platform/hardware/soc/
        ${CMAKE_CURRENT_LIST_DIR}/src/platform/hardware/soc/rp2040/
        ${CMAKE_CURRENT_LIST_DIR}/src/platform/hardware/usb/
        ${CMAKE_CURRENT_LIST_DIR}/src/pulp/
        ${CMAKE_CURRENT_LIST_DIR}/src/registry/
        ${CMAKE_CURRENT_LIST_DIR}/src/storage/
)

# Uncomment this line to enable fix for Errata RP2040-E5 (the fix requires use of GPIO 15)
# target_compile_definitions(dev_hid_composite PUBLIC PICO_RP2040_USB_DEVICE_ENUMERATION_FIX=1)
target_link_libraries(${EXECUTABLE_NAME} PUBLIC
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
pico_enable_stdio_uart(${EXECUTABLE_NAME} 1)
pico_add_extra_outputs(${EXECUTABLE_NAME})
