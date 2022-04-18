/*
 *	Author 			: Wattanai Pongtham
 *	Create On 	:	13 Apr 2022
 *	Description	:	Header File For STM32F103C8 UART1 Driver
*/

#ifndef UART1_H_

#define	UART1_H_
#include <stdint.h>
void uart1_tx_Init(void);
void uart1_rx_Init(void);
void uart1_write(int ch);
char uart1_read(void);
void DMA1_channel4_init(uint32_t src, uint32_t dst, uint32_t len);
void DMA1_channel5_init(uint32_t src, uint32_t dst, uint32_t len);

#endif
