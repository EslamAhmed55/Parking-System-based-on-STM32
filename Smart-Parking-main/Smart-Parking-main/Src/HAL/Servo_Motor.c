
#include "HAL/Servo_Motor.h"





//B8 SERVO1
void Servo1_Entry_Gate_Init(void)
{
	/*SERVO MOTOR 1*/
	GPIO_PinConfig_t PinCinfg;
	PinCinfg.GPIO_PinNumber=GPIO_PIN_8;
	PinCinfg.GPIO_Mode = GPIO_MODE_OUTPUT_PP;
	PinCinfg.GPIO_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(GPIOB, &PinCinfg);
}

//Direction Up or Down
void Servo1_Entry_Gate(e_ServoMotor_Direction_t Direction)
{
	if(Direction == SERVO_UP)
	{
		//servo1 Enter gate up +90
		MCAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, 1);
		MCAL_Timer2_dus(500);
		MCAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, 0);
	}
	if(Direction== SERVO_DOWN)
	{
		//servo1 Enter gate down -90
		MCAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, 1);
		MCAL_Timer2_dus(1488);
		MCAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, 0);
	}


}

void Servo2_Exit_Gate_Init(void)
{
	/*SERVO MOTOR 2*/
	GPIO_PinConfig_t PinCinfg;
	PinCinfg.GPIO_PinNumber=GPIO_PIN_9;
	PinCinfg.GPIO_Mode = GPIO_MODE_OUTPUT_PP;
	PinCinfg.GPIO_Speed =GPIO_SPEED_10M;
	MCAL_GPIO_Init(GPIOB, &PinCinfg);
}

void Servo2_Exit_Gate(e_ServoMotor_Direction_t Direction)
{
	if(Direction == SERVO_UP)
	{
		//servo2 Exit gate up +90
		MCAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, 1);
		MCAL_Timer2_dus(500);
		MCAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, 0);
	}

	if(Direction == SERVO_DOWN)
	{
		//servo2 Exit gate down -90
		MCAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, 1);
		MCAL_Timer2_dus(1488);
		MCAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, 0);
	}

}
