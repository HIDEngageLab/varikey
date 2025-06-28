/**
 * \file serial_frame.cpp
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */
/**
    \brief HDLC-like frame

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#include <assert.h>
#include <stdint.h>

#include "checksum.hpp"
#include "cmd_protocol_msg.hpp"
#include "commander.hpp"
#include "macros.hpp"
#include "serial_frame.hpp"

namespace engine
{
    namespace serial
    {
        namespace frame
        {

            static const size_t MESSAGE_SPACE_SIZE = 64;
            static const uint8_t DELIMITER = 0x7e;
            static const uint8_t MINIMAL_FRAME_SIZE = 6;
            static const uint16_t CORRUPT_SHORT_FRAME_COUNTER_THRESHOLD = 500;
            static const uint16_t CORRUPT_LONG_FRAME_COUNTER_THRESHOLD = 500;

            /* Attention: only pow 2 values are legal! */
            static const size_t BYTERING_BUFFER_SIZE = (1 << 8);
            static const uint8_t HANDLER_REGISTER_SIZE = 2;
            static const uint8_t DEFAULT_ADDRESS_FIELD = 0x00;
            static const uint8_t DEFAULT_CONTROL_FIELD = 0x01;

            enum class ITEM_STATE : uint8_t
            {
                FREE,
                BUSY
            };

            /** \name Serial handler */
            /* @{ */
            /**
                \brief Handler register

                All the handler of received data needs to register here with they address.
            */
            struct handler_register_t
            {
                ITEM_STATE state;
                uint8_t address;
                handler_t handler;
            };

            static handler_register_t handler_register[HANDLER_REGISTER_SIZE];
            /* @} */

            /**
                \name Serial buffer
                \brief TX buffer space; ~3% RAM fro a serial buffer
            */
            /* @{ */
            static uint8_t tx_space[BYTERING_BUFFER_SIZE];
            static const chunk_t tx_chunk = {tx_space, BYTERING_BUFFER_SIZE};
            static buffer_t tx_buffer;
            /* @} */

            /**
                \name Serial Buffer
                \brief RX buffer space; ~3% RAM fro a serial buffer
            */
            /* @{ */
            static uint8_t rx_space[BYTERING_BUFFER_SIZE];
            static const chunk_t rx_chunk = {rx_space, BYTERING_BUFFER_SIZE};
            static buffer_t rx_buffer;
            /* @} */

            /**
                \brief Serial frame fields description
            */
            struct fields_t
            {
                uint8_t address; //< Address field
                uint8_t control; //< Control field
                chunk_t pdu;     //< Serial frame (check sum will be cut by length)
            };

            enum class STATUS : uint8_t
            {
                IDLE,
                READY
            };
            static STATUS status = STATUS::IDLE;

            static bool check_frame(void);
            static bool parse_frame(fields_t *);
            static void next_frame(void);

            static uint8_t store_byte(uint8_t const);

            /**
                \brief Serial frame initialization
            */
            extern void init(void)
            {
                assert(status == STATUS::IDLE); // serial frame initialization and wrong status
                status = STATUS::READY;
                bytering_init(&tx_buffer, tx_chunk.space, tx_chunk.size);
                bytering_init(&rx_buffer, rx_chunk.space, rx_chunk.size);

                for (uint8_t i = 0; i < HANDLER_REGISTER_SIZE; ++i)
                {
                    handler_register[i].state = ITEM_STATE::FREE;
                    handler_register[i].address = 0;
                    handler_register[i].handler = 0;
                }
            }

            /**
                \brief Handle USART data
            */
            extern void usart_data_handler(buffer_t *const _rx_buffer, buffer_t *const _tx_buffer)
            {
                assert(status == STATUS::READY); // serial frame USART data and wrong status
                bytering_copy(_rx_buffer, &rx_buffer);
                bytering_copy(&tx_buffer, _tx_buffer);
            }

            /**
                \brief Register handler with address
            */
            extern void register_handler(uint8_t const _address, handler_t _handler)
            {
                uint8_t free_index = HANDLER_REGISTER_SIZE;

                /* search for a empty space for address/handler and check for uniques */
                for (uint8_t i = 0; i < HANDLER_REGISTER_SIZE; ++i)
                {
                    if (handler_register[i].state == ITEM_STATE::FREE)
                    {
                        if (free_index == HANDLER_REGISTER_SIZE)
                        {
                            free_index = i;
                        }
                        else
                        {
                            if (handler_register[i].address == _address)
                            {
                                /* attention: handler was already registered */
                                handler_register[free_index].handler = _handler;
                                return;
                            }
                        }
                    }
                }

                /* register handler */
                if (free_index < HANDLER_REGISTER_SIZE)
                {
                    handler_register[free_index].state = ITEM_STATE::BUSY;
                    handler_register[free_index].address = _address;
                    handler_register[free_index].handler = _handler;
                }
            }

            /**
                \brief Send chunk over serial

                Delimiter   0x7e
                Escape      0x7d->0x7d,0x5d, 0x7e->0x7d,0x5e
                De-escape   0x7d,0x5d->0x7d, 0x7d,0x5e->0x7e

                \param _address Target address
                \param _chunk Data to send

                \return Number of send bytes
            */
            extern uint8_t send(uint8_t const _address, chunk_t const *const _chunk)
            {
                assert(_chunk != NULL && _chunk->size < (MESSAGE_SPACE_SIZE - MINIMAL_FRAME_SIZE)); // serial frame send chunk not null
                assert(status == STATUS::READY);                                                    // serial frame send and wrong status
                /* try to send... */

                /* check TX buffer */
                if (tx_buffer.number_of_free_items < (_chunk->size + MINIMAL_FRAME_SIZE * 2))
                {
                    return 0;
                }

                uint8_t result = MINIMAL_FRAME_SIZE;
                uint8_t *ptr = _chunk->space;
                bytering_write(&tx_buffer, 0x7e);                  // write front delimiter
                bytering_write(&tx_buffer, _address);              // write address field
                bytering_write(&tx_buffer, DEFAULT_CONTROL_FIELD); // write control field
                uint16_t crc = 0;

                for (uint8_t i = 0; i < _chunk->size; ++i)
                {
                    uint8_t byte = *ptr++;
                    crc = checksum_crc_byte(byte, crc);
                    result += store_byte(byte);
                }

                crc = checksum_crc_postprocess(crc);

                uint8_t byte[2];
                byte[0] = HIBYTE(crc);
                byte[1] = LOBYTE(crc);

                for (uint8_t i = 0; i < 2; ++i)
                {
                    result += store_byte(byte[i]);
                }

                bytering_write(&tx_buffer, 0x7e); // write back delimiter
                return result;
            }

            /**
                \brief Perform frame

                Perform serial engine

                Attention: this job cost a lot of time...
            */
            extern void perform(void)
            {
                /* default functionality */
                if (check_frame() == true)
                {

                    uint8_t serial_msg_space[MESSAGE_SPACE_SIZE]; //< Serial message space
                    fields_t serial_frame_fields = {
                        DEFAULT_ADDRESS_FIELD,
                        DEFAULT_CONTROL_FIELD,
                        {serial_msg_space, 0},
                    };

                    if (parse_frame(&serial_frame_fields) == true)
                    {
                        /* interpret frame */
                        for (uint8_t i = 0; i < HANDLER_REGISTER_SIZE; ++i)
                        {
                            if ((handler_register[i].state == ITEM_STATE::BUSY) &&
                                (handler_register[i].address == serial_frame_fields.address))
                            {
                                assert(handler_register[i].handler != NULL); // serial frame perform handler null
                                hci::cmd::protocol::RESULT result = handler_register[i].handler(&serial_frame_fields.pdu);
                                if (result != hci::cmd::protocol::RESULT::SUCCESS)
                                {
                                    hci::cmd::protocol::message_t msg;
                                    msg.result = result;
                                    hci::cmd::protocol::indication(&msg, &serial_frame_fields.pdu);
                                }
                            }
                        }
                    }
                    else
                    {
                        // error: can't read frame
                    }
                }
            }
            /**
                \brief Frame detector

                Fast search for a frame in the RX buffer and remove the unsynchronized tails.
            */
            static bool check_frame(void)
            {
                const size_t used_space = rx_buffer.in - rx_buffer.out;

                static int corrupt_short_frame_detected_counter = 0;
                static int corrupt_long_frame_detected_counter = 0;

                if (used_space == 0)
                {
                    return false;
                }
                else if (used_space < MINIMAL_FRAME_SIZE)
                {
                    if (++corrupt_short_frame_detected_counter > CORRUPT_SHORT_FRAME_COUNTER_THRESHOLD)
                    {
                        corrupt_short_frame_detected_counter = 0;
                        corrupt_long_frame_detected_counter = 0;
                        next_frame();
                    }

                    return false;
                }

                corrupt_short_frame_detected_counter = 0;

                bool start_delimiter_found = false;
                uint8_t byte = 0;
                uint8_t cursor = 0;

                while (bytering_peek(&rx_buffer, cursor, &byte) == 1)
                {
                    if ((byte != DELIMITER) && (start_delimiter_found == false))
                    {
                        /* RX buffer data begins not with a delimiter: remove */
                        bytering_read(&rx_buffer, &byte);
                    }
                    else if ((byte == DELIMITER) && (start_delimiter_found == false))
                    {
                        /* frame begin found */
                        start_delimiter_found = true;
                        cursor++;
                    }
                    else if ((byte != DELIMITER) && (start_delimiter_found == true))
                    {
                        /* jump over frame data */
                        cursor++;
                    }
                    else if ((byte == DELIMITER) && (start_delimiter_found == true))
                    {
                        /* stop delimiter found: bingo! */
                        cursor++;

                        if (cursor < MINIMAL_FRAME_SIZE)
                        {
                            /* a frame length can't be under MINIMAL_FRAME_SIZE bytes: remove */
                            next_frame();
                            corrupt_long_frame_detected_counter = 0;
                            return false;
                        }

                        corrupt_long_frame_detected_counter = 0;
                        return true;
                    }
                }

                if (++corrupt_long_frame_detected_counter > CORRUPT_LONG_FRAME_COUNTER_THRESHOLD)
                {
                    /* a long broken frame over "long" time in the buffer: remove */
                    corrupt_long_frame_detected_counter = 0;
                    next_frame();
                }

                return false;
            }

            /**
                \brief Get frame data from RX buffer

                Attention: the data bytes are removed from RX buffer.

                Special bytes:
                    delimiter   0x7e
                    escape      0x7d->0x7d,0x5d, 0x7e->0x7d,0x5e
                    de-escape   0x7d,0x5d->0x7d, 0x7d,0x5e->0x7e

                Frame structure:
                     0               1               2                   3 - N-3     N-2             N-1             N
                    +- - - - - - - -+- - - - - - - -+- - - - - - - -+- - - ... - - -+- - - - - - - -+- - - - - - - -+- - - - - - - -+
                                    |               |               |               |               |               |               +--- delimiter
                                    |               |               |               |               |               +------------------- crc16/2
                                    |               |               |               |               +----------------------------------- crc16/1
                                    |               |               |               +--------------------------------------------------- SDU (serial message)
                                    |               |               +----- ... --------------------------------------------------------- control
                                    |               +--------------------- ... --------------------------------------------------------- address
                                    +------------------------------------- ... --------------------------------------------------------- delimiter
            */
            static bool parse_frame(fields_t *_serial_frame_fields)
            {
                uint8_t byte = 0;
                uint8_t data_index = 0;
                bool start_delimiter_found = false;

                while (bytering_peek(&rx_buffer, 0, &byte) == 1)
                {
                    // printf("byte: %02x\n", byte);

                    if ((byte != DELIMITER) && (start_delimiter_found == false))
                    {
                        /* data in buffer should begins with a delimiter */
                        assert(false); /* serial frame parser: wrong delimiter */
                    }
                    else if ((byte == DELIMITER) && (start_delimiter_found == false))
                    {
                        /* frame begin found */
                        start_delimiter_found = true;
                        bytering_read(&rx_buffer, &byte);                          // read delimiter
                        bytering_read(&rx_buffer, &_serial_frame_fields->address); // read address field
                        bytering_read(&rx_buffer, &_serial_frame_fields->control); // read control field
                    }
                    else if ((byte != DELIMITER) && (start_delimiter_found == true))
                    {
                        /* remove frame data from buffer */
                        bytering_read(&rx_buffer, &_serial_frame_fields->pdu.space[data_index]);

                        /* remove escapes */
                        if (data_index > 0)
                        {
                            if (_serial_frame_fields->pdu.space[data_index - 1] == 0x7d)
                            {
                                if (_serial_frame_fields->pdu.space[data_index] == 0x5d)
                                {
                                    _serial_frame_fields->pdu.space[data_index - 1] = 0x7d;
                                    data_index--;
                                }
                                else if (_serial_frame_fields->pdu.space[data_index] == 0x5e)
                                {
                                    _serial_frame_fields->pdu.space[data_index - 1] = 0x7e;
                                    data_index--;
                                }
                            }
                        }

                        data_index++;
                        assert(data_index < MESSAGE_SPACE_SIZE); /* serial frame parser: space */
                    }
                    else if ((byte == DELIMITER) && (start_delimiter_found == true))
                    {
                        /* stop delimiter found: remove and break, the next byte should be a delimiter too */
                        bytering_read(&rx_buffer, &byte);
                        /* check CRC (last two bytes) */
                        _serial_frame_fields->pdu.size = data_index - 2;
                        uint16_t read_crc = SETWORD(_serial_frame_fields->pdu.space[data_index - 2], _serial_frame_fields->pdu.space[data_index - 1]);
                        uint16_t calc_crc = checksum_crc(&_serial_frame_fields->pdu, 0);

                        // printf("read: %04x\n", read_crc);
                        // printf("calc: %04x\n", calc_crc);

                        if (calc_crc == read_crc)
                        {
                            return true;
                        }
                        else
                        {
                            return false;
                        }
                    }
                }

                return false;
            }

            /**
                \brief Clean up RX-buffer

                Cut RX-Buffer data from begin the buffer over the open frame delimiter and to the next frame close delimiter
            */
            static void next_frame(void)
            {
                uint8_t byte = 0;
                bool start_delimiter_found = false;

                while (bytering_peek(&rx_buffer, 0, &byte) == 1)
                {
                    if ((byte != DELIMITER) && (start_delimiter_found == false))
                    {
                        /* data in buffer begins not a non delimiter byte: erase */
                        bytering_read(&rx_buffer, &byte);
                    }
                    else if ((byte == DELIMITER) && (start_delimiter_found == false))
                    {
                        /* frame begin found */
                        start_delimiter_found = true;
                        bytering_read(&rx_buffer, &byte);
                    }
                    else if ((byte != DELIMITER) && (start_delimiter_found == true))
                    {
                        /* remove frame data from buffer */
                        bytering_read(&rx_buffer, &byte);
                    }
                    else if ((byte == DELIMITER) && (start_delimiter_found == true))
                    {
                        /* stop delimiter found: remove and break, the next byte should be a delimiter too */
                        bytering_read(&rx_buffer, &byte);
                    }
                }
            }

            static uint8_t store_byte(uint8_t const _byte)
            {
                if (_byte == 0x7d)
                {
                    bytering_write(&tx_buffer, 0x7d);
                    bytering_write(&tx_buffer, 0x5d);
                    return 2;
                }
                else if (_byte == 0x7e)
                {
                    bytering_write(&tx_buffer, 0x7d);
                    bytering_write(&tx_buffer, 0x5e);
                    return 2;
                }
                else
                {
                    bytering_write(&tx_buffer, _byte);
                }

                return 1;
            }
        }
    }
}