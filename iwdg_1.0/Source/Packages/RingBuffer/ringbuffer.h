/***
和原版完全一致，只不过加了#include "stm32f1xx.h"
另外还有***以下，我自己找的反正原版没有***
#include "stdio.h"
#include "string.h"

#define RTM_EXPORT(symbol)

#define RT_ASSERT(EX)                                                         \
if (!(EX))                                                                    \
{                                                                             \
    printf("(%s) assertion failed at function:%s, line number:%d \n",#EX, __FUNCTION__, __LINE__);                           \
}

#define RT_ALIGN_DOWN(size, align)      ((size) & ~((align) - 1))
#define RT_ALIGN_SIZE 4
***/


/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */
#ifndef RINGBUFFER_H__
#define RINGBUFFER_H__

#ifdef __cplusplus
extern "C" {
#endif

/***以下为原版，补全代码***/
//#include <rtthread.h>
/***以上为原版，补全代码***/

/*********以下为添加的代码*********/
#include "stm32f1xx.h"							//头文件支持			
/*********以上为添加的代码*********/

/***以下，我自己找的反正原版没有***/
//?????????????????????????????????
#include "stdio.h"
#include "string.h"

#define RTM_EXPORT(symbol)

#define RT_ASSERT(EX)                                                         \
if (!(EX))                                                                    \
{                                                                             \
    printf("(%s) assertion failed at function:%s, line number:%d \n",#EX, __FUNCTION__, __LINE__);                           \
}

#define RT_ALIGN_DOWN(size, align)      ((size) & ~((align) - 1))
#define RT_ALIGN_SIZE 4
//?????????????????????????????????
/***以上，我自己找的反正原版没有***/

/* ring buffer */
struct rt_ringbuffer
{
    uint8_t *buffer_ptr;
    /* use the msb of the {read,write}_index as mirror bit. You can see this as
     * if the buffer adds a virtual mirror and the pointers point either to the
     * normal or to the mirrored buffer. If the write_index has the same value
     * with the read_index, but in a different mirror, the buffer is full.
     * While if the write_index and the read_index are the same and within the
     * same mirror, the buffer is empty. The ASCII art of the ringbuffer is:
     *
     *          mirror = 0                    mirror = 1
     * +---+---+---+---+---+---+---+|+~~~+~~~+~~~+~~~+~~~+~~~+~~~+
     * | 0 | 1 | 2 | 3 | 4 | 5 | 6 ||| 0 | 1 | 2 | 3 | 4 | 5 | 6 | Full
     * +---+---+---+---+---+---+---+|+~~~+~~~+~~~+~~~+~~~+~~~+~~~+
     *  read_idx-^                   write_idx-^
     *
     * +---+---+---+---+---+---+---+|+~~~+~~~+~~~+~~~+~~~+~~~+~~~+
     * | 0 | 1 | 2 | 3 | 4 | 5 | 6 ||| 0 | 1 | 2 | 3 | 4 | 5 | 6 | Empty
     * +---+---+---+---+---+---+---+|+~~~+~~~+~~~+~~~+~~~+~~~+~~~+
     * read_idx-^ ^-write_idx
     *
     * The tradeoff is we could only use 32KiB of buffer for 16 bit of index.
     * But it should be enough for most of the cases.
     *
     * Ref: http://en.wikipedia.org/wiki/Circular_buffer#Mirroring */
    uint16_t read_mirror : 1;
    uint16_t read_index : 15;
    uint16_t write_mirror : 1;
    uint16_t write_index : 15;
    /* as we use msb of index as mirror bit, the size should be signed and
     * could only be positive. */
    uint16_t buffer_size;
};

enum rt_ringbuffer_state
{
    RT_RINGBUFFER_EMPTY,
    RT_RINGBUFFER_FULL,
    /* half full is neither full nor empty */
    RT_RINGBUFFER_HALFFULL,
};

/**
 * RingBuffer for DeviceDriver
 *
 * Please note that the ring buffer implementation of RT-Thread
 * has no thread wait or resume feature.
 */
void rt_ringbuffer_init(struct rt_ringbuffer *rb, uint8_t *pool, uint16_t size);						//使用。环形队列初始化
void rt_ringbuffer_reset(struct rt_ringbuffer *rb);
unsigned long rt_ringbuffer_put(struct rt_ringbuffer *rb, const uint8_t *ptr, uint16_t length);			//使用。将数据放入队列
unsigned long rt_ringbuffer_put_force(struct rt_ringbuffer *rb, const uint8_t *ptr, uint16_t length);
unsigned long rt_ringbuffer_putchar(struct rt_ringbuffer *rb, const uint8_t ch);
unsigned long rt_ringbuffer_putchar_force(struct rt_ringbuffer *rb, const uint8_t ch);
unsigned long rt_ringbuffer_get(struct rt_ringbuffer *rb, uint8_t *ptr, uint16_t length);				//使用。取数据
unsigned long rt_ringbuffer_getchar(struct rt_ringbuffer *rb, uint8_t *ch);
unsigned long rt_ringbuffer_data_len(struct rt_ringbuffer *rb);																  //使用。判断当前队列中是否有数据（得到大小，即不为零是有数据）

/***以下为原版，补全代码***/
//#ifdef RT_USING_HEAP
//struct rt_ringbuffer* rt_ringbuffer_create(rt_uint16_t length);
//void rt_ringbuffer_destroy(struct rt_ringbuffer *rb);
//#endif
/***以上为原版，补全代码***/

static __inline uint16_t rt_ringbuffer_get_size(struct rt_ringbuffer *rb)								
{
    RT_ASSERT(rb != NULL);
    return rb->buffer_size;
}

/** return the size of empty space in rb */
#define rt_ringbuffer_space_len(rb) ((rb)->buffer_size - rt_ringbuffer_data_len(rb))


#ifdef __cplusplus
}
#endif

#endif
