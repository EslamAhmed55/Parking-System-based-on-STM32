

#ifndef HAL_HAL_H_
#define HAL_HAL_H_

/**
 * @brief Initialize the Hardware Abstraction Layer (HAL).
 *
 * This function initializes the hardware peripherals and settings specific to the
 * target hardware platform. It sets up the hardware interface, such as KPAD, LCD
 * PIR, etc., required for the application to interact with the hardware.
 *
 * @note This function should be called at the beginning of the application After
 * MCAL initialization
 */
void HAL_init(void);

#endif /* HAL_HAL_H_ */
