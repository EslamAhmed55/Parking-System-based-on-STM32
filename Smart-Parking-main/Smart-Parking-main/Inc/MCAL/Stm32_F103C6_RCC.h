

#ifndef INC_STM32_F103C6_RCC_H_
#define INC_STM32_F103C6_RCC_H_

#include "MCAL/stm32f103x6.h"
#include "MCAL/Stm32_F103C6_GPIO.h"

#define HSE_CLK 		(uint32_t)16000000
#define HSI_RC_CLK 		(uint32_t)8000000

uint32_t MCAL_RCC_GetSYS_CLKFreq(void);

uint32_t MCAL_RCC_GetHCLKFreq(void);

uint32_t MCAL_RCC_GetPCLK1Freq(void);
uint32_t MCAL_RCC_GetPCLK2Freq(void);


#endif /* INC_STM32_F103C6_RCC_H_ */
