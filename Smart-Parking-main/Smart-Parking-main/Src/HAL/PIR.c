

#include <stdint.h>

#include "HAL/PIR.h"
#include "MCAL/Stm32_F103C6_GPIO.h"

void PIR_init(void)
{

	GPIO_PinConfig_t PinConfig;
	PinConfig.GPIO_Mode = GPIO_MODE_INPUT_PU;
	PinConfig.GPIO_Speed = GPIO_SPEED_10M;

	// Entry gate PIR
	PinConfig.GPIO_PinNumber= PIR_ENTRY_PIN;
	MCAL_GPIO_Init(GPIOA, &PinConfig);

	// Exit gate PIR
	PinConfig.GPIO_PinNumber= PIR_EXIT_PIN;
	MCAL_GPIO_Init(GPIOA, &PinConfig);

	MCAL_GPIO_WritePin(PIR_GPIOx, PIR_ENTRY_PIN, GPIO_PIN_SET);
	MCAL_GPIO_WritePin(PIR_GPIOx, PIR_EXIT_PIN, GPIO_PIN_SET);
}

e_PIRStatus_t PIR_entry(void)
{
	e_PIRStatus_t status;
	uint8_t pinStatus = MCAL_GPIO_ReadPin(PIR_GPIOx, PIR_ENTRY_PIN);
	if(pinStatus == GPIO_PIN_SET)
	{
		status = PIR_DETECTED;
	}
	else
	{
		status = PIR_NOT_DETECTED;
	}

	return status;
}

e_PIRStatus_t PIR_exit(void)
{
	e_PIRStatus_t status;
	uint8_t pinStatus = MCAL_GPIO_ReadPin(PIR_GPIOx, PIR_EXIT_PIN);
	if(pinStatus == GPIO_PIN_SET)
	{
		status = PIR_DETECTED;
	}
	else
	{
		status = PIR_NOT_DETECTED;
	}

	return status;
}


