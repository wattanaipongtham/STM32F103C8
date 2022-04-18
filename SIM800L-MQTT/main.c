#include <stdio.h>
#include <stdint.h>
#include "stm32f10x.h"
#include "wattanai_stm32f103c8_uart1.h"
#include "wattanai_stm32f103c8_clock_config.h"

/*=============================SIM800L COMMAND=============================*/
char AT_CMD[4] 				= "AT\r\n";
char AT_CSTT[41] 			= "AT+CSTT=\"TRUE-H INTERNET\",\"true\",\"true\"\r\n";
char AT_CIICR[10] 		= "AT+CIICR\r\n";
char AT_CIFSR[10] 		= "AT+CIFSR\r\n";
char AT_CIPSTART[31] 	= "\"TCP\",\"167.71.217.190\",\"1883\"\r\n";
/*=========================================================================*/


/*=============================RESPONSE BUFFER=============================*/
char RES_CMD[50];
char RES_CSTT[50];
char RES_CIICR[50];
char RES_CIFSR[50];
char RES_CIPSTART[50];
/*=========================================================================*/
int i=0;

int main()
{
	system_clock_config();
	RCC->APB2ENR	|=	(1U<<4);
	GPIOC->CRH		|=	(0x44744444UL);
	GPIOC->ODR		&=	~(0x0000UL);
	
	uart1_tx_Init();
	uart1_rx_Init();
	DMA1_channel5_init((uint32_t) RES_CMD, (uint32_t) &USART1->DR, 4);
	DMA1_channel4_init((uint32_t) AT_CMD, (uint32_t) &USART1->DR, 4);
	while(1)
	{
	
	}
}

void USART1_IRQHandler(void)
{
	GPIOC->ODR		|=	(0x2000UL);
}

void DMA1_Channel4_IRQHandler(void)
{
	/*if(DMA1->ISR & (1U<<13))
	{
		DMA1->IFCR |= (1U<<13);
	}*/
}

void DMA1_Channel5_IRQHandler(void)
{
	/*if(DMA1->ISR & (1U<<17))
	{
		DMA1->IFCR |= (1U<<17);
	}*/
}
