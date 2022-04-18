#include <stdio.h>
#include "stm32f10x.h"
#include "wattanai_stm32f103c8_uart1.h"
	
#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)

#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif

PUTCHAR_PROTOTYPE
{
	uart1_write(ch);
	return 0;
}

void uart1_tx_Init(void)
{
	/*Enable Alternate Function For Peripheral Pin*/
	RCC->APB2ENR	|=	(1U<<0);
	
	/*Enable IO Port A*/
	RCC->APB2ENR	|=	(1U<<2);
	
	/*Enable UART1*/
	RCC->APB2ENR |= 	(1U<<14);
	
	/*Set Port A Pin9 As Alternate Function Output PP 50MHz*/
	GPIOA->CRH		|=	0xB4;
	
	/*Set Buad Rate 9600*/
	USART1->BRR		|=	0x1D4C;
	
	/*Enable Transmitter*/
	USART1->CR1		|=	(1U<<3);
	
	/*Enable UART*/
	USART1->CR1		|=	(1U<<13);
}

void uart1_rx_Init(void)
{
	
	/*Enable IO Port A*/
	RCC->APB2ENR	|=	(1U<<2);
	
	/*Enable UART1*/
	RCC->APB2ENR |= 	(1U<<14);
	
	/*Set Port A Pin10 As Input Pull-up Pull-down*/
	GPIOA->CRH		|=	(1U<<10);
	
	/*Set Buad Rate 9600*/
	USART1->BRR		|=	0x1D4C;
	
	/*Enable IDLE Line*/
	USART1->CR1	|=	(1U<<4);
	
	/*Enable Receiver*/
	USART1->CR1		|=	(1U<<2);
	
	/*Enable UART*/
	USART1->CR1		|=	(1U<<13);
	
	NVIC_EnableIRQ(USART1_IRQn);
}

void uart1_write(int ch)
{
	/*Check That Transmit Data Register is Empty*/
	while(!(USART1->SR & (1U<<6)))
	{
		/*Wait*/
	}
		
	/*Write Data To Data Register*/
	USART1->DR		|=	(ch & 0xFF);
}

char uart1_read(void)
{
	while(!(USART1->SR & (1U<<5)))
	{
		/*Wait*/
	}
	return USART1->DR;
}

void DMA1_channel4_init(uint32_t src, uint32_t dst, uint32_t len)
{
	/*Enable Clock Access To DMA*/
	RCC->AHBENR		|=	(1U<<0);
	
	/*Disable DMA1 Channel4*/
	DMA1_Channel4->CCR	&= ~(1U<<0);
	
	/*Wait For DMA1 Channel4 is Disable*/
	while(DMA1_Channel4->CCR & (1U<<0)){}
		
	/*Clear All Interrupt Flags of Channel4*/
	DMA1->IFCR	|=	(1U<<12);
	DMA1->IFCR	|=	(1U<<13);
	DMA1->IFCR	|=	(1U<<14);
	DMA1->IFCR	|=	(1U<<15);
	
	/*Set the Destination Buffer*/
	DMA1_Channel4->CPAR		=	dst;
	
	/*Set the Source Buffer*/
	DMA1_Channel4->CMAR		=	src;
	
	/*Set Length*/
	DMA1_Channel4->CNDTR	=	len;
	
	/*Enable Memory Increment*/
	DMA1_Channel4->CCR	|=	(1U<<7);
	
	/*Configure Transfer Direction*/
	DMA1_Channel4->CCR	|=	(1U<<4);
	
	/*Enable DMA Transfer Complete Interrupt*/
	DMA1_Channel4->CCR	|=	(1U<<1);
	
	/*Enable DMA1 Channel4*/
	DMA1_Channel4->CCR	|=	(1U<<0);
	
	/*Enable UART1 Transmitter DMA*/
	USART1->CR3	|=	(1U<<7);
	
	/*DMA Interrupt Enable in NVIC*/
	NVIC_EnableIRQ(DMA1_Channel4_IRQn);
	
}

void DMA1_channel5_init(uint32_t src, uint32_t dst, uint32_t len)
{
	/*Enable Clock Access To DMA*/
	RCC->AHBENR		|=	(1U<<0);
	
	/*Disable DMA1 Channel5*/
	DMA1_Channel5->CCR	&= ~(1U<<0);
	
	/*Wait For DMA1 Channel5 is Disable*/
	while(DMA1_Channel5->CCR & (1U<<0)){}
		
	/*Clear All Interrupt Flags of Channel5*/
	DMA1->IFCR	|=	(1U<<16);
	DMA1->IFCR	|=	(1U<<17);
	DMA1->IFCR	|=	(1U<<18);
	DMA1->IFCR	|=	(1U<<19);
	
	/*Set the Destination Buffer*/
	DMA1_Channel5->CPAR		=	dst;
	
	/*Set the Source Buffer*/
	DMA1_Channel5->CMAR		=	src;
	
	/*Set Length*/
	DMA1_Channel5->CNDTR	=	len;
	
	/*Enable Memory Increment*/
	DMA1_Channel5->CCR	|=	(1U<<7);
	
	/*Enable Circular Mode*/
	DMA1_Channel5->CCR	&=	~(1U<<5);
	
	/*Configure Transfer Direction*/
	DMA1_Channel5->CCR	&=	~(1U<<4);
	
	/*Enable DMA Transfer Complete Interrupt*/
	DMA1_Channel5->CCR	|=	(1U<<1);
	
	/*Enable DMA1 Channel5*/
	DMA1_Channel5->CCR	|=	(1U<<0);
	
	/*Enable UART1 Transmitter DMA*/
	USART1->CR3	|=	(1U<<6);
	
	/*DMA Interrupt Enable in NVIC*/
	NVIC_EnableIRQ(DMA1_Channel5_IRQn);
	
}
