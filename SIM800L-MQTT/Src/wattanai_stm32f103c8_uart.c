#include <stdio.h>
#include "stm32f10x.h"
#include "wattanai_stm32f103c8_uart.h"
	
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
	
	/*Enable Clock To Port A*/
	RCC->APB2ENR	|=	(1U<<2);
	
	/*Enable Clock To UART1*/
	RCC->APB2ENR |= 	(1U<<14);
	
	/*Configure Port A Pin9 As Alternate Function Output PP 50MHz*/
	GPIOA->CRH		|=	(1U<<7);
	GPIOA->CRH		&=	~(1U<<6);
	GPIOA->CRH		|=	(1U<<5);
	GPIOA->CRH		|=	(1U<<4);
	
	/*Configure Buad Rate 9600*/
	USART1->BRR		|=	0x1D4C;
	
	/*Enable Transmitter*/
	USART1->CR1		|=	(1U<<3);
	
	/*Enable UART*/
	USART1->CR1		|=	(1U<<13);
}

void uart1_rx_Init(void)
{
	
	/*Enable Clock To Port A*/
	RCC->APB2ENR	|=	(1U<<2);
	
	/*Enable Clock To UART1*/
	RCC->APB2ENR |= 	(1U<<14);
	
	/*Configure Port A Pin10 As Input Pull-up Pull-down*/
	GPIOA->CRH		|=	(1U<<11);
	GPIOA->CRH		&=	~(1U<<10);
	GPIOA->CRH		&=	~(1U<<9);
	GPIOA->CRH		&=	~(1U<<8);
	
	/*Configure Buad Rate 9600*/
	USART1->BRR		|=	0x1D4C;
	
	/*Enable IDLE Line*/
	USART1->CR1	|=	(1U<<4);
	
	/*Enable Receiver*/
	USART1->CR1		|=	(1U<<2);
	
	/*Enable UART*/
	USART1->CR1		|=	(1U<<13);
	
	NVIC_EnableIRQ(USART1_IRQn);
}

void uart2_tx_Init(void)
{
	/*Enable Alternate Function For Peripheral Pin*/
	RCC->APB2ENR	|=	(1U<<0);
	
	/*Enable Clock To Port A*/
	RCC->APB2ENR	|=	(1U<<2);
	
	/*Enable Clock To UART2*/
	RCC->APB1ENR |= 	(1U<<17);
	
	/*Configure Port A Pin2 As Alternate Function Output PP 50MHz*/
	GPIOA->CRL		|=	(1U<<11);
	GPIOA->CRL		&=	~(1U<<10);
	GPIOA->CRL		|=	(1U<<9);
	GPIOA->CRL		|=	(1U<<8);
	
	/*Configure Buad Rate 9600*/
	USART2->BRR		|=	0xEA6;
	
	/*Enable Transmitter*/
	USART2->CR1		|=	(1U<<3);
	
	/*Enable UART*/
	USART2->CR1		|=	(1U<<13);
}

void uart2_rx_Init(void)
{
	
	/*Enable Clock To Port A*/
	RCC->APB2ENR	|=	(1U<<2);
	
	/*Enable Clock To UART2*/
	RCC->APB1ENR |= 	(1U<<17);
	
	/*Configure Port A Pin3 As Input Pull-up Pull-down*/
	GPIOA->CRL		|=	(1U<<15);
	GPIOA->CRL		&=	~(1U<<14);
	GPIOA->CRL		&=	~(1U<<13);
	GPIOA->CRL		&=	~(1U<<12);
	
	/*Configure Buad Rate 9600*/
	USART2->BRR		|=	0xEA6;
	
	/*Enable IDLE Line*/
	USART2->CR1	|=	(1U<<4);
	
	/*Enable Receiver*/
	USART2->CR1		|=	(1U<<2);
	
	/*Enable UART*/
	USART2->CR1		|=	(1U<<13);
	
	NVIC_EnableIRQ(USART2_IRQn);
}

void uart3_tx_Init(void)
{
	/*Enable Alternate Function For Peripheral Pin*/
	RCC->APB2ENR	|=	(1U<<0);
	
	/*Enable Clock To Port B*/
	RCC->APB2ENR	|=	(1U<<3);
	
	/*Enable Clock To UART3*/
	RCC->APB1ENR |= 	(1U<<18);
	
	/*Configure Port B Pin10 As Alternate Function Output PP 50MHz*/
	//GPIOB->CRH		|=	0xB44;
	GPIOB->CRH		|=	(1U<<11);
	GPIOB->CRH		&=	~(1U<<10);
	GPIOB->CRH		|=	(1U<<9);
	GPIOB->CRH		|=	(1U<<8);
	
	/*Configure Buad Rate 9600*/
	USART3->BRR		|=	0xEA6;
	
	/*Enable Transmitter*/
	USART3->CR1		|=	(1U<<3);
	
	/*Enable UART*/
	USART3->CR1		|=	(1U<<13);
}

