/* USER CODE BEGIN Header */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "spi.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include <string.h>
#include <stdlib.h>
#include "ringbuff.h"
#include "protocol.h"
#include "commands.h"
#include "stdarg.h"
#include "string.h"
#include <ctype.h>
#include <stdio.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
#define USART_TXBUF_LEN 300 //wielkość bufora nadawczego
#define USART_RXBUF_LEN 300 //wielkość bufore odbiorczego
#define BUF_ARCHIVE_LEN 3000 //wielkość bufore archiwum
uint8_t USART_TxBuf[USART_TXBUF_LEN];//tablica bufora nadawczego
uint8_t USART_RxBuf [USART_RXBUF_LEN];//tablica bufora odbiorczego
uint8_t BUF_Arch[BUF_ARCHIVE_LEN]; //tablica bufora archiwum

__IO int USART_TX_Empty = 0;
__IO int USART_TX_Busy = 0;
__IO int USART_RX_Empty = 0;
__IO int USART_RX_Busy = 0;
__IO int BUF_ARCH_Empty = 0;

uint8_t buffer[USART_RXBUF_LEN]; // tablica pomocnicza używana przy odczytywaniu ramki
uint8_t frameState = 0;
                        				// 0 - czekamy na początek ramki
										// 1 - ramka jest przetwarzana

const char device_address[3] = "STM";
char src_address[4];
uint8_t frameLen = 0; //ilość odebranych znaków w ramce
int commLength; // długość komendy

//bufor spi
int numbers[500];
uint8_t rxspibuf[500];
uint8_t txspibuf[500];

struct register_{
	uint8_t ONE_REG;
	uint8_t TWO_REG;
	uint8_t THREE_REG;
	uint8_t FOUR_REG;
	uint8_t FIVE_REG;
	uint8_t SIX_REG;
	uint8_t SEVEN_REG;
	uint8_t EIGHT_REG;
	uint8_t NINE_REG;
	uint8_t TEN_REG;
	uint8_t ELEVEN_REG;
	uint8_t TWELVE_REG;
	uint8_t THIRTEEN_REG;
	uint8_t FOURTEEN_REG;
	uint8_t FIFTEEN_REG;
	uint8_t SIXTEEN_REG;
};

struct register_ reg = {0};
uint32_t* regBaseAddr = (uint32_t*)&reg;
uint8_t regOffset = 1;

void set_reg(uint8_t reg_num, uint8_t value)
{
	if(reg_num<=16)
		*((uint8_t*)((uint32_t)regBaseAddr+(reg_num-1))) = value;
}

uint8_t SPI_Read_reg(uint8_t reg_num)
{
	uint8_t temp=0;

	HAL_SPI_Transmit(&hspi3, ((uint8_t*)((uint32_t)regBaseAddr+(reg_num-1))), 1, 100);
	HAL_SPI_Receive(&hspi1, &temp, 1, 100);
	return temp;
}

void SPI_Write_reg(uint8_t reg_num, int16_t value, uint8_t pos)
{
	uint8_t temp = 0;
	HAL_SPI_Transmit(&hspi1, &temp, 1, 100);
	HAL_SPI_Receive(&hspi3, rxspibuf, 5, 100); // flush SPI

	temp = SPI_Read_reg(reg_num);
	if(value > 0)
		temp |= value << pos;
	else if(value == 0)
		temp &= ~(1 << pos);
	else if(value == -1)
		temp = 0;

	HAL_SPI_Transmit(&hspi1, &temp, 1, 10);
	HAL_SPI_Receive(&hspi3, rxspibuf, 1, 10);
	HAL_SPI_Receive(&hspi3, rxspibuf, 1, 10);
	set_reg(reg_num, *rxspibuf);
}


