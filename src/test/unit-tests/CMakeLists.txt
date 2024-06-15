# Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
# SPDX-License-Identifier: MIT

add_library(unit_tests STATIC) 

target_sources(unit_tests PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/test_checksum.cpp
    ${CMAKE_CURRENT_LIST_DIR}/test_random.cpp
    ${CMAKE_CURRENT_LIST_DIR}/unit_test.cpp
)

include(${CMAKE_SOURCE_DIR}/build/subdirectories.cmake)
get_subdirectories(UNIT_TESTS_SUBDIRS ${CMAKE_CURRENT_LIST_DIR})

target_include_directories(unit_tests PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
    ${UNIT_TESTS_SUBDIRS}
)

target_link_libraries(unit_tests PRIVATE
    pico_stdlib    
    platform
    hardware_flash
    engine
    pulp
    unity
)
