# Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
# SPDX-License-Identifier: MIT

add_library(pulp)

target_sources(pulp PRIVATE
    ${CMAKE_SOURCE_DIR}/src/pulp/bytering.cpp
    ${CMAKE_SOURCE_DIR}/src/pulp/checksum.cpp
    ${CMAKE_SOURCE_DIR}/src/pulp/macros.cpp
    ${CMAKE_SOURCE_DIR}/src/pulp/random.cpp
)

include(${CMAKE_SOURCE_DIR}/build/subdirectories.cmake)
get_subdirectories(PULP_SUBDIRS ${CMAKE_CURRENT_LIST_DIR})

target_include_directories(pulp INTERFACE 
    ${CMAKE_CURRENT_LIST_DIR}
    ${PULP_SUBDIRS}
)
