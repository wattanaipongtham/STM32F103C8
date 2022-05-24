#include <stdio.h>
#include <stdint.h>
#include <ctype.h>
#include "stm32f10x.h"
#include "sysTick.h"
#include "wattanai_stm32f103c8_uart.h"
#include "wattanai_stm32f103c8_clock_config.h"

void GSM_POWER_ON(void);
int GPS_SEARCH_MODE(void);

/*=============================SIM800L COMMAND=============================*/
char AT_CMD[4]= "AT\r\n";
char AT_CSQ[8]=	"AT+CSQ\r\n";
char AT_CREG[9]=	"AT+CREG\r\n";
char AT_CIPSHUT[12]= "AT+CIPSHUT\r\n";
char AT_CFUN[11]=	"AT+CFUN=1\r\n";
char AT_CGATT[12]			=	"AT+CGATT=1\r\n";
char AT_CPIN[10]			=	"AT+CPIN?\r\n";
char AT_CSTT[34] 			= "AT+CSTT=\"internet\",\"true\",\"true\"\r\n";
char AT_CIICR[10] 		= "AT+CIICR\r\n";
char AT_CIFSR[10] 		= "AT+CIFSR\r\n";
char AT_CIPSTART[42]	=	"AT+CIPSTART=\"TCP\",\"18.159.219.87\",\"1883\"\r\n";
char AT_CIPSEND[15] 	=	"AT+CIPSEND=42\r\n";
char DATA[44]					=	{0x10, 0x11, 0x00, 0x04, 0x4D, 0x51, 0x54, 0x54, 0x04, 0x02, 0x00, 0x3C, 0x00, 0x05, 0x50, 0x51, 0x52, 0x53, 0x54, 0x30, 0x15, 0x00, 0x09, 0x57, 0x41, 0x54, 0x54, 0x41, 0x4E, 0x41, 0x49, 0x49, 0x7B, 0x22, 0x64, 0x22, 0x3A, 0x30, 0x30, 0x30, 0x30, 0x7D, 0x0A};
/*=========================================================================*/


/*=============================RESPONSE BUFFER=============================*/
char RES_CMD[50];
char RES_CREG[50];
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
char RES_SERVER[50];
char RES_MX7383[50];
/*=========================================================================*/
int count=0, distance=0, num=0, digit1=0, digit2=0, digit3=0, digit4=0;
__IO uint32_t tmpreg;

