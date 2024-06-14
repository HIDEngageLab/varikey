add_library(platform)

pico_generate_pio_header(platform "${PROJECT_SOURCE_DIR}/src/platform/hardware/backlight/ws2812.pio")

target_sources(platform PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/board/board_assembly.cpp
    ${CMAKE_CURRENT_LIST_DIR}/hardware/backlight/backlight_ws2812.cpp
    ${CMAKE_CURRENT_LIST_DIR}/hardware/backlight/ws2812.cpp
    ${CMAKE_CURRENT_LIST_DIR}/hardware/display/display_oled_128x32.cpp
    ${CMAKE_CURRENT_LIST_DIR}/hardware/display/ssd1306.cpp
    ${CMAKE_CURRENT_LIST_DIR}/hardware/keymatrix/adp5585.cpp
    ${CMAKE_CURRENT_LIST_DIR}/hardware/keymatrix/keymatrix_adp5585_handler_gossenmetrawatt.cpp
    ${CMAKE_CURRENT_LIST_DIR}/hardware/keymatrix/keymatrix_adp5585_handler_varikey.cpp
    ${CMAKE_CURRENT_LIST_DIR}/hardware/keymatrix/keymatrix_adp5585_handler.cpp
    ${CMAKE_CURRENT_LIST_DIR}/hardware/keymatrix/keymatrix_adp5585.cpp
    ${CMAKE_CURRENT_LIST_DIR}/hardware/soc/rp2040/rp2040_gpio.cpp
    ${CMAKE_CURRENT_LIST_DIR}/hardware/soc/rp2040/rp2040_soc.cpp
    ${CMAKE_CURRENT_LIST_DIR}/hardware/soc/rp2040/rp2040_stopwatch.cpp
    ${CMAKE_CURRENT_LIST_DIR}/hardware/soc/rp2040/rp2040_temperature.cpp
    ${CMAKE_CURRENT_LIST_DIR}/hardware/soc/rp2040/rp2040_ticker.cpp
    ${CMAKE_CURRENT_LIST_DIR}/hardware/soc/rp2040/rp2040_watchdog.cpp
    ${CMAKE_CURRENT_LIST_DIR}/hardware/uart/usart.cpp
    ${CMAKE_CURRENT_LIST_DIR}/hardware/usb/usb_descriptors.cpp
    ${CMAKE_CURRENT_LIST_DIR}/hardware/usb/usb_device.cpp
    ${CMAKE_CURRENT_LIST_DIR}/platform.cpp
)

include(${CMAKE_SOURCE_DIR}/build/subdirectories.cmake)
get_subdirectories(PLATFORM_SUBDIRS ${CMAKE_CURRENT_LIST_DIR})

target_include_directories(platform PUBLIC 
    ${PICO_SDK_PATH}/pico
    ${CMAKE_CURRENT_LIST_DIR}
    ${PLATFORM_SUBDIRS}
)

target_link_libraries(platform 
    pico_stdlib
    hardware_adc
    hardware_flash
    hardware_i2c
    hardware_spi
    hardware_sync
    hardware_pio
    hardware_exception
    tinyusb_board
    tinyusb_device
    registry
    engine
    pulp
)
