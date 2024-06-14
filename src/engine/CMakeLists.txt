add_library(engine)

target_sources(engine PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/backlight/backlight3.cpp
    ${CMAKE_CURRENT_LIST_DIR}/display/display.cpp
    ${CMAKE_CURRENT_LIST_DIR}/display/resources/display_font.cpp
    ${CMAKE_CURRENT_LIST_DIR}/display/resources/display_image.cpp
    ${CMAKE_CURRENT_LIST_DIR}/display/resources/fonts/font_big.c
    ${CMAKE_CURRENT_LIST_DIR}/display/resources/fonts/font_huge.c
    ${CMAKE_CURRENT_LIST_DIR}/display/resources/fonts/font_normal.c
    ${CMAKE_CURRENT_LIST_DIR}/display/resources/fonts/font_small.c
    ${CMAKE_CURRENT_LIST_DIR}/display/resources/fonts/font_symbol.c
    ${CMAKE_CURRENT_LIST_DIR}/display/resources/images/image_add_circle_16.c
    ${CMAKE_CURRENT_LIST_DIR}/display/resources/images/image_add_circle_24.c
    ${CMAKE_CURRENT_LIST_DIR}/display/resources/images/image_add_circle_32.c
    ${CMAKE_CURRENT_LIST_DIR}/display/resources/images/image_add_circle_8.c
    ${CMAKE_CURRENT_LIST_DIR}/display/resources/images/image_add_square_16.c
    ${CMAKE_CURRENT_LIST_DIR}/display/resources/images/image_add_square_24.c
    ${CMAKE_CURRENT_LIST_DIR}/display/resources/images/image_add_square_32.c
    ${CMAKE_CURRENT_LIST_DIR}/display/resources/images/image_add_square_8.c
    ${CMAKE_CURRENT_LIST_DIR}/display/resources/images/image_frame.c
    ${CMAKE_CURRENT_LIST_DIR}/display/resources/images/image_gmc.c
    ${CMAKE_CURRENT_LIST_DIR}/display/resources/images/image_heart.c
    ${CMAKE_CURRENT_LIST_DIR}/display/resources/images/image_varikey.c
    ${CMAKE_CURRENT_LIST_DIR}/engine_event_handler.cpp
    ${CMAKE_CURRENT_LIST_DIR}/engine.cpp
    ${CMAKE_CURRENT_LIST_DIR}/gpio/engine_gpio.cpp
    ${CMAKE_CURRENT_LIST_DIR}/interface/hci/commander/cmd_control.cpp
    ${CMAKE_CURRENT_LIST_DIR}/interface/hci/commander/cmd_feature.cpp
    ${CMAKE_CURRENT_LIST_DIR}/interface/hci/commander/cmd_setting.cpp
    ${CMAKE_CURRENT_LIST_DIR}/interface/hci/commander/commander.cpp
    ${CMAKE_CURRENT_LIST_DIR}/interface/hci/commander/control/cmd_gadget_msg.cpp
    ${CMAKE_CURRENT_LIST_DIR}/interface/hci/commander/control/cmd_hash_msg.cpp
    ${CMAKE_CURRENT_LIST_DIR}/interface/hci/commander/control/cmd_protocol_msg.cpp
    ${CMAKE_CURRENT_LIST_DIR}/interface/hci/commander/control/cmd_reset_msg.cpp
    ${CMAKE_CURRENT_LIST_DIR}/interface/hci/commander/control/cmd_temperature_msg.cpp
    ${CMAKE_CURRENT_LIST_DIR}/interface/hci/commander/feature/cmd_backlight_msg.cpp
    ${CMAKE_CURRENT_LIST_DIR}/interface/hci/commander/feature/cmd_display_msg.cpp
    ${CMAKE_CURRENT_LIST_DIR}/interface/hci/commander/feature/cmd_gpio_msg.cpp
    ${CMAKE_CURRENT_LIST_DIR}/interface/hci/commander/feature/cmd_keypad_msg.cpp
    ${CMAKE_CURRENT_LIST_DIR}/interface/hci/commander/setting/cmd_identity_msg.cpp
    ${CMAKE_CURRENT_LIST_DIR}/interface/hci/commander/setting/cmd_parameter_msg.cpp
    ${CMAKE_CURRENT_LIST_DIR}/interface/hci/serial/serial_frame.cpp
    ${CMAKE_CURRENT_LIST_DIR}/interface/hci/serial/serial_msg.cpp
    ${CMAKE_CURRENT_LIST_DIR}/interface/hci/serial/serial.cpp
    ${CMAKE_CURRENT_LIST_DIR}/interface/hid/hid_handler.cpp
    ${CMAKE_CURRENT_LIST_DIR}/interface/hid/hid_report.cpp
    ${CMAKE_CURRENT_LIST_DIR}/interface/payload/payload_backlight.cpp
    ${CMAKE_CURRENT_LIST_DIR}/interface/payload/payload_display.cpp
    ${CMAKE_CURRENT_LIST_DIR}/interface/payload/payload_gadget.cpp
    ${CMAKE_CURRENT_LIST_DIR}/interface/payload/payload_gpio.cpp
    ${CMAKE_CURRENT_LIST_DIR}/interface/payload/payload_identity.cpp
    ${CMAKE_CURRENT_LIST_DIR}/interface/payload/payload_keypad.cpp
    ${CMAKE_CURRENT_LIST_DIR}/interface/payload/payload_parameter.cpp
    ${CMAKE_CURRENT_LIST_DIR}/interface/payload/payload_reset.cpp
    ${CMAKE_CURRENT_LIST_DIR}/interface/payload/payload_temperature.cpp
    ${CMAKE_CURRENT_LIST_DIR}/keypad/keypad_keycode_10bwdb.cpp
    ${CMAKE_CURRENT_LIST_DIR}/keypad/keypad_keycode_varikey.cpp
    ${CMAKE_CURRENT_LIST_DIR}/keypad/keypad_keycode.cpp
    ${CMAKE_CURRENT_LIST_DIR}/keypad/keypad_modifiers.cpp
    ${CMAKE_CURRENT_LIST_DIR}/keypad/keypad.cpp
    ${CMAKE_CURRENT_LIST_DIR}/parameter/param_backlight.cpp
    ${CMAKE_CURRENT_LIST_DIR}/parameter/param_display.cpp
    ${CMAKE_CURRENT_LIST_DIR}/parameter/param_features.cpp
    ${CMAKE_CURRENT_LIST_DIR}/parameter/param_keypad.cpp
    ${CMAKE_CURRENT_LIST_DIR}/parameter/param_maintainer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/parameter/param_mapping.cpp
    ${CMAKE_CURRENT_LIST_DIR}/parameter/param_position.cpp
    ${CMAKE_CURRENT_LIST_DIR}/parameter/param_serial_number.cpp
    ${CMAKE_CURRENT_LIST_DIR}/parameter/param_user.cpp
    ${CMAKE_CURRENT_LIST_DIR}/parameter/parameter_identifier.cpp
)

target_include_directories(engine PRIVATE
    ${CMAKE_SOURCE_DIR}/src
)

include(${CMAKE_SOURCE_DIR}/build/subdirectories.cmake)
get_subdirectories(ENGINE_SUBDIRS ${CMAKE_CURRENT_LIST_DIR})

target_include_directories(engine PUBLIC 
    ${PICO_SDK_PATH}/pico
    ${CMAKE_CURRENT_LIST_DIR}
    ${ENGINE_SUBDIRS}
)

target_link_libraries(engine 
    pico_stdlib
    tinyusb_board
    tinyusb_device
    platform
    pulp
)
