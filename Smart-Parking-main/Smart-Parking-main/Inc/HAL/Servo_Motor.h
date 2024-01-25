

#ifndef HAL_SERVO_MOTOR_H_
#define HAL_SERVO_MOTOR_H_

/**
 * @file Servo_Motor.h
 * @brief Header file for the Servo Motor module.
 *
 * This file contains the declarations of functions and enumerations
 * related to the Servo Motor module.
 */

#include "MCAL/stm32f103x6.h"
#include "MCAL/Stm32_F103C6_GPIO.h"
#include "MCAL/Stm32_F103C6_Timer.h"

/**
 * @brief Enumeration for the direction of the Servo Motor.
 *
 * This enumeration defines the possible directions of the Servo Motor,
 * either SERVO_UP or SERVO_DOWN.
 */
typedef enum {
    SERVO_UP = 1,    /**< Servo Motor direction: Up. */
    SERVO_DOWN = 2   /**< Servo Motor direction: Down. */
} e_ServoMotor_Direction_t;

/**
 * @brief Initialize Servo Motor for the Entry Gate.
 *
 * This function initializes the Servo Motor connected to the Entry Gate
 * by configuring the required GPIO pins and any other necessary setup.
 */
void Servo1_Entry_Gate_Init(void);

/**
 * @brief Control the Servo Motor for the Entry Gate.
 *
 * This function controls the Servo Motor connected to the Entry Gate
 * to move it in the specified direction (SERVO_UP or SERVO_DOWN).
 *
 * @param Direction The direction to move the Servo Motor (SERVO_UP or SERVO_DOWN).
 */
void Servo1_Entry_Gate(e_ServoMotor_Direction_t Direction);

/**
 * @brief Initialize Servo Motor for the Exit Gate.
 *
 * This function initializes the Servo Motor connected to the Exit Gate
 * by configuring the required GPIO pins and any other necessary setup.
 */
void Servo2_Exit_Gate_Init(void);

/**
 * @brief Control the Servo Motor for the Exit Gate.
 *
 * This function controls the Servo Motor connected to the Exit Gate
 * to move it in the specified direction (SERVO_UP or SERVO_DOWN).
 *
 * @param Direction The direction to move the Servo Motor (SERVO_UP or SERVO_DOWN).
 */
void Servo2_Exit_Gate(e_ServoMotor_Direction_t Direction);

#endif /* HAL_SERVO_MOTOR_H_ */
