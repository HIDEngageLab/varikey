# Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
# SPDX-License-Identifier: MIT

cmake_minimum_required(VERSION 3.22)

unset(ENV{PICO_SDK_PATH})
set(PICO_SDK_FETCH_FROM_GIT ON)

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
#-fpack-struct
-g
-O0
)

# platform variants management
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

# product variants management
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

set(EXECUTABLE_NAME "${PROJECT_NAME}_${FIRMWARE_PRODUCT}_${HARDWARE_PLATFORM}_${HARDWARE_NUMBER}_${HARDWARE_VARIANT}")
string(TOLOWER ${EXECUTABLE_NAME} EXECUTABLE_NAME)

add_subdirectory(${CMAKE_SOURCE_DIR}/src/pulp)
add_subdirectory(${CMAKE_SOURCE_DIR}/src/platform)
add_subdirectory(${CMAKE_SOURCE_DIR}/src/registry)
add_subdirectory(${CMAKE_SOURCE_DIR}/src/engine)
add_executable(${EXECUTABLE_NAME})

set(BUILD_MACROS_DIRECTORY "${PROJECT_SOURCE_DIR}/build")
set(IDENTITY_DIRECTORY "${PROJECT_SOURCE_DIR}/src/engine/identity")

set(GIT_HASH_SIZE 8)
execute_process (COMMAND bash -c "git rev-parse --short=${GIT_HASH_SIZE} HEAD | tr -d '\n'" OUTPUT_VARIABLE GIT_HASH)
configure_file(${BUILD_MACROS_DIRECTORY}/revision.h.in ${IDENTITY_DIRECTORY}/revision.h @ONLY)

if(NOT EXISTS "${IDENTITY_DIRECTORY}/build_number.h")
        execute_process(
                COMMAND ${CMAKE_COMMAND} -P "${BUILD_MACROS_DIRECTORY}/build_number_inc.cmake"
                WORKING_DIRECTORY "${BUILD_MACROS_DIRECTORY}/"
        )
else()
        IF(CMAKE_BUILD_TYPE MATCHES "Release")
                add_custom_command(        
                        TARGET ${EXECUTABLE_NAME}
                        COMMAND ${CMAKE_COMMAND} -P "${BUILD_MACROS_DIRECTORY}/build_number_inc.cmake"
                        WORKING_DIRECTORY "${BUILD_MACROS_DIRECTORY}/"
                        )
        ENDIF(CMAKE_BUILD_TYPE MATCHES "Release")
endif()

include("${CMAKE_SOURCE_DIR}/build/graffiti.cmake")
add_dependencies(${EXECUTABLE_NAME} ascii_art)

target_sources(${EXECUTABLE_NAME} PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/src/varikey.cpp
    )

target_include_directories(${EXECUTABLE_NAME} PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/build/
        ${CMAKE_CURRENT_LIST_DIR}/src/
)

# Uncomment this line to enable fix for Errata RP2040-E5 (the fix requires use of GPIO 15)
# target_compile_definitions(dev_hid_composite PUBLIC PICO_RP2040_USB_DEVICE_ENUMERATION_FIX=1)
target_link_libraries(${EXECUTABLE_NAME} PUBLIC
        pico_stdlib
        pulp
        platform
        registry
        engine
)

# add url via pico_set_program_url
# example_auto_set_url(${PROJECT_NAME})

# pico_enable_stdio_usb(${PROJECT_NAME} 0)
pico_enable_stdio_uart(${EXECUTABLE_NAME} 1)
pico_add_extra_outputs(${EXECUTABLE_NAME})
