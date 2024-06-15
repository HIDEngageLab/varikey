# Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
# SPDX-License-Identifier: MIT

# ------------------------------------------------------------
# CMake, SDK, Conpiler and Project config
# ------------------------------------------------------------
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

add_link_options(-T ${CMAKE_CURRENT_LIST_DIR}/build/memmap_extended.ld)

if (ENABLE_UNIT_TESTING)
        message(STATUS "Unit testing enabled")
        add_compile_options(-DENABLE_UNIT_TESTS=1)
else()
        message(STATUS "Unit testing disabled")
        add_compile_options(-DENABLE_UNIT_TESTS=0)
endif()

# ------------------------------------------------------------
# Platform variants management
# ------------------------------------------------------------

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

# ------------------------------------------------------------
# Product variants management
# ------------------------------------------------------------

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

# ------------------------------------------------------------
# Source code structure
# ------------------------------------------------------------

if (ENABLE_UNIT_TESTING)
        set(EXECUTABLE_NAME "TEST_${PROJECT_NAME}_${FIRMWARE_PRODUCT}_${HARDWARE_PLATFORM}_${HARDWARE_NUMBER}_${HARDWARE_VARIANT}")
else()
        set(EXECUTABLE_NAME "${PROJECT_NAME}_${FIRMWARE_PRODUCT}_${HARDWARE_PLATFORM}_${HARDWARE_NUMBER}_${HARDWARE_VARIANT}")
endif()
string(TOLOWER ${EXECUTABLE_NAME} EXECUTABLE_NAME)

add_subdirectory(${CMAKE_SOURCE_DIR}/src/pulp)
add_subdirectory(${CMAKE_SOURCE_DIR}/src/platform)
add_subdirectory(${CMAKE_SOURCE_DIR}/src/registry)
add_subdirectory(${CMAKE_SOURCE_DIR}/src/engine)
if (ENABLE_UNIT_TESTING)
        add_subdirectory(${CMAKE_SOURCE_DIR}/src/test/unity)
        add_subdirectory(${CMAKE_SOURCE_DIR}/src/test/unit-tests)
endif()
add_executable(${EXECUTABLE_NAME})

# ------------------------------------------------------------
# Revision description generator
# ------------------------------------------------------------

set(BUILD_MACROS_DIRECTORY "${PROJECT_SOURCE_DIR}/build")
set(IDENTITY_DIRECTORY "${PROJECT_SOURCE_DIR}/src/engine/identity")

set(GIT_HASH_SIZE 8)
execute_process (COMMAND bash -c "git rev-parse --short=${GIT_HASH_SIZE} HEAD | tr -d '\n'" OUTPUT_VARIABLE GIT_HASH)
configure_file(${BUILD_MACROS_DIRECTORY}/revision.h.in ${IDENTITY_DIRECTORY}/revision.h @ONLY)

# ------------------------------------------------------------
# Build Number generator
# ------------------------------------------------------------

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

# ------------------------------------------------------------
# Nice grafiti
# ------------------------------------------------------------

include("${CMAKE_SOURCE_DIR}/build/graffiti.cmake")
add_dependencies(${EXECUTABLE_NAME} ascii_art)

# ------------------------------------------------------------
# Executable management
# ------------------------------------------------------------

if (ENABLE_UNIT_TESTING)
        target_sources(${EXECUTABLE_NAME} PUBLIC
                ${CMAKE_CURRENT_LIST_DIR}/src/test/test.cpp
        )
else()
        target_sources(${EXECUTABLE_NAME} PUBLIC
                ${CMAKE_CURRENT_LIST_DIR}/src/varikey.cpp
        )
endif()

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

if (ENABLE_UNIT_TESTING)
        target_link_libraries(${EXECUTABLE_NAME} PUBLIC
                unit_tests
        )
endif()

# add url via pico_set_program_url
# example_auto_set_url(${PROJECT_NAME})

if (ENABLE_UNIT_TESTING)
        pico_enable_stdio_usb(${EXECUTABLE_NAME} 0)
        pico_enable_stdio_uart(${EXECUTABLE_NAME} 1)
else()
        pico_enable_stdio_usb(${EXECUTABLE_NAME} 0)
        pico_enable_stdio_uart(${EXECUTABLE_NAME} 1)
endif()

pico_add_extra_outputs(${EXECUTABLE_NAME})

# ------------------------------------------------------------
# Testing
# ------------------------------------------------------------

enable_testing()

include(CTest)
list(APPEND CMAKE_CTEST_ARGUMENTS "--output-on-failure")
list(APPEND CMAKE_CTEST_ARGUMENTS "--extra-verbose")

set (PICOTOOL_TEST_SCRIPT "${PROJECT_SOURCE_DIR}/tools/test.sh")

set (passRegex "PASSED|OK")
set (failRegex "FAILED|TIMEOUT")
set_property(TEST PROPERTY PASS_REGULAR_EXPRESSION "${passRegex}")
set_property(TEST PROPERTY FAIL_REGULAR_EXPRESSION "${failRegex}")

function(do_upload_test test_name group identifier binary)
        add_test(NAME ${test_name} COMMAND ${PICOTOOL_TEST_SCRIPT} ${group} ${identifier} ${binary} WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/tools)
        set_tests_properties( ${name} PROPERTIES PASS_REGULAR_EXPRESSION "${passRegex}") 
        set_tests_properties( ${name} PROPERTIES FAIL_REGULAR_EXPRESSION "${failRegex}") 
        set_tests_properties( ${name} PROPERTIES TIMEOUT 20)
endfunction()

function(do_test test_name group identifier)
        add_test(NAME ${test_name} COMMAND ${PICOTOOL_TEST_SCRIPT} ${group} ${identifier} WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/tools)
        set_tests_properties( ${name} PROPERTIES PASS_REGULAR_EXPRESSION "${passRegex}") 
        set_tests_properties( ${name} PROPERTIES FAIL_REGULAR_EXPRESSION "${failRegex}") 
        set_tests_properties( ${name} PROPERTIES TIMEOUT 20)
endfunction()

do_upload_test(checksum_sum 0 0 "${PROJECT_SOURCE_DIR}/bin/${EXECUTABLE_NAME}.uf2")
do_test(checksum_hash 0 1)
do_test(checksum_crc 0 2)
do_test(checksum_crc_reflected 0 3)
do_test(checksum_crc_byte 0 4)
do_test(checksum_crc_post 0 5)
do_test(checksum_crc_reflected_post 0 6)
do_test(random_8 1 0)
do_test(random_11 1 1)
do_test(random_32 1 2)
do_test(random_many 1 3)

# run CTest from the command-line
# ctest --extra-verbose

# run a single test or a subset of tests
# ctest -R checksum

# exclude test or a subset of tests
# ctest -E upload
