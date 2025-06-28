# Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
# SPDX-License-Identifier: MIT

find_program(FIGLET figlet)
if(FIGLET)
    add_custom_target(ascii_art
        COMMAND sh -c "figlet ${PROJECT_NAME} ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR} && figlet -f small custom keypad && echo && echo Copyright 2023 Roman Koch, roman.koch@gmail.com && echo"
        VERBATIM
    )
else()
    add_custom_target(ascii_art
        COMMAND sh -c "echo && echo ${PROJECT_NAME} ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR} && echo custom keypad && echo && echo Copyright 2023 Roman Koch, roman.koch@gmail.com && echo"
        VERBATIM
    )
endif()
