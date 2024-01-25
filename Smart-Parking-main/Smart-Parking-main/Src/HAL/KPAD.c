
#include "HAL/KPAD.h"

uint16_t Col[] = {KPAD_C0, KPAD_C1, KPAD_C2};
uint16_t Row[] = {KPAD_R0, KPAD_R1, KPAD_R2, KPAD_R3};

char KPAD_Chars[4][3] = {
							{'*', '0', '#'},
							{'7', '8', '9'},
							{'4', '5', '6'},
							{'1', '2', '3'}
						};



void KPAD_init()
{

	GPIO_PinConfig_t PinConfig;
	PinConfig.GPIO_Mode = GPIO_MODE_INPUT_PD;
	for(int Ri = 0; Ri < (sizeof(Row) / sizeof(Row[0])); Ri++)
	{
		PinConfig.GPIO_PinNumber = Row[Ri];
		MCAL_GPIO_Init(KPAD_PORT, &PinConfig);

	}

	PinConfig.GPIO_Mode = GPIO_MODE_OUTPUT_PP;
	PinConfig.GPIO_Speed = GPIO_SPEED_10M;

	for(int Ci = 0; Ci < (sizeof(Col) / sizeof(Col[0])); Ci++)
	{
		PinConfig.GPIO_PinNumber = Col[Ci];
		MCAL_GPIO_Init(KPAD_PORT, &PinConfig);
	}


	for(int Ci = 0; Ci < (sizeof(Col) / sizeof(Col[0])); Ci++)
		MCAL_GPIO_WritePin(KPAD_PORT, Col[Ci], GPIO_PIN_SET);
	for(int Ri = 0; Ri < (sizeof(Row) / sizeof(Row[0])); Ri++)
		MCAL_GPIO_WritePin(KPAD_PORT, Row[Ri], GPIO_PIN_SET);
}

char KPAD_Get_Char()
{
	int Ri, Ci;
	for(Ci = 0; Ci < (sizeof(Col) / sizeof(Col[0])); Ci++)
	{
		// All columns HIGH
		for(int nestedCi= 0; nestedCi < (sizeof(Col) / sizeof(Col[0])); nestedCi++)
			MCAL_GPIO_WritePin(KPAD_PORT, Col[nestedCi], GPIO_PIN_SET);

		// Ground each column
		MCAL_GPIO_WritePin(KPAD_PORT, Col[Ci], GPIO_PIN_RESET);
		for(Ri = 0; Ri < (sizeof(Row) / sizeof(Row[0])); Ri++)
		{
			if(!MCAL_GPIO_ReadPin(KPAD_PORT, Row[Ri]))
			{
				// Key is still pressed
				while(!(MCAL_GPIO_ReadPin(KPAD_PORT, Row[Ri])));
				return KPAD_Chars[Ri][Ci];

			}
		}
	}

	return 0;

}
