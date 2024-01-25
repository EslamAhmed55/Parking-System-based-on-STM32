
#include <stdio.h>

#include "HAL/KPAD.h"
#include "HAL/LCD.h"
#include "HAL/RFID.h"
#include "HAL/Alarm.h"
#include "HAL/PIR.h"
#include "HAL/Servo_Motor.h"

#include "MCAL/Stm32_F103C6_Timer.h"

static int8_t AuthenticIDs[3] = {-1, -1, -1};
static uint8_t FreeSlots = 3;

void SmartParking_init(void)
{
	// Admin enters authentic IDs
	LCD_sendstring(&LCD_admin, (const char *)"Enter allowed ID");

	char string[17];
	for(int i = 0; i < 3; i++)
	{
		LCD_gotoxy(&LCD_admin, 0, i + 1);

		sprintf(string, "Enter ID[%d]: ", i);
		LCD_sendstring(&LCD_admin, (const char *)string);

		do
		{
			AuthenticIDs[i] = KPAD_Get_Char();
		}
		while(AuthenticIDs[i] == 0);

		LCD_sendchar(&LCD_admin, (unsigned char)AuthenticIDs[i], DATA);
	}

	// Shows entered IDs
	LCD_clearscreen(&LCD_admin);
	LCD_gotoxy(&LCD_admin, 0,0);

	LCD_sendstring(&LCD_admin, (const char *)"Allowed IDs:");
	for(int i = 0; i < 3; i++)
	{
		LCD_gotoxy(&LCD_admin, 0, i + 1);

		sprintf(string, "ID[%d]: %c", i, AuthenticIDs[i]);
		LCD_sendstring(&LCD_admin, (const char *)string);
	}


}

/**
 * @brief Checks if the provided ID is authentic for accessing the parking area.
 *
 * This function verifies whether the given ID is authentic and allowed to access the parking area.
 * It checks the ID against a list of authentic IDs stored in the system.
 *
 * @param id The ID to be checked for authenticity.
 * @return 1 if the ID is authentic and allowed access, 0 otherwise.
 */
uint8_t SmartParking_isAuthentic(uint8_t id)
{
	uint8_t isAuthentic = 0;
	for(int i = 0; i < 3; i++)
	{
		if(id == AuthenticIDs[i])
		{
			isAuthentic = 1;
		}
	}

	return isAuthentic;
}

/**
 * @brief Entry process for the Smart Parking system.
 *
 *
 * @note This function is marked as static and should only be called internally within the Smart Parking module.
 * It is not intended for direct external use.
 */
static void SmartParking_entry(void)
{
	LCD_clearscreen(&LCD_user);
	LCD_gotoxy(&LCD_user, 0, 0);


	char string[17];
	LCD_sendstring(&LCD_user, (const char *)"  *Entry Gate*  ");

	LCD_gotoxy(&LCD_user, 0, 1);
	sprintf(string, "Free Slots:%d ", FreeSlots);
	LCD_sendstring(&LCD_user, string);

	uint16_t id = RFID_entry_Read();

	LCD_gotoxy(&LCD_user, 0, 2);
	sprintf(string, "Entered id:%c", id);
	LCD_sendstring(&LCD_user, string);

	LCD_gotoxy(&LCD_user, 0, 3);
	LCD_sendstring(&LCD_user, (const char*)" * Processing * ");

	MCAL_Timer2_dms(200);

	LCD_clearscreen(&LCD_user);
	LCD_gotoxy(&LCD_user, 0, 1);

	uint8_t isAuthentic = SmartParking_isAuthentic(id);
	if(isAuthentic == 1 && FreeSlots == 0)
	{
		LCD_sendstring(&LCD_user, (const char *)"*No Free Slots*");
		Alarm_correctID_blink();
		LCD_clearscreen(&LCD_user);

		return;
	}
	else if(isAuthentic == 0)
	{
		LCD_sendstring(&LCD_user, (const char *)"   *Wrong ID*   ");
		Alarm_wrongID_blink();
		LCD_clearscreen(&LCD_user);
		return;
	}


	LCD_sendstring(&LCD_user, (const char *)"  *Correct ID*  ");

	Servo1_Entry_Gate(SERVO_UP);
	Alarm_correctID_blink();
	Alarm_correctID_on();
	MCAL_Timer2_dms(200);

	while(PIR_entry() == PIR_DETECTED);
	Servo1_Entry_Gate(SERVO_DOWN);
	Alarm_correctID_blink();
	Alarm_correctID_off();

	FreeSlots--;

	LCD_clearscreen(&LCD_user);

}

/**
 * @brief Exit process for the Smart Parking system.
 *
 *
 * @note This function is marked as static and should only be called internally within the Smart Parking module.
 * It is not intended for direct external use.
 */
static void SmartParking_exit(void)
{
	LCD_clearscreen(&LCD_user);
	LCD_gotoxy(&LCD_user, 0, 0);

	char string[17];
	LCD_sendstring(&LCD_user, (const char *)"  *Exit Gate*  ");

	LCD_gotoxy(&LCD_user, 0, 1);
	sprintf(string, "Free Slots:%d ", FreeSlots);
	LCD_sendstring(&LCD_user, string);

	uint16_t id = RFID_exit_Read();

	LCD_gotoxy(&LCD_user, 0, 2);
	sprintf(string, "Entered id:%c", id);
	LCD_sendstring(&LCD_user, string);

	LCD_gotoxy(&LCD_user, 0, 3);
	LCD_sendstring(&LCD_user, (const char*)" * Processing * ");

	MCAL_Timer2_dms(200);

	LCD_clearscreen(&LCD_user);
	LCD_gotoxy(&LCD_user, 0, 1);

	uint8_t isAuthentic = SmartParking_isAuthentic(id);
	if(isAuthentic == 1 && FreeSlots == 3)
	{
		LCD_sendstring(&LCD_user, (const char *)" *Not Entered* ");
		Alarm_correctID_blink();
		LCD_clearscreen(&LCD_user);
		return;
	}
	else if(isAuthentic == 0)
	{
		LCD_sendstring(&LCD_user, (const char *)"   *Wrong ID*   ");
		Alarm_wrongID_blink();
		LCD_clearscreen(&LCD_user);
		return;
	}


	LCD_sendstring(&LCD_user, (const char *)"  *Correct ID*  ");

	Servo2_Exit_Gate(SERVO_UP);
	Alarm_correctID_blink();
	Alarm_correctID_on();
	MCAL_Timer2_dms(200);

	while(PIR_exit() == PIR_DETECTED);
	Servo2_Exit_Gate(SERVO_DOWN);
	Alarm_correctID_blink();
	Alarm_correctID_off();

	FreeSlots++;

	LCD_clearscreen(&LCD_user);

}

void SmartParking_main(void)
{
	while(1)
	{
		if(RFID_entry_isavailable())
		{
			SmartParking_entry();
		}
		else if(RFID_exit_isavailable())
		{
			SmartParking_exit();
		}
	}
}

