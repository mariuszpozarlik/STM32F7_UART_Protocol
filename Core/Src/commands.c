/*
 * commands.c
 *
 *  Created on: Feb 26, 2022
 *      Author: Adrian
 */

#include "commands.h"
#include <string.h>
#include <stdlib.h>

command_t commands(uint8_t* command, buffer_t* measbuff)
{
	command_t comm = {"", 0};

	if(strcmp(command, "D1") == 0)
	{
		itoa(getOldestElement(measbuff),  comm.TX_payload, COMM_LEN);
		comm.len = (uint16_t)strlen(comm.TX_payload);
	}
	else if(strcmp(command, "D2") == 0)
	{
		itoa(getLastElement(measbuff), comm.TX_payload, COMM_LEN);
		comm.len = (uint16_t)strlen(comm.TX_payload);
	}
	else if(command[0] == 'I')
	{
		itoa(getElementByIdx(measbuff, atoi(command+1)), comm.TX_payload, COMM_LEN);
		comm.len = (uint16_t)strlen(comm.TX_payload);
	}
	else if(strcmp(command, "CLR") == 0)
	{
		bufferClear(measbuff);
		comm.len = (uint16_t)strlen("cleared");
		memcpy(comm.TX_payload, "cleared", comm.len);
	}
	else
	{
		comm.len = (uint16_t)strlen("unknown");
		memcpy(comm.TX_payload, "unknown", comm.len);
	}

	return comm;
}