//ODBIÓR
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart){ // funkcja jest wywoływana gdy jest w trybie przerwań
	if(huart==&huart2){ // jeśli pojawia się przerwanie
		if (USART_TX_Empty!=USART_TX_Busy){
			uint8_t tmp=USART_TxBuf[USART_TX_Busy]; //pobieranie znaku z bufora
			USART_TX_Busy++; //korygowanie wskaznika
			if (USART_TX_Busy>=USART_TXBUF_LEN)USART_TX_Busy=0;
			HAL_UART_Transmit_IT(&huart2, &tmp, 1); //wysyłanie kolejnego bajtu 'danych'
		}
	}
}


//NADAWANIE
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	if(huart==&huart2){ // jeśli przerwanie nastąpiło to został odebrany znak
		USART_RX_Empty++;
        if (USART_RX_Empty>=USART_RXBUF_LEN)USART_RX_Empty=0;
        HAL_UART_Receive_IT(&huart2, &USART_RxBuf[USART_RX_Empty], 1); //wywołanie funkcji HAL_UART_Receive, aby odebrała kolejny znak
	}
}


//WYSY�?ANIE
void USART_fsend(char* format, ...) {

	char tmp_rs[300];

	__IO int idx;
	va_list valist;
	va_start(valist, format);
	vsprintf(tmp_rs, format, valist); //wyświetlanie stringa z wprowadzonych danych
	va_end(valist);
	idx = USART_TX_Empty;
	for (int i = 0; i < strlen(tmp_rs); i++) {
		USART_TxBuf[idx] = tmp_rs[i]; //przekazywanie po kolei znaków do naszege bufora
		idx++;
		if (idx >= USART_TXBUF_LEN)
			idx = 0;
	}
	__disable_irq(); //wyłaczenie przerwań
	if ((USART_TX_Empty == USART_TX_Busy) && (__HAL_UART_GET_FLAG(&huart2, UART_FLAG_TXE) == SET)) {
		USART_TX_Empty = idx;
		uint8_t tmp = USART_TxBuf[USART_TX_Busy];
		USART_TX_Busy++;
		if (USART_TX_Busy >= USART_TXBUF_LEN)
			USART_TX_Busy = 0;
		HAL_UART_Transmit_IT(&huart2, &tmp, 1);
	} else {
		USART_TX_Empty = idx;
	}
	__enable_irq(); //włączenie przerwań

}


/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

void ErrorKomer() {

	USART_fsend(":%s%s005KOMER;\n\r", device_address, src_address);

}

void ErrorRamer() {

	USART_fsend(":%s%s005RAMER;\n\r", device_address, src_address);

}

void ErrorNull() {

	USART_fsend(":%s%s006NULLER;\n\r", device_address, src_address);

}

void ErrorMax() {

	USART_fsend(":%s%s005MAXER;\n\r", device_address, src_address);

}



