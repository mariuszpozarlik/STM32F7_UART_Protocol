//#include "pch.h"
#include <inttypes.h>
#include "ringbuff.h"
#include "stdlib.h"

uint32_t getLastElement(buffer_t* buff)
{
	uint32_t ret = 0;
	if (buff->flags.clr_flag == BUFF_NOT_EMPTY)
	{
		ret = *buff->begin_handler;
	}
	return ret;
}

uint32_t getOldestElement(buffer_t* buff)
{
	uint32_t ret = 0;
	if (buff->flags.clr_flag == BUFF_NOT_EMPTY)
	{
		ret = *buff->end_handler;
	}
	return ret;
}

uint32_t getElementByIdx(buffer_t* buff, uint16_t idx)
{
	uint32_t ret = 0;
	uint32_t temp_adr = 0;
	if (idx < RING_BUF_SIZE &&
		buff->flags.clr_flag == BUFF_NOT_EMPTY)
	{
		if ((buff->end_handler + idx) >= (buff->elements + RING_BUF_SIZE))
		{
			temp_adr = (uint32_t)(buff->end_handler + idx) % (uint32_t)(buff->elements + RING_BUF_SIZE - 1);
			ret = *(uint32_t*)(buff->elements + (temp_adr / 4) - 1);
		}
		else
		{
			ret = *(buff->end_handler + idx);
		}
	}
	return ret;
}


void bufferAddElement(buffer_t* buff, uint32_t element)
{
	if (BUFF_NOT_OVF == buff->flags.buffer_overflow_flag)
	{
		if (BUFF_EMPTY == buff->flags.clr_flag)
		{
			*(buff->begin_handler) = element;
			buff->flags.clr_flag = BUFF_NOT_EMPTY;
		}
		else
		{
			buff->begin_handler++;
			*(buff->begin_handler) = element;
			if (buff->begin_handler >= buff->elements + (RING_BUF_SIZE - 1))
			{
				buff->flags.buffer_overflow_flag = BUFF_OVF;
			}
		}
	}
	else
	{
		buff->end_handler++;
		buff->begin_handler++;
		if (buff->begin_handler >= buff->elements + (RING_BUF_SIZE))
		{
			buff->begin_handler = buff->elements;
		}
		if (buff->end_handler >= buff->elements + (RING_BUF_SIZE))
		{
			buff->end_handler = buff->elements;
		}
		*(buff->begin_handler) = element;
	}
}

uint8_t bufferInit(buffer_t* buff)
{
	uint8_t ret = NOK;

	buff->flags.clr_flag = BUFF_NOT_EMPTY;
	buff->flags.buffer_overflow_flag = BUFF_NOT_OVF;
	if (OK == bufferClear(buff))
	{
		buff->begin_handler = buff->elements;
		buff->end_handler = buff->elements;

		ret = OK;
	}

	return ret;
}

uint8_t bufferClear(buffer_t* buff)
{
	uint8_t ret = NOK;
	if (BUFF_NOT_EMPTY == buff->flags.clr_flag)
	{
		uint16_t idx = 0;
		for (idx = 0; idx < RING_BUF_SIZE; ++idx)
		{
			buff->elements[idx] = 0;
		}
		buff->begin_handler = NULL;
		buff->end_handler = NULL;

		buff->flags.clr_flag = BUFF_EMPTY;

		ret = OK;
	}

	return ret;
}
