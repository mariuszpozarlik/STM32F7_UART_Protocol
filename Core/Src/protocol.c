#include "protocol.h"
#include "stdlib.h"

RX_buffer_t RX;

void RXbufferClear(uint8_t* buff, int size) //memset
{
	while (size)
	{
		*buff = '\0';
		size--;
		buff++;
	}
}

//zakładamy, że bufor zawiera docelową ramkę to przeparsowania, wstępnie sprawdzoną pod kątem
//wystepowania znaków $ oraz #, tzn ramka posiada prawidłowy format: $_________#
//              "$       5            7             05                    12345         255             #
//               ^       ^            ^             ^                     ^             ^               ^
//      znak poczatku,  adres zroda,  adres celu,  ilość danych w ramce,  dane ramki, suma konrolna   znak konca ramki
framecontent prarseRxBuffer()
{
	framecontent RxFrame;
	uint8_t l_checksum = 0;
	uint8_t tempstring[COMMAND_LEN] = "";
	RxFrame.frameOK = false;
	if(*RX.RX_Buffer == '$')
	{
		RxFrame.src_address = RX.RX_Buffer[1] - 48;
		RxFrame.dst_address = RX.RX_Buffer[2] - 48;
		memcpy(tempstring, (const char*)&RX.RX_Buffer[3], 2);
		RxFrame.data_count = atoi((const char*)tempstring);
		if(RxFrame.data_count <= 10)
		{
			RXbufferClear(tempstring, COMMAND_LEN);
			RXbufferClear(RxFrame.command, COMMAND_LEN);
			memcpy(RxFrame.command, (const char*)&RX.RX_Buffer[5], RxFrame.data_count);
			memcpy(tempstring, (const char*)&RX.RX_Buffer[5] + RxFrame.data_count, 3);
			RxFrame.checksum = atoi((const char*)tempstring);
			for (int offset = 0; offset < RxFrame.data_count; ++offset)
			{
				l_checksum += RX.RX_Buffer[5 + offset];
			}
			if (l_checksum == RxFrame.checksum)
			{
				RxFrame.frameOK = true;
			}
		}
	}
	RX.RX_Frame_Cplt = 0;
	return RxFrame;
}
