/**
 * \file serial_frame.h
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * @copyright Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 *
 */
/**
    \brief HDLC-like framing

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#ifndef __SERIAL_FRAME_H__
#define __SERIAL_FRAME_H__

#include "bytering.h"
#include "cmd_hci_status_msg.h"

typedef cmd_hci_status_result_t (*serial_frame_handler_t)(chunk_t const *_chunk);

extern void serial_frame_init(void);
extern void serial_frame_usart_data_handler(buffer_t *const _rx_buffer, buffer_t *const _tx_buffer);
extern void serial_frame_register_handler(uint8_t const _address, serial_frame_handler_t _handler);
extern uint8_t serial_frame_send(uint8_t const _address, chunk_t const *const _chunk);
extern void serial_frame_perform(void);

#endif /* __SERIAL_FRAME_H__ */
