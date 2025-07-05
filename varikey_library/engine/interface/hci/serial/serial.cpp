// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: serial module
// SPDX-FileType: SOURCE

#include "serial.hpp"
#include "commander.hpp"
#include "serial_frame.hpp"
#include "usart.hpp"

using namespace engine::serial;


extern void engine::serial::init(void)
{
    
    g_usart_rx_tx_handler = frame::usart_data_handler;

    
    frame::init();
    
    frame::register_handler(engine::hci::INTERPRETER_ADDRESS,
                            engine::hci::interpreter);
}

extern void engine::serial::perform(void)
{
    frame::perform();
}
