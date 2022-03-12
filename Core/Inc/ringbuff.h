#ifndef __RINGBUFF_H__
#define __RINGBUFF_H__

#include <inttypes.h>

#define RING_BUF_SIZE 70
#define OK 1
#define NOK 0
#define BUFF_EMPTY 0
#define BUFF_NOT_EMPTY 1
#define BUFF_NOT_OVF 0
#define BUFF_OVF 1
//#define NULL (void*)0

typedef struct flags_t
{
	uint8_t clr_flag : 1;
	uint8_t buffer_overflow_flag : 1;
}flags_t;

typedef struct buffer_t {
	uint32_t* begin_handler;
	uint32_t* end_handler;
	uint32_t elements[RING_BUF_SIZE];
	flags_t flags;
} buffer_t;

uint8_t bufferInit(buffer_t* buff);
uint8_t bufferClear(buffer_t* buff);
void bufferAddElement(buffer_t* buff, uint32_t element);
uint32_t getLastElement(buffer_t* buff);
uint32_t getOldestElement(buffer_t* buff);
uint32_t getElementByIdx(buffer_t* buff, uint16_t idx);

#endif /*__RINGBUFF_H__*/
