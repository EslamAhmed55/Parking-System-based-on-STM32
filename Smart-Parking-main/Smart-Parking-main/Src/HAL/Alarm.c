

#include "HAL/Alarm.h"
#include "MCAL/Stm32_F103C6_Timer.h"

void Alarm_init(void)
{
	GPIO_PinConfig_t PinConfig;
	PinConfig.GPIO_Mode = GPIO_MODE_OUTPUT_PP;
	PinConfig.GPIO_Speed = GPIO_SPEED_10M;

	// CorrecID LED
	PinConfig.GPIO_PinNumber= ALARM_CORRECID_PIN;
	MCAL_GPIO_Init(ALARM_CORRECID_PORT, &PinConfig);

	// WrongID LED
	PinConfig.GPIO_PinNumber= ALARM_WRONGID_PIN;
	MCAL_GPIO_Init(ALARM_WRONGID_PORT, &PinConfig);

	// Turn off LEDS
	MCAL_GPIO_WritePin(ALARM_CORRECID_PORT, ALARM_CORRECID_PIN, GPIO_PIN_SET);
	MCAL_GPIO_WritePin(ALARM_WRONGID_PORT, ALARM_WRONGID_PIN, GPIO_PIN_SET);
}

void Alarm_correctID_on(void)
{
	MCAL_GPIO_WritePin(ALARM_CORRECID_PORT, ALARM_CORRECID_PIN, GPIO_PIN_RESET);
}

void Alarm_correctID_off(void)
{
	MCAL_GPIO_WritePin(ALARM_CORRECID_PORT, ALARM_CORRECID_PIN, GPIO_PIN_SET);
}

void Alarm_correctID_blink(void)
{
	uint8_t blinks;
	for(blinks = 0; blinks < ALARM_NUM_BLINKS; blinks++)
	{
		MCAL_GPIO_TogglePin(ALARM_CORRECID_PORT, ALARM_CORRECID_PIN);
		MCAL_Timer2_dms(ALARM_BLINK_MS);
	}
	MCAL_GPIO_WritePin(ALARM_CORRECID_PORT, ALARM_CORRECID_PIN, GPIO_PIN_SET);
}

void Alarm_wrongID_on(void)
{
	MCAL_GPIO_WritePin(ALARM_WRONGID_PORT, ALARM_WRONGID_PIN, GPIO_PIN_RESET);

}
void Alarm_wrongID_off(void)
{
	MCAL_GPIO_WritePin(ALARM_WRONGID_PORT, ALARM_WRONGID_PIN, GPIO_PIN_SET);

}

void Alarm_wrongID_blink(void)
{
	uint8_t blinks;
	for(blinks = 0; blinks < ALARM_NUM_BLINKS; blinks++)
	{
		MCAL_GPIO_TogglePin(ALARM_WRONGID_PORT, ALARM_WRONGID_PIN);
		MCAL_Timer2_dms(ALARM_BLINK_MS);
	}
	MCAL_GPIO_WritePin(ALARM_WRONGID_PORT, ALARM_WRONGID_PIN, GPIO_PIN_SET);
}
