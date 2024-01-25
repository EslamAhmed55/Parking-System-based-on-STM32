

#include "MCAL/Stm32_F103C6_Timer.h"


void MCAL_Timer2_init(void)
{
	RCC_APB1ENR |=(1<<0);     //Enable RCC for tim2
	TIM2_PSC = 7;             //Clk_input=(8M/(7+1))=1MHZ
	TIM2_ARR = 0xC350;        //to make interrupt after 50000 tick(50000*10^-6)=0.05s
	TIM2_CR1 |=(1<<0);
	while(!(TIM2_SR)&(1<<0));
}

void MCAL_Timer2_dus(int us)
{
	TIM2_CNT=0;
	while(TIM2_CNT<us);
}

void MCAL_Timer2_dms(int ms)
{
	int i=0;
	for(i=0;i<ms;i++)
	{
		MCAL_Timer2_dus(1000);
	}
}

