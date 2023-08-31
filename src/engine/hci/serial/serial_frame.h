/**
 * \file serial_frame.h
 * \author Koch, Roman (koch.roman@googlemail.com)
 * \brief
 * \version 0.1
 * @date 2023-03-28
 *
 * @copyright Copyright (c) 2023
 *
 */
/**
    \brief HDLC-like framing

    \internal
    \author Roman Koch, koch.roman@googlemail.com
*/

#ifndef __SERIAL_FRAME_H__
#define __SERIAL_FRAME_H__

#include "bytering.h"
#include "cmd_hci_status_msg.h"
#include "types.h"

    typedef cmd_hci_status_result_t (*serial_frame_handler_t)(chunk_t const *_chunk);

extern void serial_frame_init(void);
extern void serial_frame_usart_data_handler(buffer_t *const _rx_buffer, buffer_t *const _tx_buffer);
extern void serial_frame_register_handler(uint8_t const _address, serial_frame_handler_t _handler);
extern uint8_t serial_frame_send(uint8_t const _address, chunk_t const *const _chunk);
extern void serial_frame_perform(void);

#endif /* __SERIAL_FRAME_H__ */
