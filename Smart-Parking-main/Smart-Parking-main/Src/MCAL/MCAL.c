

#include "MCAL/stm32f103x6.h"
#include "MCAL/Stm32_F103C6_Timer.h"

void MCAL_init(void)
{
	// Using internal 8 MHz RC oscillator
	// Enable clocks
	RCC_GPIOA_CLK_EN();
	RCC_GPIOB_CLK_EN();
	RCC_AFIO_CLK_EN();

	MCAL_Timer2_init();
}

