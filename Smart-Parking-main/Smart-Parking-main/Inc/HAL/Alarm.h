

#ifndef HAL_ALARM_H_
#define HAL_ALARM_H_

#include "MCAL/Stm32_F103C6_GPIO.h"

/** @defgroup Alarm_GPIO Alarm GPIO Pins
 * @{ */

/** @brief GPIO port for the correct ID LED. */
#define ALARM_CORRECID_PORT GPIOA
/** @brief GPIO pin for the correct ID LED. */
#define ALARM_CORRECID_PIN GPIO_PIN_11

/** @brief GPIO port for the wrong ID LED. */
#define ALARM_WRONGID_PORT GPIOA
/** @brief GPIO pin for the wrong ID LED. */
#define ALARM_WRONGID_PIN GPIO_PIN_0

/** @} */

/** @defgroup Alarm_Config Alarm Configuration
 * @{ */

/** @brief Number of blinks for alarm LEDs (blinks every ALARM_BLINK_MS). */
#define ALARM_NUM_BLINKS 6
/** @brief Time of every blink for alarm LEDs. */
#define ALARM_BLINK_MS 50

/** @} */

/**
 * @brief Initializes the alarm system.
 *
 * This function should be called before using any other alarm-related functions.
 * It initializes the GPIO pins for the correct and wrong ID LEDs.
 */
void Alarm_init();

/**
 * @brief Turns on the correct ID LED.
 *
 * This function turns on the correct ID LED, indicating that the ID is correct.
 */
void Alarm_correctID_on(void);

/**
 * @brief Turns off the correct ID LED.
 *
 * This function turns off the correct ID LED, indicating that the ID is no longer correct.
 */
void Alarm_correctID_off(void);

/**
 * @brief Blinks the correct ID LED.
 *
 * This function blinks the correct ID LED a specified number of times with a ALARM_BLINK_MS duration per blink.
 * The number of blinks and duration are specified by the constants ALARM_NUM_BLINKS and ALARM_BLINK_MS, respectively.
 */
void Alarm_correctID_blink(void);

/**
 * @brief Turns on the wrong ID LED.
 *
 * This function turns on the wrong ID LED, indicating that the ID is wrong.
 */
void Alarm_wrongID_on(void);

/**
 * @brief Turns off the wrong ID LED.
 *
 * This function turns off the wrong ID LED, indicating that the ID is no longer wrong.
 */
void Alarm_wrongID_off(void);

/**
 * @brief Blinks the wrong ID LED.
 *
 * This function blinks the wrong ID LED a specified number of times with a ALARM_BLINK_MS duration per blink.
 * The number of blinks and duration are specified by the constants ALARM_NUM_BLINKS and ALARM_BLINK_MS, respectively.
 */
void Alarm_wrongID_blink(void);

#endif /* HAL_ALARM_H_ */
