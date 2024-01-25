#include <math.h>

#include "MCAL/Stm32_F103C6_GPIO.h"
uint8_t Get_CRLH_POS(uint16_t GPIO_PIN_x)
{
	switch(GPIO_PIN_x)
		{
		case GPIO_PIN_0 :
			return 0;
			break;

		case GPIO_PIN_1 :
			return 4;
			break;

		case GPIO_PIN_2 :
			return 8;
			break;

		case GPIO_PIN_3 :
			return 12;
			break;
		case GPIO_PIN_4 :
			return 16;
			break;

		case GPIO_PIN_5 :
			return 20;
			break;

		case GPIO_PIN_6 :
			return 24;
			break;

		case GPIO_PIN_7 :
			return 28;
			break;

		case GPIO_PIN_8 :
			return 0;
			break;

		case GPIO_PIN_9 :
			return 4;
			break;

		case GPIO_PIN_10 :
			return 8;
			break;

		case GPIO_PIN_11 :
			return 12;
			break;
		case GPIO_PIN_12 :
			return 16;
			break;

		case GPIO_PIN_13 :
			return 20;
			break;

		case GPIO_PIN_14 :
			return 24;
			break;

		case GPIO_PIN_15 :
			return 28;
			break;
		}
		return 0;
}

/**================================================================
 * @Fn			- MCAL_GPIO_Init
 * @brief 		- Initialize GPIOx Piny according to PinConfig
 * @param[in] 	- GPIOx: where x can be any letter from A to E
 * @param[in] 	- PinConfig: carry the configuration of the GPIOx Piny
 * @retval		- None
 * Note			- STM32F103C6 has five ports (A:E) but LQFP48 includes (PORTA, PORTB) fully
 * 				  and (PORTC, PORTD) partially.
 */
void MCAL_GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_PinConfig_t *PinConfig)
{
	// Port configuration register low (GPIOx_CRL) (x=A..G) Configures Pins [0:7]
	// Port configuration register high (GPIOx_CRH) (x=A..G) Configures Pins [8:15]
	volatile uint32_t *configRegister = NULL;
	configRegister = (PinConfig->GPIO_PinNumber <= GPIO_PIN_7) ? &GPIOx->CRL : &GPIOx->CRH;

	// Clear CNFx[1:0] MODEx[1:0]
	uint8_t pinPos = Get_CRLH_POS(PinConfig->GPIO_PinNumber);
	(*configRegister) &= ~(0b1111 << pinPos);

	uint8_t pinConf = 0;
	if((PinConfig->GPIO_Mode == GPIO_MODE_OUTPUT_AF_OD) ||  (PinConfig->GPIO_Mode == GPIO_MODE_OUTPUT_AF_OD) || (PinConfig->GPIO_Mode == GPIO_MODE_OUTPUT_PP) || (PinConfig->GPIO_Mode == GPIO_MODE_OUTPUT_OD))
	{
		pinConf = ((PinConfig->GPIO_Mode - 4) << 2) | PinConfig->GPIO_Speed;
	}
	else
	{
		if((PinConfig->GPIO_Mode == GPIO_MODE_INPUT_FLO) || (PinConfig->GPIO_Mode == GPIO_MODE_ANALOG))
		{
			pinConf = PinConfig->GPIO_Mode << 2;
		}
		else if(PinConfig->GPIO_Mode == GPIO_MODE_INPUT_AF)
		{
			pinConf = GPIO_MODE_INPUT_FLO << 2;
		}
		else
		{
			pinConf = GPIO_MODE_INPUT_PU << 2;
			if(PinConfig->GPIO_Mode == GPIO_MODE_INPUT_PU)
			{
				GPIOx->ODR |= PinConfig->GPIO_PinNumber;
			}
			else
			{
				GPIOx->ODR &= ~(PinConfig->GPIO_PinNumber);
			}

		}
	}

	(*configRegister) |= (pinConf << pinPos);


}

/**================================================================
 * @Fn			- MCAL_GPIO_DeInit
 * @brief 		- Reset all GPIO registers
 * @param[in] 	- GPIOx: where x can be any letter from A to E
 * @retval		- None
 * Note			- None
 */
void MCAL_GPIO_DeInit(GPIO_TypeDef* GPIOx)
{

	// Manual Reset
	GPIOx->BRR 	= 0x00000000;
	GPIOx->BSRR = 0x00000000;
	GPIOx->CRL 	= 0x44444444;
	GPIOx->CRH 	= 0x00000000;
	GPIOx->BRR  = 0x00000000;
	GPIOx->LCKR = 0x00000000;
	GPIOx->ODR = 0x00000000;
	// GPIOx->IDR = ReadOnly!

}

/**================================================================
 * @Fn			- MCAL_GPIO_ReadPin
 * @brief 		- Read specific PIN_x
 * @param[in] 	- GPIOx: where x can be any letter from A to E
 * @param[in] 	- GPIO_PIN_x: Specific pin to be read according to GPIO_pins_define
 * @retval		- returns the value of the specific pin GPIO_PIN_x according to @ref GPIO_PIN_State
 * Note			- None
 */
uint8_t MCAL_GPIO_ReadPin(GPIO_TypeDef* GPIOx, uint16_t GPIO_PIN_x)
{
	return (GPIOx->IDR & GPIO_PIN_x) ? 1 : 0;
}

