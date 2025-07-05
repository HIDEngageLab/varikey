// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: serial frame module
// SPDX-FileType: SOURCE

#include <assert.h>
#include <stdint.h>

#include "checksum.hpp"
#include "cmd_protocol_msg.hpp"
#include "commander.hpp"
#include "macros.hpp"
#include "serial_frame.hpp"

namespace engine::serial::frame
{
    static const size_t MESSAGE_SPACE_SIZE = 64;
    static const uint8_t DELIMITER = 0x7e;
    static const uint8_t MINIMAL_FRAME_SIZE = 6;
    static const uint16_t CORRUPT_SHORT_FRAME_COUNTER_THRESHOLD = 500;
    static const uint16_t CORRUPT_LONG_FRAME_COUNTER_THRESHOLD = 500;

    static const size_t BYTERING_BUFFER_SIZE = (1 << 8);
    static const uint8_t HANDLER_REGISTER_SIZE = 2;
    static const uint8_t DEFAULT_ADDRESS_FIELD = 0x00;
    static const uint8_t DEFAULT_CONTROL_FIELD = 0x01;

    enum class ITEM_STATE : uint8_t
    {
        FREE,
        BUSY
    };

    struct handler_register_t
    {
        ITEM_STATE state;
        uint8_t address;
        handler_t handler;
    };

    static handler_register_t handler_register[HANDLER_REGISTER_SIZE];

    static uint8_t tx_space[BYTERING_BUFFER_SIZE];
    static const chunk_t tx_chunk = {tx_space, BYTERING_BUFFER_SIZE};
    static buffer_t tx_buffer;

    static uint8_t rx_space[BYTERING_BUFFER_SIZE];
    static const chunk_t rx_chunk = {rx_space, BYTERING_BUFFER_SIZE};
    static buffer_t rx_buffer;

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

    extern void usart_data_handler(buffer_t *const _rx_buffer, buffer_t *const _tx_buffer)
    {
        assert(status == STATUS::READY); // serial frame USART data and wrong status
        bytering_copy(_rx_buffer, &rx_buffer);
        bytering_copy(&tx_buffer, _tx_buffer);
    }

    extern void register_handler(uint8_t const _address, handler_t _handler)
    {
        uint8_t free_index = HANDLER_REGISTER_SIZE;

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

                        handler_register[free_index].handler = _handler;
                        return;
                    }
                }
            }
        }

        if (free_index < HANDLER_REGISTER_SIZE)
        {
            handler_register[free_index].state = ITEM_STATE::BUSY;
            handler_register[free_index].address = _address;
            handler_register[free_index].handler = _handler;
        }
    }

    extern uint8_t send(uint8_t const _address, chunk_t const *const _chunk)
    {
        assert(_chunk != NULL && _chunk->size < (MESSAGE_SPACE_SIZE - MINIMAL_FRAME_SIZE)); // serial frame send chunk not null
        assert(status == STATUS::READY);                                                    // serial frame send and wrong status

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

    extern void perform(void)
    {

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

                bytering_read(&rx_buffer, &byte);
            }
            else if ((byte == DELIMITER) && (start_delimiter_found == false))
            {

                start_delimiter_found = true;
                cursor++;
            }
            else if ((byte != DELIMITER) && (start_delimiter_found == true))
            {

                cursor++;
            }
            else if ((byte == DELIMITER) && (start_delimiter_found == true))
            {

                cursor++;

                if (cursor < MINIMAL_FRAME_SIZE)
                {

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

            corrupt_long_frame_detected_counter = 0;
            next_frame();
        }

        return false;
    }

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

                assert(false);
            }
            else if ((byte == DELIMITER) && (start_delimiter_found == false))
            {

                start_delimiter_found = true;
                bytering_read(&rx_buffer, &byte);                          // read delimiter
                bytering_read(&rx_buffer, &_serial_frame_fields->address); // read address field
                bytering_read(&rx_buffer, &_serial_frame_fields->control); // read control field
            }
            else if ((byte != DELIMITER) && (start_delimiter_found == true))
            {

                bytering_read(&rx_buffer, &_serial_frame_fields->pdu.space[data_index]);

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
                assert(data_index < MESSAGE_SPACE_SIZE);
            }
            else if ((byte == DELIMITER) && (start_delimiter_found == true))
            {

                bytering_read(&rx_buffer, &byte);

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

    static void next_frame(void)
    {
        uint8_t byte = 0;
        bool start_delimiter_found = false;

        while (bytering_peek(&rx_buffer, 0, &byte) == 1)
        {
            if ((byte != DELIMITER) && (start_delimiter_found == false))
            {

                bytering_read(&rx_buffer, &byte);
            }
            else if ((byte == DELIMITER) && (start_delimiter_found == false))
            {

                start_delimiter_found = true;
                bytering_read(&rx_buffer, &byte);
            }
            else if ((byte != DELIMITER) && (start_delimiter_found == true))
            {

                bytering_read(&rx_buffer, &byte);
            }
            else if ((byte == DELIMITER) && (start_delimiter_found == true))
            {

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
