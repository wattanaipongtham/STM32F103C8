/*
 *	Author 			: Wattanai Pongtham
 *	Create On 	:	13 Apr 2022
 *	Description	:	Header File For STM32F103C8 UART1 Driver
*/

#ifndef UART_H_

#define	UART_H_
#include <stdint.h>
void uart1_tx_Init(void);
void uart1_rx_Init(void);
void uart2_tx_Init(void);
void uart2_rx_Init(void);
void uart3_tx_Init(void);
void uart3_rx_Init(void);

void uart1_write(int ch);
char uart1_read(void);
void uart2_write(int ch);
char uart2_read(void);
void uart3_write(int ch);
char uart3_read(void);

void DMA1_channel2_init(uint32_t src, uint32_t dst, uint32_t len);//USART3_TX
void DMA1_channel3_init(uint32_t src, uint32_t dst, uint32_t len);//USART3_RX
void DMA1_channel4_init(uint32_t src, uint32_t dst, uint32_t len);//USART1_TX
void DMA1_channel5_init(uint32_t src, uint32_t dst, uint32_t len);//USART1_RX
void DMA1_channel6_init(uint32_t src, uint32_t dst, uint32_t len);//USART2_RX
void DMA1_channel7_init(uint32_t src, uint32_t dst, uint32_t len);//USART2_TX

#endif
