

#ifndef HAL_KEYPAD_H_
#define HAL_KEYPAD_H_

/**
 * @file Keypad.h
 * @brief Header file for the Keypad module.
 *
 * This file contains the declarations of functions and macros
 * related to the Keypad module.
 */

#include "MCAL/Stm32_F103C6_GPIO.h"

/**
 * @brief GPIO Port for the Keypad pins.
 *
 * This macro defines the GPIO port to which the Keypad is connected.
 * Modify this macro to change the GPIO port for the Keypad.
 */
#define KPAD_PORT GPIOB

/**
 * @brief Keypad Rows
 *
 * These macros define the GPIO pins for the Keypad rows.
 * Modify these macros to change the GPIO pins for the Keypad rows.
 */
#define KPAD_R0 GPIO_PIN_0
#define KPAD_R1 GPIO_PIN_1
#define KPAD_R2 GPIO_PIN_3
#define KPAD_R3 GPIO_PIN_4

/**
 * @brief Keypad Columns
 *
 * These macros define the GPIO pins for the Keypad columns.
 * Modify these macros to change the GPIO pins for the Keypad columns.
 */
#define KPAD_C0 GPIO_PIN_5
#define KPAD_C1 GPIO_PIN_6
#define KPAD_C2 GPIO_PIN_7

/**
 * @brief Initialize the Keypad module.
 *
 * This function initializes the Keypad module by configuring the
 * required GPIO pins and any other necessary setup.
 */
void KPAD_init();

/**
 * @brief Get the character from the Keypad.
 *
 * This function reads the current state of the Keypad and returns the
 * character corresponding to the pressed key.
 *
 * @note This function assumes that only one key is pressed at a time.
 *
 * @return The character corresponding to the pressed key.
 *         If no key is pressed, it returns '\0' (null character).
 */
char KPAD_Get_Char();

#endif /* HAL_KEYPAD_H_ */
