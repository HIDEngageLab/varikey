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

/**
    \brief  Initialize serial engine
*/
extern void serial_init(void)
{
    /* set external dependency between core USART module and the serial engine */
    g_usart_rx_tx_handler = engine::serial::frame::usart_data_handler;

    /* initialize serial engine */
    engine::serial::frame::init();
    /* register interpreter with address by serial frame handler */
    engine::serial::frame::register_handler(engine::hci::INTERPRETER_ADDRESS,
                                            engine::hci::interpreter);
}

extern void serial_perform(void)
{
    engine::serial::frame::perform();
}