void AnalyzeCmd(char *cmd) {

	if(!strncmp(cmd, "WREG", 4)){
		USART_fsend(":%s%s005HELLO;\n\r", device_address, src_address);
		USART_fsend(":%s%s%s;\n\r", device_address, src_address, cmd);


	}else if(!strncmp(cmd, "RREG", 4)){
		USART_fsend(":%s%s005HELLO;\n\r", device_address, src_address);

	    int number_count = 0;

	    for (int i = 0; i < commLength; ++i) // policzmy ile jest liczb w komendzie
	        if (cmd[i] == 'x')
	            ++number_count;

	    //int* numbers = (int*)malloc(number_count * sizeof(int));
	    int index = 0;

	    char* number_str = strtok(cmd, "|"); // podzielmy na tokeny po "|" i bierzemy pierwszy
	    while (number_str) {
	        if (number_str[0] == '0' && number_str[1] == 'x') { // jeśli to szesnastkowy literał
	            numbers[index++] = strtoul(&number_str[2], NULL, 16); // przekonwertujmy go na dzisiętny i dodajmy do tablicy
	        }
	        number_str = strtok(NULL, "|"); // bierzemy kolejny token
	    }

		    //int ilosc = strlen(numbers);
		    //strncpy(txspibuf, numbers, number_count);
		    //int iloscbuf = strlen(txspibuf);
		    //HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET);
		    //HAL_SPI_Transmit(&hspi1, txspibuf, iloscbuf, 100);
		    //HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET);

		    for (int i = 0; i < number_count; ++i){
		        USART_fsend("0x%02x \n\r", numbers[i]);
		    }

		    //USART_fsend(":%s%s009WRITEBYTE;\n\r", device_address, src_address);

		    //for (int i = 0; i < iloscbuf; i++){
		    //    USART_fsend("0x%02x \n\r", txspibuf[i]);
		    //}

	}else if(!strncmp(cmd, "WBA", 3)){
		USART_fsend(":%s%s005HELLO;\n\r", device_address, src_address);

	    int number_count = 0;

	    for (int i = 0; i < commLength; ++i) // policzmy ile jest liczb w komendzie
	        if (cmd[i] == 'x')
	            ++number_count;

	    //int* numbers = (int*)malloc(number_count * sizeof(int));
	    int index = 0;

	    char* number_str = strtok(cmd, "|"); // podzielmy na tokeny po "|" i bierzemy pierwszy
	    while (number_str) {
	        if (number_str[0] == '0' && number_str[1] == 'x') { // jeśli to szesnastkowy literał
	            numbers[index++] = strtoul(&number_str[2], NULL, 16); // przekonwertujmy go na dzisiętny i dodajmy do tablicy
	        }
	        number_str = strtok(NULL, "|"); // bierzemy kolejny token
	    }

		    //int ilosc = sizeof numbers / sizeof *numbers;
		    //strncpy(txspibuf, numbers, number_count);
		    //int iloscbuf = strlen(txspibuf);
		    //HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET);
		    //HAL_SPI_Transmit(&hspi1, txspibuf, iloscbuf, 100);
		    //HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET);

		    //USART_fsend("%d \n\r", ilosc);
		    for (int i = 0; i < number_count; ++i){
		        USART_fsend("0x%02x \n\r", numbers[i]);
		    }

		    //USART_fsend(":%s%s009WRITEBYTE;\n\r", device_address, src_address);

		    //for (int i = 0; i < iloscbuf; i++){
		    //    USART_fsend("0x%02x \n\r", txspibuf[i]);
		    //}



	}
	else{
		ErrorKomer();
	}

}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	buffer_t measbuff;
	framecontent myFrame;
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_SPI1_Init();
  MX_SPI3_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
  uint32_t value[3] = {0, 0, 0};
//  HAL_ADC_Start_DMA(&hadc1, value, 3);
//  HAL_TIM_Base_Start_IT(&htim1);
//  HAL_TIM_Base_Start_IT(&htim2);
//  HAL_TIM_Base_Start_IT(&htim3);
  bufferInit(&measbuff); //fill measurement buffer with dummy data
  for(uint32_t i = 0; i < RING_BUF_SIZE; ++i)
  {
	  bufferAddElement(&measbuff, (i+1234)*(i%1548));
  }
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

//  HAL_UART_Receive_IT(&huart3, (uint8_t*)&RX.c, 1);


