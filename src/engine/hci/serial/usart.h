/**
 * \file usart.h
 * \author Koch, Roman (koch.roman@googlemail.com)
 * \brief
 * \version 0.1
 * @date 2023-03-28
 *
 * @copyright Copyright (c) 2023
 *
 */
/**
    \brief USART controller

    \internal
    \author Roman Koch, koch.roman@googlemail.com
*/

#ifndef __USART_H__
#define __USART_H__

#include "bytering.h"

/** \brief Type for RX/TX handler */
typedef void (*usart_rx_tx_handler_t)(buffer_t *const _rx, buffer_t *const _tx);

/** \brief Global USART TR/TX handler */
extern usart_rx_tx_handler_t g_usart_rx_tx_handler;

extern void usart_init(void);
extern void usart_start(void);
extern void usart_stop(void);
extern void usart_shutdown(void);

extern void usart_perform(void);

extern void usart_last_whisper(uint8_t const _byte);

#endif /* __USART_H__ */
