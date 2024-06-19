# Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
# SPDX-License-Identifier: MIT

add_library(registry STATIC) 

target_sources(registry PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/parameter.cpp
    ${CMAKE_CURRENT_LIST_DIR}/registry_interface.cpp
    ${CMAKE_CURRENT_LIST_DIR}/registry.cpp
)

include(${CMAKE_SOURCE_DIR}/build/subdirectories.cmake)
get_subdirectories(RESISTRY_SUBDIRS ${CMAKE_CURRENT_LIST_DIR})

target_include_directories(registry PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
    ${RESISTRY_SUBDIRS}
)

target_link_libraries(registry PRIVATE
    pico_stdlib    
    platform
    hardware_flash
    engine
    pulp
)