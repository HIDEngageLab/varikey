# Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
# SPDX-License-Identifier: MIT

cmake_minimum_required(VERSION 3.22)

set(SCRIPTS_DIR "${CMAKE_CURRENT_LIST_DIR}/.scripts")

set(PICO_SDK_FETCH_FROM_GIT on)
include(${SCRIPTS_DIR}/pico_sdk_import.cmake)
include(${SCRIPTS_DIR}/pico_extras_import_optional.cmake)
include(${SCRIPTS_DIR}/cpp_check.cmake)

project(varikey
    VERSION 1.1.0.2
    DESCRIPTION "Custom composed keypad HID device"
    LANGUAGES C CXX ASM
)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

set(CMAKE_BUILD_TYPE Debug)

pico_sdk_init()

add_compile_options(
    -Wall
    -Wno-format # int != int32_t as far as the compiler is concerned because gcc has int32_t as long int
    -Wno-unused-function # we have some for the docs that aren't called
    #-Wno-unused-parameter # we have some for the docs that aren't called
    #-Wno-unused-variable # we have some for the docs that aren't called
    #-Wno-unused-but-set-variable # we have some for the docs that aren't called
    #-Wno-maybe-uninitialized
    #-Wextra
    -Waddress
    #-Wpedantic
    #-fpack-struct
)

if (NOT HARDWARE_PLATFORM)
    message(WARNING "platform is not defined, default is VARIKEY")
    # set default hardware
    # evailable platfroms are: VARIKEY, GMCI  
    set(HARDWARE_PLATFORM "VARIKEY")
endif()
if (${HARDWARE_PLATFORM} STREQUAL "GMCI")
    set(HARDWARE_IDENTIFIER 2)
    set(HARDWARE_NUMBER 1)
    set(HARDWARE_VARIANT 0)
elseif (${HARDWARE_PLATFORM} STREQUAL "VARIKEY")
    set(HARDWARE_IDENTIFIER 1)
    set(HARDWARE_NUMBER 1)
    set(HARDWARE_VARIANT 0)
elseif (${HARDWARE_PLATFORM} STREQUAL "VARIKEY_15SBLA_PROTO")
    set(HARDWARE_IDENTIFIER 3)
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
elseif (${FIRMWARE_PRODUCT} STREQUAL "KEYPAD_15SBLA")
    set(FIRMWARE_IDENTIFIER 3)
    set(FIRMWARE_VENDOR 0xABCD)
else()
    set(FIRMWARE_IDENTIFIER 1)
    set(FIRMWARE_VENDOR 0xBEEF)
endif()
message(STATUS "product is ${FIRMWARE_PRODUCT} (internal ID:${FIRMWARE_IDENTIFIER} REV:${PROJECT_VERSION})")

set(EXECUTABLE_NAME "${PROJECT_NAME}_${FIRMWARE_PRODUCT}_${HARDWARE_PLATFORM}_${HARDWARE_NUMBER}_${HARDWARE_VARIANT}")
string(TOLOWER ${EXECUTABLE_NAME} EXECUTABLE_NAME)

set(VARIKEY_LIBRARY_NAME ${CMAKE_PROJECT_NAME}_library)
SET(VARIKEY_LIBRARY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/${VARIKEY_LIBRARY_NAME}")
string(TOLOWER ${VARIKEY_LIBRARY_NAME} VARIKEY_LIBRARY_NAME)

set(GIT_HASH_SIZE 8)
execute_process (COMMAND bash -c "git rev-parse --short=${GIT_HASH_SIZE} HEAD | tr -d '\n'" OUTPUT_VARIABLE GIT_HASH)
configure_file(${SCRIPTS_DIR}/revision.h.in ${VARIKEY_LIBRARY_DIR}/revision.h @ONLY)

include(${SCRIPTS_DIR}/graffiti.cmake)
  
add_executable(${EXECUTABLE_NAME}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/firmware.cpp)

add_dependencies(${EXECUTABLE_NAME} ascii_art)

if(NOT EXISTS "${VARIKEY_LIBRARY_DIR}/build_number.h")
    execute_process(
        COMMAND ${CMAKE_COMMAND} -P "${SCRIPTS_DIR}/build_number_inc.cmake"
        WORKING_DIRECTORY "${SCRIPTS_DIR}/"
    )
else()
    IF(CMAKE_BUILD_TYPE MATCHES "Release")
        add_custom_command(        
            TARGET ${EXECUTABLE_NAME}
            COMMAND ${CMAKE_COMMAND} -P "${SCRIPTS_DIR}/build_number_inc.cmake"
            WORKING_DIRECTORY "${SCRIPTS_DIR}/"
        )
    ENDIF(CMAKE_BUILD_TYPE MATCHES "Release")
endif()

add_subdirectory(${VARIKEY_LIBRARY_NAME})

# Uncomment this line to enable fix for Errata RP2040-E5 (the fix requires use of GPIO 15)
# target_compile_definitions(dev_hid_composite PUBLIC PICO_RP2040_USB_DEVICE_ENUMERATION_FIX=1)
target_link_libraries(${EXECUTABLE_NAME} PUBLIC
    ${VARIKEY_LIBRARY_NAME}
)

# add url via pico_set_program_url
# example_auto_set_url(${PROJECT_NAME})

# pico_enable_stdio_usb(${PROJECT_NAME} 0)
pico_enable_stdio_uart(${EXECUTABLE_NAME} 1)
pico_add_extra_outputs(${EXECUTABLE_NAME})
