
#ifndef MCAL_STM32_F103C6_TIMER_H_
#define MCAL_STM32_F103C6_TIMER_H_

#include "MCAL/stm32f103x6.h"
#include "MCAL/Stm32_F103C6_GPIO.h"

#define RCC_APB1ENR                           *( volatile uint32_t *)(RCC_BASE+0x1C)
#define RCC_APB2ENR                           *( volatile uint32_t *)(RCC_BASE+0x18)





//TIMER2
#define TIM2_timer_Base                        0x40000000
#define TIM2_CNT                              *( volatile uint32_t *)(TIM2_timer_Base+0x24)
#define TIM2_CR1                              *( volatile uint32_t *)(TIM2_timer_Base+0x00)
#define TIM2_PSC                              *( volatile uint32_t *)(TIM2_timer_Base+0x28)
#define TIM2_SR                               *( volatile uint32_t *)(TIM2_timer_Base+0x10)
#define TIM2_DIER                             *( volatile uint32_t *)(TIM2_timer_Base+0x0c)
#define TIM2_ARR                              *( volatile uint32_t *)(TIM2_timer_Base+0x2c)
#define RCC_APB1ENR                           *( volatile uint32_t *)(RCC_BASE+0x1C)



/*=================Timer2======================*/
void MCAL_Timer2_init(void);
void MCAL_Timer2_dus(int us);
void MCAL_Timer2_dms(int ms);



#endif /* MCAL_STM32_F103C6_TIMER_H_ */
