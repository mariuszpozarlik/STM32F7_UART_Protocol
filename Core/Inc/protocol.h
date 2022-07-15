#ifndef INC_PROTOCOL_H_
#define INC_PROTOCOL_H_

#include <inttypes.h>

#define true 1
#define false 0
#define COMMAND_LEN 10
#define RX_BUFF_SIZE 19

typedef struct
{
	volatile uint8_t RX_Buffer[RX_BUFF_SIZE]; // = { '\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0'  };
	volatile uint8_t RX_Buff_Idx; // = 0;
	volatile uint8_t RX_Frame_Cplt; // = 0;
	uint8_t c;
}RX_buffer_t;

typedef struct frame
{
	uint8_t frameOK;
	uint8_t src_address;
	uint8_t dst_address;
	uint8_t data_count;
	uint8_t command[COMMAND_LEN];
	uint8_t checksum;
}framecontent;

extern RX_buffer_t RX;

void RXbufferClear(uint8_t* buff, int size);
framecontent prarseRxBuffer();

#endif /* INC_PROTOCOL_H_ */