int main()
{
	/*Configure System Clock*/
	system_clock_config();
	
	if(GPS_SEARCH_MODE())
	{
		/*For Receive Data From GPS-Module*/
		uart3_rx_Init();
		GPIOC->ODR	&=	~(1U<<13);
	}
	else{
	/*Power On SIM800A*/
	GSM_POWER_ON();
	
	/*For Receive Data From GSM*/
	uart1_rx_Init();
	
	/*For Send Command To GSM*/
	uart1_tx_Init();
	
	/*For Receive Data From MB7383 Sensor*/
	uart2_rx_Init();
	
	/*Start Reading Data From MB7383 Sensor*/
	DMA1_channel6_init((uint32_t) RES_MX7383, (uint32_t) &USART2->DR, 6);
	}
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
				if(RES_CMD[5] == 'O' && RES_CMD[6] == 'K')
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
				if(RES_CIPSHUT[18] == 'O' && RES_CIPSHUT[19] == 'K')
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
				if(RES_CGATT[13] == 'O' && RES_CGATT[14] == 'K')
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
				if(RES_CFUN[12] == 'O' && RES_CFUN[13] == 'K')
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
				if(RES_CPIN[18] == 'R' && RES_CPIN[19] == 'E' && RES_CPIN[20] == 'A' && RES_CPIN[21] == 'D' && RES_CPIN[22] == 'Y' && RES_CPIN[27] == 'O' && RES_CPIN[28] == 'K' )
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
				if(RES_CSTT[35] == 'O' && RES_CSTT[36] == 'K')
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
				if(isdigit(RES_CIFSR[11]) && isdigit(RES_CIFSR[12]))
				{
					count = count + 1;
					DMA1_channel5_init((uint32_t) RES_CIPSTART, (uint32_t) &USART1->DR, 50);
					DMA1_channel4_init((uint32_t) AT_CIPSTART, (uint32_t) &USART1->DR, 42);
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
				if(RES_CIPSTART[43] == 'O' && RES_CIPSTART[44] == 'K')
				{
					count = count + 1;
					DMA1_channel5_init((uint32_t) RES_CIPSTART2, (uint32_t) &USART1->DR, 50);
				}else
				{
					DMA1_channel5_init((uint32_t) RES_CIPSTART, (uint32_t) &USART1->DR, 50);
					DMA1_channel4_init((uint32_t) AT_CIPSTART, (uint32_t) &USART1->DR, 42);
				}
				break;
			case 9:
				tmpreg = USART1->SR;
				(void) tmpreg;
				tmpreg = USART1->DR;
				(void) tmpreg;
				if(RES_CIPSTART2[10] == 'O' && RES_CIPSTART2[11] == 'K')
				{
					count = count + 1;
					DMA1_channel5_init((uint32_t) RES_CIPSEND, (uint32_t) &USART1->DR, 50);
					DMA1_channel4_init((uint32_t) AT_CIPSEND, (uint32_t) &USART1->DR, 15);
				}else
				{

				}
				break;
			case 10:
				tmpreg = USART1->SR;
				(void) tmpreg;
				tmpreg = USART1->DR;
				(void) tmpreg;
				if(RES_CIPSEND[16] == '>')
				{
					count = count + 1;
					DMA1_channel5_init((uint32_t) RES_SERVER, (uint32_t) &USART1->DR, 50);
					DMA1_channel4_init((uint32_t) DATA, (uint32_t) &USART1->DR, 44);
				}else
				{

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

void USART2_IRQHandler(void)
{
	tmpreg = USART2->SR;
	(void) tmpreg;
	tmpreg = USART2->DR;
	(void) tmpreg;
	if(num < 100){
	num = num + 1;
	distance += ((int)RES_MX7383[1] - 48)*1000;
	distance += ((int)RES_MX7383[2] - 48)*100;
	distance += ((int)RES_MX7383[3] - 48)*10;
	distance += ((int)RES_MX7383[4] - 48)*1;
	DMA1_channel6_init((uint32_t) RES_MX7383, (uint32_t) &USART2->DR, 6);
	}else
	{
		/*Disable Receiver*/
		USART2->CR1		&=	~(1U<<2);
	
		/*Disable UART2*/
		USART2->CR1		&=	~(1U<<13);

		distance = distance/100;
		digit1 = distance/1000;
		digit2 = (distance/100)%10;
		digit3 = (distance%100)/10;
		digit4 = distance%10;
		if(digit1 == 0)
		{
			DATA[37] = 0x20;
		}
		DATA[38] = digit2+48;
		DATA[39] = digit3+48;
		DATA[40] = digit4+48;
		DMA1_channel5_init((uint32_t) RES_CMD, (uint32_t) &USART1->DR, 50);
		DMA1_channel4_init((uint32_t) AT_CMD, (uint32_t) &USART1->DR, 4);
	}
}

void GSM_POWER_ON()
{
	/*Enable clock To Port A*/
	RCC->APB2ENR |= (1U<<2);
	
	/*Configure Port A Pin7 As Output Push-Pull 50MHz*/
	GPIOA->CRL	 &= ~(1U<<31);
	GPIOA->CRL	 &= ~(1U<<30);
	GPIOA->CRL	 |= (1U<<29);
	GPIOA->CRL	 |= (1U<<28);
	
	/*Set Port A Pin7*/
	GPIOA->ODR	 |= (1U<<7);
	
	/*Wait 3 Second For Turn On GSM*/
	sysTickDelayMs(3000);
	
	/*Then Reset PortA Pin7*/
	GPIOA->ODR	 &= ~(1U<<7);
	
	/*Wait 15 Second For GSM To Search For Signal*/
	sysTickDelayMs(5000);
	sysTickDelayMs(5000);
	sysTickDelayMs(5000);
}

int GPS_SEARCH_MODE()
{
	/*Enable clock To Port A*/
	RCC->APB2ENR 	|= 	(1U<<2);
	
	/*Configure Port A Pin4 As Input Pull-down*/
	GPIOA->CRL	 	|= 	(1U<<19);
	GPIOA->CRL	 	&= 	~(1U<<18);
	GPIOA->ODR		&=	~(1U<<4);
	
	return GPIOA->IDR & (1U<<4);
}
