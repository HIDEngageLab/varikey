# Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
# SPDX-License-Identifier: MIT

find_program(CPPCHECK cppcheck)
if(CPPCHECK)
    message(STATUS "cppcheck found: ${CPPCHECK}")
    add_custom_target(
        cppcheck 
        COMMAND ${CPPCHECK} --enable=all --quiet --std=c++17 --xml-version=2 ${CMAKE_SOURCE_DIR}/src  2> ${CMAKE_BINARY_DIR}/cppcheck.xml
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMENT "Running cppcheck on ${CMAKE_SOURCE_DIR}"
    )
else()
    message(STATUS "cppcheck not found, skipping cppcheck target")
endif()

find_program(CPPREPORT cppcheck-htmlreport)
if(CPPREPORT)
    message(STATUS "cppcheck-htmlreport found: ${CPPREPORT}")
    add_custom_target(
        cppreport 
        COMMAND ${CPPREPORT} --title="Cppcheck Report" --file=${CMAKE_BINARY_DIR}/cppcheck.xml --report-dir=${CMAKE_BINARY_DIR}/cppcheck_report
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMENT "Running cppcheck-htmlreport on ${CMAKE_SOURCE_DIR}"
    )
else()
    message(STATUS "cppcheck-htmlreport not found, skipping cppcheck target")
endif()

find_program(CLOC cloc)
if(CLOC)
    message(STATUS "cloc found: ${CLOC}")
    add_custom_target(
        cloc
        COMMAND cloc --quiet --exclude-dir=bin --out=${CMAKE_BINARY_DIR}/cloc-result.txt . && cat  ${CMAKE_BINARY_DIR}/cloc-result.txt
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMENT "Running cloc on source code"
    )
else()
    message(STATUS "clock not found, skipping cppcheck target")
endif()
