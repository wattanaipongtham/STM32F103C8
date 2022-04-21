#include <stdio.h>
#include <stdint.h>
#include <ctype.h>
#include "stm32f10x.h"
#include "wattanai_stm32f103c8_uart1.h"
#include "wattanai_stm32f103c8_clock_config.h"

/*=============================SIM800L COMMAND=============================*/
char AT_CMD[4] 				= "AT\r\n";
char AT_CIPSHUT[12] 	= "AT+CIPSHUT\r\n";
char AT_CFUN[11]			=	"AT+CFUN=1\r\n";
char AT_CGATT[12]			=	"AT+CGATT=1\r\n";
char AT_CPIN[10]			=	"AT+CPIN?\r\n";
char AT_CSTT[34] 			= "AT+CSTT=\"internet\",\"true\",\"true\"\r\n";
char AT_CIICR[10] 		= "AT+CIICR\r\n";
char AT_CIFSR[10] 		= "AT+CIFSR\r\n";
char AT_CIPSTART[43] 	= "AT+CIPSTART=\"TCP\",\"167.71.217.190\",\"1883\"\r\n";
char AT_CIPSEND[12] 	=	"AT+CIPSEND\r\n";
/*=========================================================================*/


/*=============================RESPONSE BUFFER=============================*/
char RES_CMD[50];
char RES_CIPSHUT[50];
char RES_CFUN[50];
char RES_CGATT[50];
char RES_CPIN[50];
char RES_CSTT[50];
char RES_CIICR[50];
char RES_CIFSR[50];
char RES_CIPSTART[50];
char RES_CIPSTART2[50];
char RES_CIPSEND[50];
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
				if(RES_CMD[2] == 'O' && RES_CMD[3] == 'K')
				{
					count = count + 1;
					DMA1_channel5_init((uint32_t) RES_CIPSHUT, (uint32_t) &USART1->DR, 50);
					DMA1_channel4_init((uint32_t) AT_CIPSHUT, (uint32_t) &USART1->DR, 12);
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
				if(RES_CIPSHUT[7] == 'O' && RES_CIPSHUT[8] == 'K')
				{
					count = count + 1;
					DMA1_channel5_init((uint32_t) RES_CGATT, (uint32_t) &USART1->DR, 50);
					DMA1_channel4_init((uint32_t) AT_CGATT, (uint32_t) &USART1->DR, 12);
				}else
				{
					DMA1_channel5_init((uint32_t) RES_CIPSHUT, (uint32_t) &USART1->DR, 50);
					DMA1_channel4_init((uint32_t) AT_CIPSHUT, (uint32_t) &USART1->DR, 12);
				}
				break;
			case 2:
				tmpreg = USART1->SR;
				(void) tmpreg;
				tmpreg = USART1->DR;
				(void) tmpreg;
				if(RES_CGATT[2] == 'O' && RES_CGATT[3] == 'K')
				{
					count = count + 1;
					DMA1_channel5_init((uint32_t) RES_CFUN, (uint32_t) &USART1->DR, 50);
					DMA1_channel4_init((uint32_t) AT_CFUN, (uint32_t) &USART1->DR, 11);
				}else
				{
					DMA1_channel5_init((uint32_t) RES_CGATT, (uint32_t) &USART1->DR, 50);
					DMA1_channel4_init((uint32_t) AT_CGATT, (uint32_t) &USART1->DR, 12);
				}
				break;
			case 3:
				tmpreg = USART1->SR;
				(void) tmpreg;
				tmpreg = USART1->DR;
				(void) tmpreg;
				if(RES_CFUN[2] == 'O' && RES_CFUN[3] == 'K')
				{
					count = count + 1;
					DMA1_channel5_init((uint32_t) RES_CPIN, (uint32_t) &USART1->DR, 50);
					DMA1_channel4_init((uint32_t) AT_CPIN, (uint32_t) &USART1->DR, 10);
				}else
				{
					DMA1_channel5_init((uint32_t) RES_CFUN, (uint32_t) &USART1->DR, 50);
					DMA1_channel4_init((uint32_t) AT_CFUN, (uint32_t) &USART1->DR, 11);
				}
				break;
			case 4:
				tmpreg = USART1->SR;
				(void) tmpreg;
				tmpreg = USART1->DR;
				(void) tmpreg;
				if(RES_CPIN[9] == 'R' && RES_CPIN[10] == 'E' && RES_CPIN[11] == 'A' && RES_CPIN[12] == 'D' && RES_CPIN[13] == 'Y')
				{
					count = count + 1;
					DMA1_channel5_init((uint32_t) RES_CSTT, (uint32_t) &USART1->DR, 50);
					DMA1_channel4_init((uint32_t) AT_CSTT, (uint32_t) &USART1->DR, 34);
				}else
				{
					DMA1_channel5_init((uint32_t) RES_CPIN, (uint32_t) &USART1->DR, 50);
					DMA1_channel4_init((uint32_t) AT_CPIN, (uint32_t) &USART1->DR, 10);
				}
				break;
			case 5:
				tmpreg = USART1->SR;
				(void) tmpreg;
				tmpreg = USART1->DR;
				(void) tmpreg;
				if(RES_CSTT[2] == 'O' && RES_CSTT[3] == 'K')
				{
					count = count + 1;
					DMA1_channel5_init((uint32_t) RES_CIICR, (uint32_t) &USART1->DR, 50);
					DMA1_channel4_init((uint32_t) AT_CIICR, (uint32_t) &USART1->DR, 10);
				}else
				{
					DMA1_channel5_init((uint32_t) RES_CSTT, (uint32_t) &USART1->DR, 50);
					DMA1_channel4_init((uint32_t) AT_CSTT, (uint32_t) &USART1->DR, 34);
				}
				break;
			case 6:
				tmpreg = USART1->SR;
				(void) tmpreg;
				tmpreg = USART1->DR;
				(void) tmpreg;
				if(RES_CIICR[2] == 'O' && RES_CIICR[3] == 'K')
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
			case 7:
				tmpreg = USART1->SR;
				(void) tmpreg;
				tmpreg = USART1->DR;
				(void) tmpreg;
				if(isdigit(RES_CIFSR[2]) && isdigit(RES_CIFSR[3]))
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
			case 8:
				tmpreg = USART1->SR;
				(void) tmpreg;
				tmpreg = USART1->DR;
				(void) tmpreg;
				if(RES_CIPSTART[2] == 'O' && RES_CIPSTART[3] == 'K')
				{
					count = count + 1;
				}else
				{
					
				}
				break;
			case 9:
				tmpreg = USART1->SR;
				(void) tmpreg;
				tmpreg = USART1->DR;
				(void) tmpreg;
				if((RES_CIPSTART2[10] == 'O' && RES_CIPSTART2[11] == 'K') || (RES_CIPSTART[16] == 'O' && RES_CIPSTART[17] == 'K'))
				{
					count = count + 1;
					DMA1_channel5_init((uint32_t) RES_CIPSEND, (uint32_t) &USART1->DR, 50);
					DMA1_channel4_init((uint32_t) AT_CIPSEND, (uint32_t) &USART1->DR, 12);
				}else
				{
					//DMA1_channel5_init((uint32_t) RES_CIPSTART, (uint32_t) &USART1->DR, 50);
					//DMA1_channel4_init((uint32_t) AT_CIPSTART, (uint32_t) &USART1->DR, 10);
				}
				break;
			default :
				tmpreg = USART1->SR;
				(void) tmpreg;
				tmpreg = USART1->DR;
				(void) tmpreg;
				break;
		}
	}
}