void uart3_rx_Init(void)
{
	
	/*Enable Clock To Port B*/
	RCC->APB2ENR	|=	(1U<<3);
	
	/*Enable Clock To UART3*/
	RCC->APB1ENR |= 	(1U<<18);
	
	/*Configure Port B Pin 11 As Input Pull-up Pull-down*/
	GPIOB->CRH		|=	(1U<<15);
	GPIOB->CRH		&=	~(1U<<14);
	GPIOB->CRH		&=	~(1U<<13);
	GPIOB->CRH		&=	~(1U<<12);
	
	/*Configure Buad Rate 9600*/
	USART3->BRR		|=	0xEA6;
	
	/*Enable IDLE Line*/
	USART3->CR1	|=	(1U<<4);
	
	/*Enable Receiver*/
	USART3->CR1		|=	(1U<<2);
	
	/*Enable UART*/
	USART3->CR1		|=	(1U<<13);
	
	NVIC_EnableIRQ(USART3_IRQn);
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

void uart2_write(int ch)
{
	/*Check That Transmit Data Register is Empty*/
	while(!(USART2->SR & (1U<<6)))
	{
		/*Wait*/
	}
		
	/*Write Data To Data Register*/
	USART2->DR		|=	(ch & 0xFF);
}

char uart2_read(void)
{
	while(!(USART2->SR & (1U<<5)))
	{
		/*Wait*/
	}
	return USART2->DR;
}

void uart3_write(int ch)
{
	/*Check That Transmit Data Register is Empty*/
	while(!(USART3->SR & (1U<<6)))
	{
		/*Wait*/
	}
		
	/*Write Data To Data Register*/
	USART3->DR		|=	(ch & 0xFF);
}

char uart3_read(void)
{
	while(!(USART3->SR & (1U<<5)))
	{
		/*Wait*/
	}
	return USART3->DR;
}

void DMA1_channel2_init(uint32_t src, uint32_t dst, uint32_t len)
{
	/*Enable Clock Access To DMA1*/
	RCC->AHBENR		|=	(1U<<0);
	
	/*Disable DMA1 Channel2*/
	DMA1_Channel2->CCR	&= ~(1U<<0);
	
	/*Wait For DMA1 Channel2 is Disable*/
	while(DMA1_Channel4->CCR & (1U<<0)){}
		
	/*Clear All Interrupt Flags of Channel2*/
	DMA1->IFCR	|=	(1U<<4);
	DMA1->IFCR	|=	(1U<<5);
	DMA1->IFCR	|=	(1U<<6);
	DMA1->IFCR	|=	(1U<<7);
	
	/*Set the Destination Buffer*/
	DMA1_Channel2->CPAR		=	dst;
	
	/*Set the Source Buffer*/
	DMA1_Channel2->CMAR		=	src;
	
	/*Set Length*/
	DMA1_Channel2->CNDTR	=	len;
	
	/*Enable Memory Increment*/
	DMA1_Channel2->CCR	|=	(1U<<7);
	
	/*Configure Transfer Direction*/
	DMA1_Channel2->CCR	|=	(1U<<4);
	
	/*Enable DMA Transfer Complete Interrupt*/
	DMA1_Channel2->CCR	|=	(1U<<1);
	
	/*Enable DMA1 Channel4*/
	DMA1_Channel2->CCR	|=	(1U<<0);
	
	/*Enable UART3 Transmitter DMA*/
	USART3->CR3	|=	(1U<<7);
	
	/*DMA Interrupt Enable in NVIC*/
	//NVIC_EnableIRQ(DMA1_Channel4_IRQn);
	
}

void DMA1_channel3_init(uint32_t src, uint32_t dst, uint32_t len)
{
	/*Enable Clock Access To DMA1*/
	RCC->AHBENR		|=	(1U<<0);
	
	/*Disable DMA1 Channel3*/
	DMA1_Channel3->CCR	&= ~(1U<<0);
	
	/*Wait For DMA1 Channel3 is Disable*/
	while(DMA1_Channel3->CCR & (1U<<0)){}
		
	/*Clear All Interrupt Flags of Channel3*/
	DMA1->IFCR	|=	(1U<<8);
	DMA1->IFCR	|=	(1U<<9);
	DMA1->IFCR	|=	(1U<<10);
	DMA1->IFCR	|=	(1U<<11);
	
	/*Set the Destination Buffer*/
	DMA1_Channel3->CPAR		=	dst;
	
	/*Set the Source Buffer*/
	DMA1_Channel3->CMAR		=	src;
	
	/*Set Length*/
	DMA1_Channel3->CNDTR	=	len;
	
	/*Enable Memory Increment*/
	DMA1_Channel3->CCR	|=	(1U<<7);
	
	/*Enable Circular Mode*/
	DMA1_Channel3->CCR	&=	~(1U<<5);
	
	/*Configure Transfer Direction*/
	DMA1_Channel3->CCR	&=	~(1U<<4);
	
	/*Enable DMA Transfer Complete Interrupt*/
	DMA1_Channel3->CCR	|=	(1U<<1);
	
	/*Enable DMA1 Channel5*/
	DMA1_Channel3->CCR	|=	(1U<<0);
	
	/*Enable UART3 Receiver DMA*/
	USART3->CR3	|=	(1U<<6);
	
	/*DMA Interrupt Enable in NVIC*/
	//NVIC_EnableIRQ(DMA1_Channel5_IRQn);
	
}

void DMA1_channel4_init(uint32_t src, uint32_t dst, uint32_t len)
{
	/*Enable Clock Access To DMA1*/
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
	//NVIC_EnableIRQ(DMA1_Channel4_IRQn);
	
}

void DMA1_channel5_init(uint32_t src, uint32_t dst, uint32_t len)
{
	/*Enable Clock Access To DMA1*/
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
	
	/*Enable UART1 Receiver DMA*/
	USART1->CR3	|=	(1U<<6);
	
	/*DMA Interrupt Enable in NVIC*/
	//NVIC_EnableIRQ(DMA1_Channel5_IRQn);
	
}

void DMA1_channel6_init(uint32_t src, uint32_t dst, uint32_t len)
{
	/*Enable Clock Access To DMA*/
	RCC->AHBENR		|=	(1U<<0);
	
	/*Disable DMA1 Channel6*/
	DMA1_Channel6->CCR	&= ~(1U<<0);
	
	/*Wait For DMA1 Channel6 is Disable*/
	while(DMA1_Channel6->CCR & (1U<<0)){}
		
	/*Clear All Interrupt Flags of Channel5*/
	DMA1->IFCR	|=	(1U<<20);
	DMA1->IFCR	|=	(1U<<21);
	DMA1->IFCR	|=	(1U<<22);
	DMA1->IFCR	|=	(1U<<23);
	
	/*Set the Destination Buffer*/
	DMA1_Channel6->CPAR		=	dst;
	
	/*Set the Source Buffer*/
	DMA1_Channel6->CMAR		=	src;
	
	/*Set Length*/
	DMA1_Channel6->CNDTR	=	len;
	
	/*Enable Memory Increment*/
	DMA1_Channel6->CCR	|=	(1U<<7);
	
	/*Enable Circular Mode*/
	DMA1_Channel6->CCR	&=	~(1U<<5);
	
	/*Configure Transfer Direction*/
	DMA1_Channel6->CCR	&=	~(1U<<4);
	
	/*Enable DMA Transfer Complete Interrupt*/
	DMA1_Channel6->CCR	|=	(1U<<1);
	
	/*Enable DMA1 Channel5*/
	DMA1_Channel6->CCR	|=	(1U<<0);
	
	/*Enable UART2 Receiver DMA*/
	USART2->CR3	|=	(1U<<6);
	
	/*DMA Interrupt Enable in NVIC*/
	//NVIC_EnableIRQ(DMA1_Channel5_IRQn);
	
}

void DMA1_channel7_init(uint32_t src, uint32_t dst, uint32_t len)
{
	/*Enable Clock Access To DMA1*/
	RCC->AHBENR		|=	(1U<<0);
	
	/*Disable DMA1 Channel7*/
	DMA1_Channel7->CCR	&= ~(1U<<0);
	
	/*Wait For DMA1 Channel7 is Disable*/
	while(DMA1_Channel7->CCR & (1U<<0)){}
		
	/*Clear All Interrupt Flags of Channel7*/
	DMA1->IFCR	|=	(1U<<24);
	DMA1->IFCR	|=	(1U<<25);
	DMA1->IFCR	|=	(1U<<26);
	DMA1->IFCR	|=	(1U<<27);
	
	/*Set the Destination Buffer*/
	DMA1_Channel7->CPAR		=	dst;
	
	/*Set the Source Buffer*/
	DMA1_Channel7->CMAR		=	src;
	
	/*Set Length*/
	DMA1_Channel7->CNDTR	=	len;
	
	/*Enable Memory Increment*/
	DMA1_Channel7->CCR	|=	(1U<<7);
	
	/*Configure Transfer Direction*/
	DMA1_Channel7->CCR	|=	(1U<<4);
	
	/*Enable DMA Transfer Complete Interrupt*/
	DMA1_Channel7->CCR	|=	(1U<<1);
	
	/*Enable DMA1 Channel7*/
	DMA1_Channel7->CCR	|=	(1U<<0);
	
	/*Enable UART2 Transmitter DMA*/
	USART2->CR3	|=	(1U<<7);
	
	/*DMA Interrupt Enable in NVIC*/
	//NVIC_EnableIRQ(DMA1_Channel7_IRQn);
	
}
