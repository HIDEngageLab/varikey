# Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
# SPDX-License-Identifier: MIT

cmake_minimum_required(VERSION 3.22)

set(PICO_SDK_FETCH_FROM_GIT on)
include(build/pico_sdk_import.cmake)
include(build/pico_extras_import_optional.cmake)
include(build/cppcheck.cmake)

project(varikey
VERSION 1.1.0.2
DESCRIPTION "Custom composed keypad HID device"
LANGUAGES C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_compile_options(-Wall
-Wno-format # int != int32_t as far as the compiler is concerned because gcc has int32_t as long int
-Wno-unused-function # we have some for the docs that aren't called
-Wno-maybe-uninitialized
-Waddress
-g
-O0
)

if (NOT HARDWARE_PLATFORM)
        message(WARNING "platform is not defined, default is VARIKEY")
        # set default hardware
        # evailable platfroms are: VARIKEY, GOSSENMETRAWATT  
        set(HARDWARE_PLATFORM "VARIKEY")
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
message(STATUS "platform is ${HARDWARE_PLATFORM} (internal ID:${HARDWARE_IDENTIFIER} NUM:${HARDWARE_NUMBER} VAR:${HARDWARE_VARIANT})")

if (NOT FIRMWARE_PRODUCT)
        message(WARNING "product is not defined, default is KEYPAD_DEMO")
        # set default device name
        # available devices are: KEYPAD_DEMO, KEYPAD_10BWDB
        set(FIRMWARE_PRODUCT "KEYPAD_DEMO")
endif()
if (${FIRMWARE_PRODUCT} STREQUAL "KEYPAD_10BWDB")
        set(FIRMWARE_IDENTIFIER 2)
        set(FIRMWARE_VENDOR 0xCAFE)
elseif (${FIRMWARE_PRODUCT} STREQUAL "KEYPAD_DEMO")
        set(FIRMWARE_IDENTIFIER 1)
        set(FIRMWARE_VENDOR 0xBEEF)
else()
        set(FIRMWARE_IDENTIFIER 1)
        set(FIRMWARE_VENDOR 0xBEEF)
endif()
message(STATUS "product is ${FIRMWARE_PRODUCT} (internal ID:${FIRMWARE_IDENTIFIER} REV:${PROJECT_VERSION})")

execute_process (COMMAND bash -c "git rev-parse --short=8 HEAD | tr -d '\n'" OUTPUT_VARIABLE GIT_HASH)
configure_file(${PROJECT_SOURCE_DIR}/build/revision.h.in ${PROJECT_SOURCE_DIR}/src/revision.h @ONLY)

set(EXECUTABLE_NAME "${PROJECT_NAME}_${FIRMWARE_PRODUCT}_${HARDWARE_PLATFORM}_${HARDWARE_NUMBER}_${HARDWARE_VARIANT}")
string(TOLOWER ${EXECUTABLE_NAME} EXECUTABLE_NAME)

include("${CMAKE_SOURCE_DIR}/build/graffiti.cmake")
  
add_executable(${EXECUTABLE_NAME})

add_dependencies(${EXECUTABLE_NAME} ascii_art)

pico_generate_pio_header(${EXECUTABLE_NAME} "${PROJECT_SOURCE_DIR}/src/platform/hardware/backlight/ws2812.pio")

if(NOT EXISTS "${PROJECT_SOURCE_DIR}/src/build_number.h")
        execute_process(
                COMMAND ${CMAKE_COMMAND} -P "${PROJECT_SOURCE_DIR}/build/build_number_inc.cmake"
                WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/build/"
        )
else()
        IF(CMAKE_BUILD_TYPE MATCHES "Release")
                add_custom_command(        
                        TARGET ${EXECUTABLE_NAME}
                        COMMAND ${CMAKE_COMMAND} -P "${PROJECT_SOURCE_DIR}/build/build_number_inc.cmake"
                        WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/build/"
                        )
        ENDIF(CMAKE_BUILD_TYPE MATCHES "Release")
endif()


target_sources(${EXECUTABLE_NAME} PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/backlight/backlight3.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/display/display.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/display/resources/display_font.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/display/resources/display_image.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/display/resources/fonts/font_big.c
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/display/resources/fonts/font_huge.c
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/display/resources/fonts/font_normal.c
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/display/resources/fonts/font_small.c
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/display/resources/fonts/font_symbol.c
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/display/resources/images/image_add_circle_16.c
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/display/resources/images/image_add_circle_24.c
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/display/resources/images/image_add_circle_32.c
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/display/resources/images/image_add_circle_8.c
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/display/resources/images/image_add_square_16.c
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/display/resources/images/image_add_square_24.c
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/display/resources/images/image_add_square_32.c
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/display/resources/images/image_add_square_8.c
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/display/resources/images/image_frame.c
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/display/resources/images/image_gmc.c
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/display/resources/images/image_heart.c
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/display/resources/images/image_varikey.c
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/engine_event_handler.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/engine.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/interface/hci/commander/cmd_control.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/interface/hci/commander/cmd_feature.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/interface/hci/commander/cmd_setting.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/interface/hci/commander/commander.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/interface/hci/commander/control/cmd_gadget_msg.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/interface/hci/commander/control/cmd_hash_msg.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/interface/hci/commander/control/cmd_protocol_msg.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/interface/hci/commander/control/cmd_reset_msg.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/interface/hci/commander/control/cmd_temperature_msg.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/interface/hci/commander/feature/cmd_backlight_msg.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/interface/hci/commander/feature/cmd_display_msg.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/interface/hci/commander/feature/cmd_gpio_msg.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/interface/hci/commander/feature/cmd_keypad_msg.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/interface/hci/commander/setting/cmd_identity_msg.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/interface/hci/commander/setting/cmd_parameter_msg.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/interface/hci/serial/serial_frame.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/interface/hci/serial/serial_msg.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/interface/hci/serial/serial.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/interface/hid/hid_handler.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/interface/hid/hid_report.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/interface/payload/payload_backlight.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/keypad/keypad_keycode_10bwdb.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/keypad/keypad_keycode_varikey.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/keypad/keypad_keycode.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/keypad/keypad.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/platform/board/board_keypad.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/platform/board/board.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/platform/hardware/backlight/backlight_ws2812.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/platform/hardware/backlight/ws2812.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/platform/hardware/display/display_oled_128x32.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/platform/hardware/display/ssd1306.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/platform/hardware/keymatrix/adp5585.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/platform/hardware/keymatrix/keymatrix_adp5585_handler_gossenmetrawatt.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/platform/hardware/keymatrix/keymatrix_adp5585_handler_varikey.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/platform/hardware/keymatrix/keymatrix_adp5585.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/platform/hardware/soc/rp2040/rp2040_gpio.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/platform/hardware/soc/rp2040/rp2040_soc.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/platform/hardware/soc/rp2040/rp2040_stopwatch.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/platform/hardware/soc/rp2040/rp2040_temperature.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/platform/hardware/soc/rp2040/rp2040_ticker.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/platform/hardware/soc/rp2040/rp2040_watchdog.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/platform/hardware/uart/usart.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/platform/hardware/usb/usb_descriptors.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/platform/hardware/usb/usb_device.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/pulp/bytering.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/pulp/checksum.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/pulp/macros.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/pulp/random.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/registry/param_backlight.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/registry/param_display.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/registry/param_features.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/registry/param_keypad.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/registry/param_maintainer.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/registry/param_mapping.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/registry/param_position.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/registry/param_serial_number.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/registry/param_user.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/registry/parameter.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/registry/registry_interface.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/registry/registry.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/varikey.cpp
)

target_include_directories(${EXECUTABLE_NAME} PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/
        ${CMAKE_CURRENT_LIST_DIR}/build/
        ${CMAKE_CURRENT_LIST_DIR}/src/
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/backlight/
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/display/
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/display/resources/
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/display/resources/fonts
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/display/resources/images
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/event/
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/interface/
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/interface/hci/
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/interface/hci/commander/
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/interface/hci/commander/control/
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/interface/hci/commander/feature/
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/interface/hci/commander/setting/
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/interface/hci/serial/
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/interface/hid/
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/interface/payload/
        ${CMAKE_CURRENT_LIST_DIR}/src/engine/keypad/
        ${CMAKE_CURRENT_LIST_DIR}/src/identity/
        ${CMAKE_CURRENT_LIST_DIR}/src/platform/
        ${CMAKE_CURRENT_LIST_DIR}/src/platform/board/
        ${CMAKE_CURRENT_LIST_DIR}/src/platform/hardware/
        ${CMAKE_CURRENT_LIST_DIR}/src/platform/hardware/backlight/
        ${CMAKE_CURRENT_LIST_DIR}/src/platform/hardware/button/
        ${CMAKE_CURRENT_LIST_DIR}/src/platform/hardware/display/
        ${CMAKE_CURRENT_LIST_DIR}/src/platform/hardware/keymatrix/
        ${CMAKE_CURRENT_LIST_DIR}/src/platform/hardware/soc/
        ${CMAKE_CURRENT_LIST_DIR}/src/platform/hardware/soc/rp2040/
        ${CMAKE_CURRENT_LIST_DIR}/src/platform/hardware/uart/
        ${CMAKE_CURRENT_LIST_DIR}/src/platform/hardware/usb/
        ${CMAKE_CURRENT_LIST_DIR}/src/pulp/
        ${CMAKE_CURRENT_LIST_DIR}/src/registry/
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
