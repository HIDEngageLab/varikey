// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: Byte manipulation implementation
// SPDX-FileType: SOURCE

#include "bytering.hpp"

#define __DEBUG_BYTE_RING

#ifdef DEBUG_BYTE_RING
static void bytering_test(void);
static void randtest(void);
#endif


extern void bytering_init(buffer_t *const buf, uint8_t *const _space, size_t const _size)
{
    buf->chunk.space = _space;
    buf->chunk.size = _size;
    buf->number_of_free_items = _size;
    buf->in = 0;
    buf->out = 0;
}


extern size_t bytering_write(buffer_t *const _buf, uint8_t const _value)
{
    if (_buf->number_of_free_items == 0)
    {
        // buffer is full
        return 0;
    }

    _buf->number_of_free_items--;
    _buf->chunk.space[_buf->in++] = _value;
    _buf->in &= (_buf->chunk.size - 1);
#ifdef DEBUG_BYTE_RING
    size_t dist = (_buf->in < _buf->out) ? _buf->out - _buf->in : _buf->in - _buf->out;

    if ((dist > 0) && (_buf->number_of_free_items == 0))
    {
        assert(false); // byte ring write free items number error
    }

#endif
    return 1;
}


extern size_t bytering_read(buffer_t *const _buf, uint8_t *const _value)
{
    if ((_buf->number_of_free_items == _buf->chunk.size) && (_buf->in == _buf->out))
    {
        // buffer is empty
        return 0;
    }

    _buf->number_of_free_items++;
    *_value = _buf->chunk.space[_buf->out++];
    _buf->out &= (_buf->chunk.size - 1);
#ifdef DEBUG_BYTE_RING
    size_t dist = (_buf->in < _buf->out) ? _buf->out - _buf->in : _buf->in - _buf->out;

    if ((dist > 0) && (_buf->number_of_free_items == 0))
    {
        // byte ring write free items number error
    }

#endif
    return 1;
}


extern size_t bytering_copy(buffer_t *const _from, buffer_t *const _to)
{
    size_t cntr = 0;
    uint8_t byte;

    while (_to->number_of_free_items && bytering_read(_from, &byte))
    {
        bytering_write(_to, byte);
        cntr++;
    }

    return cntr;
}

extern size_t bytering_peek(buffer_t *const _buf, const size_t _cursor, uint8_t *const _value)
{
    if ((_buf->number_of_free_items == _buf->chunk.size) && (_buf->in == _buf->out))
    {
        // buffer is empty
        return 0;
    }

    // attention: position can be "over the border"
    uint8_t position = (_buf->out + _cursor);
    // truncate position to the buffer size
    position &= (_buf->chunk.size - 1);

    if (_buf->in > _buf->out)
    {
        // normal in-out order
        if (position >= _buf->in)
        {
            return 0;
        }
    }
    else
    {
        // inverse in-out order (chunk placed "over the border")
        if ((position >= _buf->in) && (position < _buf->out))
        {
            return 0;
        }
    }

    *_value = _buf->chunk.space[position];
    return 1;
}


#ifdef DEBUG_BYTE_RING
static void bytering_test(void)
{
    buffer_t tx_buffer;
    uint8_t tx_space[4];
    bytering_init(&tx_buffer, tx_space, 4);
    buffer_t rx_buffer;
    uint8_t rx_space[8];
    bytering_init(&rx_buffer, rx_space, 8);
    uint8_t byte1;
    size_t result1;
    result1 = bytering_read(&tx_buffer, &byte1);
    result1 = bytering_read(&tx_buffer, &byte1);
    result1 = bytering_write(&tx_buffer, 'h');
    result1 = bytering_write(&tx_buffer, 'a');
    result1 = bytering_write(&tx_buffer, 'l');
    result1 = bytering_write(&tx_buffer, 'l');
    result1 = bytering_write(&tx_buffer, '0');
    result1 = bytering_read(&tx_buffer, &byte1);
    result1 = bytering_read(&tx_buffer, &byte1);
    result1 = bytering_write(&tx_buffer, 'x');
    result1 = bytering_write(&tx_buffer, 'y');
    result1 = bytering_write(&tx_buffer, 'z');
    result1 = bytering_read(&tx_buffer, &byte1);
    result1 = bytering_read(&tx_buffer, &byte1);
    result1 = bytering_read(&tx_buffer, &byte1);
    result1 = bytering_read(&tx_buffer, &byte1);
    result1 = bytering_read(&tx_buffer, &byte1);
    result1 = bytering_read(&tx_buffer, &byte1);
    result1 = bytering_write(&tx_buffer, '1');
    result1 = bytering_write(&tx_buffer, '2');
    result1 = bytering_copy(&tx_buffer, &rx_buffer);
    result1 = bytering_read(&rx_buffer, &byte1);
    result1 = bytering_read(&rx_buffer, &byte1);
    result1 = bytering_write(&tx_buffer, '1');
    result1 = bytering_write(&tx_buffer, '2');
    result1 = bytering_write(&tx_buffer, '3');
    result1 = bytering_write(&tx_buffer, '4');
    result1 = bytering_write(&tx_buffer, '5');
    result1 = bytering_copy(&tx_buffer, &rx_buffer);
    result1 = bytering_read(&rx_buffer, &byte1);
    result1 = bytering_read(&rx_buffer, &byte1);
    result1 = bytering_read(&rx_buffer, &byte1);
    result1 = bytering_read(&rx_buffer, &byte1);
    result1 = bytering_read(&rx_buffer, &byte1);
    result1 = bytering_read(&rx_buffer, &byte1);
    result1 = bytering_write(&tx_buffer, '1');
    result1 = bytering_write(&tx_buffer, '2');
    result1 = bytering_write(&tx_buffer, '3');
    result1 = bytering_write(&tx_buffer, '4');
    result1 = bytering_write(&tx_buffer, '5');
    result1 = bytering_copy(&tx_buffer, &rx_buffer);
    result1 = bytering_write(&tx_buffer, '1');
    result1 = bytering_write(&tx_buffer, '2');
    result1 = bytering_write(&tx_buffer, '3');
    result1 = bytering_write(&tx_buffer, '4');
    result1 = bytering_write(&tx_buffer, '5');
    result1 = bytering_copy(&tx_buffer, &rx_buffer);
}
#endif 

#ifdef DEBUG_BYTE_RING
static void randtest(void)
{
    uint8_t message_space[12];
    memset(message_space, 0xaa, 12);
    chunk_t message_chunk = {message_space, 12};
    uint8_t buffer_space[32];
    memset(buffer_space, 0x55, 32);
    buffer_t buffer;
    bytering_init(&buffer, buffer_space, 32);
    volatile size_t result;
    volatile uint8_t value;

    for (int a = 0; a < 3; a++)
    {
        for (int i = 0; i < 12; i++)
        {
            result = bytering_write(&buffer, message_space[i]);
        }

        for (int i = 0; i < 12; i++)
        {
            result = bytering_peek(&buffer, i, &value);
        }

        for (int i = 0; i < 12; i++)
        {
            result = bytering_read(&buffer, &value);
        }
    }
}
#endif 
