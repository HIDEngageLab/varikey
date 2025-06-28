/**
 * \file serial.cpp
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */
/**
    \brief Entry point for serial engine, data exchange over UART interface

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#include "serial.hpp"
#include "commander.hpp"
#include "serial_frame.hpp"
#include "usart.hpp"

using namespace engine::serial;

/**
    \brief  Initialize serial engine
*/
extern void engine::serial::init(void)
{
    /* set external dependency between core USART module and the serial engine */
    g_usart_rx_tx_handler = frame::usart_data_handler;

    /* initialize serial engine */
    frame::init();
    /* register interpreter with address by serial frame handler */
    frame::register_handler(engine::hci::INTERPRETER_ADDRESS,
                            engine::hci::interpreter);
}

extern void engine::serial::perform(void)
{
    frame::perform();
}