//  HAL_SPI_Receive_DMA(&hspi3, rcv, 1);
//  HAL_SPI_Receive_DMA(&hspi1, temp, 1);

  HAL_UART_Receive_IT(&huart2, &USART_RxBuf[USART_RX_Empty], 1);
  while(1)
                                                   {

	uint8_t oneFrameChar; // pojedynczy znak pobrany z bufora odbiorczego

	if (USART_RX_Busy != USART_RX_Empty) { // rozpoczęcie poszukiwania ramki

	  oneFrameChar = USART_RxBuf[USART_RX_Busy]; // pobieranie pierwszego znaku

		USART_RX_Busy++;
		if (USART_RX_Busy >= USART_RXBUF_LEN) {
			USART_RX_Busy = 0;
		}

		if (oneFrameChar == 0x3A /* : */) { // jeżeli znaleziono znak początku ramki
				frameState = 1;
				frameLen = 0;
				continue;
		}

	  if(frameState == 1) { // jeżeli znak początku ramki został znaleziony

		buffer[frameLen] = oneFrameChar; // kolekcjonowanie ramki
		frameLen++;

		//256 - maksymalna ilość danych
		//9 - minimalna długość ramki
		//1 - znak końca ramki (jest pobierany przy zczytywaniu ramki z bufora odbiorczego)
		if(frameLen > (256 + 9 + 1)) { // jeżeli ilość znaków w ramce przekroczy dopuszczalny rozmiar ramki (266 znaków)
			frameLen = 0; // ramka jest resetowana
			frameState = 0; // i następuje poszukiwanie nowej ramki
		}


		if (oneFrameChar == 0x3B /* ; */) { // kolekcjonowanie do końca ramki

			if (frameLen - 1 > 9) { // jeżeli podano więcej znaków, niż minimalna ilość znaków w ramce
				char destination_address[4];
				char data_length[4];

				memcpy(src_address, &buffer[0], 3);
				memcpy(destination_address, &buffer[3], 3);
				memcpy(data_length, &buffer[6], 3);

				src_address[3] = 0;
				destination_address[3] = 0;
				data_length[3] = 0;

				commLength = atoi(data_length); // suma kontrolna, ale też długość danych

				if(!strncmp(device_address, ":", 1) || !strncmp(device_address, ";", 1) || !strncmp(destination_address, ":", 1) || !strncmp(destination_address, ";", 1)){
					ErrorRamer();
				}else{
					if (strncmp(device_address, destination_address, 3) == 0) {
						if (commLength <= 256) {


							if ((9 + commLength) == (frameLen - 1)) { // jeżeli komenda została przysłana
								char cmd[commLength + 1];

								memcpy(cmd, &buffer[9], commLength);
								cmd[commLength] = 0; // dodanie znaku null na końcu tablicy

								AnalyzeCmd(cmd); // wywołanie funkcji analizującej komendę

							} else ErrorRamer();

						} else ErrorRamer();

					 } else ErrorRamer();

				}

				} else ErrorRamer();

		frameState = 0; // reset ramki
		frameLen = 0;
		}
	}
	}

	uint8_t v = 0;
	SPI_Write_reg(1, 1, 0);
	SPI_Write_reg(1, 1, 1);
	SPI_Write_reg(1, 1, 7);
	SPI_Write_reg(2, 127, 0);
	SPI_Write_reg(8, 199, 0);
	SPI_Write_reg(15, 16, 0);
	SPI_Write_reg(16, 155, 0);
	v = SPI_Read_reg(2);
	SPI_Write_reg(2, 255, 0);
	v = SPI_Read_reg(2);
	SPI_Write_reg(2, -1, 0);
	v = SPI_Read_reg(1);
	v = SPI_Read_reg(2);
	v = SPI_Read_reg(8);
	v = SPI_Read_reg(15);
	v = SPI_Read_reg(16);
	int a = 0;
	a++;
  }
//	if (RX.RX_Frame_Cplt == 1) //nastapilo zakonczenie nadawania ramki
//	{
//		myFrame = prarseRxBuffer();
//		if(myFrame.frameOK)
//		{
//			command_t co = commands(myFrame.command, &measbuff);
//			HAL_UART_Transmit_IT(&huart3, co.TX_payload, co.len);
//			HAL_UART_Transmit_IT(&huart3, '/n', 1);
//		}
//		else
//		{
//			HAL_UART_Transmit_IT(&huart3, (const uint8_t*)"frame Error\n", strlen("frame Error\n"));
//		}
//	}
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure LSE Drive Capability
  */
  HAL_PWR_EnableBkUpAccess();

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 96;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Activate the Over-Drive mode
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
