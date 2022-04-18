#include "wattanai_stm32f103c8_clock_config.h"
#include "stm32f10x.h"

void system_clock_config(void)
{
	RCC->CFGR		|=	0x05D0402;
}
