/**
 * \file storage_queue.c
 * \author Koch, Roman (koch.roman@googlemail.com)
 * \brief
 *
 * @copyright Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 *
 */
/**
   \brief Storage item

   \internal
   \author Roman Koch, koch.roman@googlemail.com
*/

#include "storage_queue.h"
#include "checksum.h"
#include "param_serial_number.h"
#include "storage_interface.h"
#include <pico/stdlib.h>
#include <stddef.h>
#include <string.h>

#define DEFAULT_RAM_DISK_SIZE (1024 * 16)

/* \name Adapter storage defines */
/* @{ */
#define RAM_DISK_SIZE (1024 * 16)
/* @} */

/**
    \brief Item state type
*/
typedef enum
{
    ITEM_DEFAULT = 0,
    ITEM_SELECTED = 1,
    ITEM_RESERVED = 2,
    ITEM_CORRUPT = 3,
} item_state_t;

/**
    \brief Storage item structure
*/
typedef struct storage_item_struct storage_item_t;
typedef struct storage_item_struct
{
    item_state_t status : 2;
    uint8_t reserved : 6;
    storage_item_t *prev;
    storage_item_t *next;
    hil_event_t event;
    uint32_t checksum;
} storage_item_t;

/**
    \brief Empty block structure
*/
typedef struct storage_block_struct storage_block_t;
typedef struct storage_block_struct
{
    storage_block_t *prev;
    storage_block_t *next;
    uint32_t size;
} storage_block_t;

static uint32_t memory_block[(RAM_DISK_SIZE) >> 2] = {0xffffffff};
static uint8_t *const storage = (uint8_t *const)memory_block;

static storage_block_t block;
static storage_item_t head;

static uint16_t select_max = 0;
static uint16_t select_index = 0;

static uint32_t item_checksum(storage_item_t const *const _item);

/**
    \brief Initialize item
*/
extern void storage_init(void)
{
    /* initialize free blocks */
    ((storage_block_t *)storage)->prev = &block;
    ((storage_block_t *)storage)->next = &block;
    ((storage_block_t *)storage)->size = RAM_DISK_SIZE;

    block.next = (storage_block_t *)storage;
    block.prev = (storage_block_t *)storage;
    block.size = RAM_DISK_SIZE;

    /* initialize items head */
    head.next = &head;
    head.prev = &head;

    head.status = ITEM_DEFAULT;
    head.checksum = KEY_VALUE_INVALID; // attention: the check value is invalid

    select_max = 0;
    select_index = 0;
}

/**
    \brief Return memory usage in bytes
*/
extern uint32_t storage_get_used_memory(void)
{
    return RAM_DISK_SIZE - block.size;
}

/**
    \brief Return memory usage in percent
*/
extern float storage_get_free_memory_progress(void)
{
    return 100.0 * ((float)block.size) / ((float)RAM_DISK_SIZE);
}

/**
    \brief Update (=store) data block in EEPROM
*/
extern result_t storage_enqueue(storage_transport_t const *const _data)
{
    storage_block_t *ptr = block.next;
    while (ptr->size < (sizeof(storage_item_t) + sizeof(storage_block_t)))
    {
        ptr = ptr->next;
        if (ptr == &block)
        {
            return FAILURE;
        }
    }

    /* dequeue free block */
    uint16_t tmp_size = ptr->size;
    ptr->prev->next = ptr->next;
    ptr->next->prev = ptr->prev;

    /* create new event item */
    storage_item_t *new_item = (storage_item_t *)ptr;
    new_item->next = &head;
    new_item->prev = head.prev;
    new_item->status = ITEM_DEFAULT;
    new_item->event = _data->event;
    new_item->checksum = item_checksum((storage_item_t *)ptr);
    head.prev->next = new_item;
    head.prev = new_item;

    /* enqueue new free block */
    *(storage_item_t **)(&ptr) += 1;
    ptr->next = &block;
    ptr->prev = block.prev;
    block.prev->next = ptr;
    block.prev = ptr;
    ptr->size = tmp_size - sizeof(storage_item_t);
    block.size -= sizeof(storage_item_t);

    return SUCCESS;
}

/**
    \brief Read data block from EEPROM

    Get item item[index] -> *item
*/
extern result_t storage_dequeue(storage_transport_t *const _data)
{
    if (head.next == &head)
    {
        return FAILURE;
    }

    /* store event data */
    _data->event = head.next->event;

    /* dequeue event item */
    storage_block_t *ptr = (storage_block_t *)head.next;
    head.next->next->prev = &head;
    head.next = head.next->next;

    /* enqueue new free block*/
    ptr->next = &block;
    ptr->prev = block.prev;
    block.prev->next = ptr;
    block.prev = ptr;
    ptr->size = sizeof(storage_item_t);
    block.size += sizeof(storage_item_t);

    return SUCCESS;
}

/**
    \brief Select items
*/
extern result_t storage_select_all(void)
{
    storage_item_t *ptr = head.next;
    select_index = 0;
    select_max = 0;
    while (ptr != &head)
    {
        ptr->status = ITEM_SELECTED;
        select_max++;
        ptr = ptr->next;
    }

    if (select_max > 0)
    {
        select_max--; /* attention: not a number of values, max value */
        return SUCCESS;
    }

    return FAILURE;
}

/**
    \brief Search for first selected item, deselect and return
*/
extern result_t storage_get_selected(storage_transport_t *const _data)
{
    storage_item_t *ptr = head.next;
    while (ptr != &head)
    {
        if (ptr->status == ITEM_SELECTED)
        {
            _data->event = ptr->event;
            _data->index = select_index;
            _data->max = select_max;

            select_index++;
            ptr->status = ITEM_DEFAULT;

            return SUCCESS;
        }
        ptr = ptr->next;
    }

    return FAILURE;
}

/**
    \brief Calculate and store item checksum
*/
static uint32_t item_checksum(storage_item_t const *const _item)
{
    assert(_item != NULL); // store item to EEPROM item null

    chunk_t chunk = {(uint8_t *)_item, sizeof(storage_item_t) - sizeof(uint32_t)};
    return checksum_hash(&chunk);
}
