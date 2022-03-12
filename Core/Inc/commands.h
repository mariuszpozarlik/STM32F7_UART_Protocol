/*
 * commands.h
 *
 *  Created on: Feb 26, 2022
 *      Author: Adrian
 */

#ifndef INC_COMMANDS_H_
#define INC_COMMANDS_H_

#include "ringbuff.h"

#define COMM_LEN 10

typedef struct command
{
	uint8_t TX_payload[100];
	uint16_t len;
}command_t;

command_t commands(uint8_t* command, buffer_t* measbuff);

#endif /* INC_COMMANDS_H_ */