/**================================================================
 * @Fn			- MCAL_GPIO_ReadPort
 * @brief 		- Read specific portx
 * @param[in] 	- GPIOx: where x can be any letter from A to E
 * @param[in] 	- GPIO_PIN_x: Specific pin to be read according to GPIO_pins_define
 * @retval		- returns the value of the specific port GPIO_PIN_x
 * Note			- None
 */
uint16_t MCAL_GPIO_ReadPort(GPIO_TypeDef* GPIOx)
{
	return GPIOx->IDR;
}

/**================================================================
 * @Fn			- MCAL_GPIO_WritePin
 * @brief 		- Write to specific PIN_x
 * @param[in] 	- GPIOx: where x can be any letter from A to E
 * @param[in] 	- GPIO_PIN_x: Specific pin to be written according to GPIO_pins_define
 * @param[in] 	- value: the value that will be written on the pin
 * @retval		- None
 * Note			- None
 */
void MCAL_GPIO_WritePin(GPIO_TypeDef* GPIOx, uint16_t GPIO_PIN_x, uint8_t value)
{
	if(value == GPIO_PIN_SET)
	{
		GPIOx->ODR |= GPIO_PIN_x;
	}
	else
	{
		GPIOx->ODR &= ~GPIO_PIN_x;
	}

}

/**================================================================
 * @Fn			- MCAL_GPIO_WritePort
 * @brief 		- Write to specific portx
 * @param[in] 	- GPIOx: where x can be any letter from A to E
 * @param[in] 	- value: value to be written on portx
 * @retval		- None
 * Note			- None
 */
void MCAL_GPIO_WritePort(GPIO_TypeDef* GPIOx, uint16_t Value)
{
	GPIOx->ODR = (uint32_t)Value;
}

/**================================================================
 * @Fn			- MCAL_GPIO_TogglePin
 * @brief 		- Toggle specific PIN_x
 * @param[in] 	- GPIOx: where x can be any letter from A to E
 * @param[in] 	- GPIO_PIN_x: Specific pin to be toggled according to GPIO_pins_define
 * @retval		- None
 * Note			- None
 */
void MCAL_GPIO_TogglePin(GPIO_TypeDef* GPIOx, uint16_t GPIO_PIN_x)
{
	GPIOx->ODR ^= GPIO_PIN_x;
}

/**================================================================
 * @Fn			- MCAL_GPIO_TogglePort
 * @brief 		- Toggles specific portx
 * @param[in] 	- GPIOx: where x can be any letter from A to E
 * @retval		- None
 * Note			- None
 */
void MCAL_GPIO_TogglePort(GPIO_TypeDef* GPIOx)
{
	GPIOx->ODR ^= GPIOx->ODR;
}

/**================================================================
 * @Fn			- MCAL_GPIO_LockPin
 * @brief 		- Locks specific portx
 * @param[in] 	- GPIOx: where x can be any letter from A to E
 * @param[in] 	- GPIO_PIN_x: Specific pin to be locked according to GPIO_pins_define
 * @retval		- returns OK if pin is locked or ERROR if failed to lock according to @ref GPIO_RETURN_LOCK
 * Note			- None
 */
uint8_t MCAL_GPIO_LockPin(GPIO_TypeDef* GPIOx, uint16_t GPIO_PIN_x)
{
/*	Bit 16 LCKK[16]: Lock key
	This bit can be read anytime. It can only be modified using the Lock Key Writing Sequence.
	0: Port configuration lock key not active
	1: Port configuration lock key active. GPIOx_LCKR register is locked until the next reset.
	LOCK key writing sequence:
	Write 1
	Write 0
	Write 1
	Read 0
	Read 1 (this read is optional but confirms that the lock is active)
	Note: During the LOCK Key Writing sequence, the value of LCK[15:0] must not change.
	Any error in the lock sequence will abort the lock.
	Bits 15:0 LCKy: Port x Lock bit y (y= 0 .. 15)
	These bits are read write but can only be written when the LCKK bit is 0.
	0: Port configuration not locked*/
	volatile uint32_t lckval = 1 << 16;
	lckval |= GPIO_PIN_x;

	//Write 1
	GPIOx->LCKR = lckval;
	//Write 0
	GPIOx->LCKR = GPIO_PIN_x;
	//Write 1
	GPIOx->LCKR = lckval;
	//Read 0
	lckval = GPIOx->LCKR;
	//Read 1 (this read is optional but confirms that the lock is active)
	if((uint32_t)(GPIOx->LCKR & (1<<16)))
	{
		return GPIO_RETURN_OK;
	}
	else
		return GPIO_RETURN_ERROR;
}

/**=================================================================
 * @Fn -                    - MCAL_GPIO_WriteGroup
 * @brief -                 -Write on specific portion of the port
 * @param [in] -            -GPIOx : where x can be (A..E depending on device used)
 * @param [in] -            -Vlaue to write on this port
 * @param [in] -            -Mask : bit with 1 will be affected , bits with 0 won't be affected
 * @retval -                -none
 * note -                   -none
 */
/**================================================================= */
void MCAL_GPIO_WriteGroup(GPIO_TypeDef * GPIOx,uint16_t Value,uint16_t Mask)
{
	GPIOx->ODR &= ~(Mask);				// clear the group
	GPIOx->ODR |= (Value & Mask);		// put the new value
}
