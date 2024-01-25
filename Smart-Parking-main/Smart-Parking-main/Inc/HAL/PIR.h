

#ifndef HAL_PIR_H_
#define HAL_PIR_H_

/**
 * @file PIR.h
 * @brief Header file for the PIR (Passive Infrared) sensor module.
 *
 * This file contains the declarations of functions and enumerations
 * related to the PIR sensor module.
 */

/**
 * @brief Enumeration for the PIR sensor status.
 *
 * This enumeration defines the possible states of the PIR sensor.
 */
typedef enum
{
    PIR_NOT_DETECTED, /**< PIR sensor is not detecting any movement. */
    PIR_DETECTED      /**< PIR sensor has detected movement. */
} e_PIRStatus_t;

/**
 * @brief GPIO Port for the PIR sensor pins.
 *
 * This macro defines the GPIO port to which the PIR sensor is connected.
 * Modify this macro to change the GPIO port.
 */
#define PIR_GPIOx    GPIOA

/**
 * @brief Pin for the PIR entry sensor.
 *
 * This macro defines the GPIO pin for the PIR entry sensor.
 * Modify this macro to change the GPIO pin for the PIR entry sensor.
 */
#define PIR_ENTRY_PIN GPIO_PIN_7

/**
 * @brief Pin for the PIR exit sensor.
 *
 * This macro defines the GPIO pin for the PIR exit sensor.
 * Modify this macro to change the GPIO pin for the PIR exit sensor.
 */
#define PIR_EXIT_PIN  GPIO_PIN_1

/**
 * @brief Initialize the PIR sensor module.
 *
 * This function initializes the PIR sensor module by configuring the
 * required GPIO pins and any other necessary setup.
 */
void PIR_init(void);

/**
 * @brief Check the PIR entry sensor status.
 *
 * This function checks the status of the PIR entry sensor to determine
 * if any movement is detected at the entry gate.
 *
 * @return The status of the PIR entry sensor (PIR_DETECTED or PIR_NOT_DETECTED).
 */
e_PIRStatus_t PIR_entry(void);

/**
 * @brief Check the PIR exit sensor status.
 *
 * This function checks the status of the PIR exit sensor to determine
 * if any movement is detected at the exit gate.
 *
 * @return The status of the PIR exit sensor (PIR_DETECTED or PIR_NOT_DETECTED).
 */
e_PIRStatus_t PIR_exit(void);

#endif /* HAL_PIR_H_ */
