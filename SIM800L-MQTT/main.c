#include <stdio.h>
#include <stdint.h>
#include <ctype.h>
#include "stm32f10x.h"
#include "wattanai_stm32f103c8_uart1.h"
#include "wattanai_stm32f103c8_clock_config.h"

/*=============================SIM800L COMMAND=============================*/
char AT_CMD[4] 				= "AT\r\n";
char AT_CSTT[41] 			= "AT+CSTT=\"TRUE-H INTERNET\",\"true\",\"true\"\r\n";
char AT_CIICR[10] 		= "AT+CIICR\r\n";
char AT_CIFSR[10] 		= "AT+CIFSR\r\n";
char AT_CIPSTART[43] 	= "AT+CIPSTART=\"TCP\",\"167.71.217.190\",\"1883\"\r\n";
/*=========================================================================*/


/*=============================RESPONSE BUFFER=============================*/
char RES_CMD[50];
char RES_CSTT[50];
char RES_CIICR[50];
char RES_CIFSR[50];
char RES_CIPSTART[50];
/*=========================================================================*/
int count=0;
__IO uint32_t tmpreg;
int main()
{
	system_clock_config();
	uart1_rx_Init();
	uart1_tx_Init();
	NVIC_EnableIRQ(USART1_IRQn);
	DMA1_channel5_init((uint32_t) RES_CMD, (uint32_t) &USART1->DR, 50);
	DMA1_channel4_init((uint32_t) AT_CMD, (uint32_t) &USART1->DR, 4);
	while(1)
	{
	
	}
}

void USART1_IRQHandler(void)
{
	if(USART1->SR & (1U<<4) && USART1->CR1 & (1U<<4)){
		switch(count){
			case 0:
				tmpreg = USART1->SR;
				(void) tmpreg;
				tmpreg = USART1->DR;
				(void) tmpreg;
				if(RES_CMD[0] == 'O' && RES_CMD[1] == 'K')
				{
					count = count + 1;
					DMA1_channel5_init((uint32_t) RES_CSTT, (uint32_t) &USART1->DR, 50);
					DMA1_channel4_init((uint32_t) AT_CSTT, (uint32_t) &USART1->DR, 41);
				}else
				{
					DMA1_channel5_init((uint32_t) RES_CMD, (uint32_t) &USART1->DR, 50);
					DMA1_channel4_init((uint32_t) AT_CMD, (uint32_t) &USART1->DR, 4);
				}
				break;
			case 1:
				tmpreg = USART1->SR;
				(void) tmpreg;
				tmpreg = USART1->DR;
				(void) tmpreg;
				if(RES_CSTT[0] == 'O' && RES_CSTT[1] == 'K')
				{
					count = count + 1;
					DMA1_channel5_init((uint32_t) RES_CIICR, (uint32_t) &USART1->DR, 50);
					DMA1_channel4_init((uint32_t) AT_CIICR, (uint32_t) &USART1->DR, 10);
				}else
				{
					DMA1_channel5_init((uint32_t) RES_CSTT, (uint32_t) &USART1->DR, 50);
					DMA1_channel4_init((uint32_t) AT_CSTT, (uint32_t) &USART1->DR, 41);
				}
				break;
			case 2:
				tmpreg = USART1->SR;
				(void) tmpreg;
				tmpreg = USART1->DR;
				(void) tmpreg;
				if(RES_CIICR[0] == 'O' && RES_CIICR[1] == 'K')
				{
					count = count + 1;
					DMA1_channel5_init((uint32_t) RES_CIFSR, (uint32_t) &USART1->DR, 50);
					DMA1_channel4_init((uint32_t) AT_CIFSR, (uint32_t) &USART1->DR, 10);
				}else
				{
					DMA1_channel5_init((uint32_t) RES_CIICR, (uint32_t) &USART1->DR, 50);
					DMA1_channel4_init((uint32_t) AT_CIICR, (uint32_t) &USART1->DR, 10);
				}
				break;
			case 3:
				tmpreg = USART1->SR;
				(void) tmpreg;
				tmpreg = USART1->DR;
				(void) tmpreg;
				if(isdigit(RES_CIFSR[0]) && isdigit(RES_CIFSR[1]))
				{
					count = count + 1;
					DMA1_channel5_init((uint32_t) RES_CIPSTART, (uint32_t) &USART1->DR, 50);
					DMA1_channel4_init((uint32_t) AT_CIPSTART, (uint32_t) &USART1->DR, 43);
				}else
				{
					DMA1_channel5_init((uint32_t) RES_CIFSR, (uint32_t) &USART1->DR, 50);
					DMA1_channel4_init((uint32_t) AT_CIFSR, (uint32_t) &USART1->DR, 10);
				}
				break;
			case 4:
				tmpreg = USART1->SR;
				(void) tmpreg;
				tmpreg = USART1->DR;
				(void) tmpreg;
				count = count + 1;
				break;
			case 5:
				tmpreg = USART1->SR;
				(void) tmpreg;
				tmpreg = USART1->DR;
				(void) tmpreg;
				count = count + 1;
				break;
			default :
				tmpreg = USART1->SR;
				(void) tmpreg;
				tmpreg = USART1->DR;
				(void) tmpreg;
				count = count + 1;
				break;
		}
	}
}
