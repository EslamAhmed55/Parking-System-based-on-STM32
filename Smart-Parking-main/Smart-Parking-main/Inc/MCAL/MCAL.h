

#ifndef MCAL_MCAL_H_
#define MCAL_MCAL_H_

/**
 * @brief Initialize the Microcontroller Abstraction Layer (MCAL).
 *
 * This function initializes the required hardware peripherals, clocks, GPIOs,
 * and other low-level settings of the microcontroller.
 *
 * @note This function should be called at the beginning of the application before
 *       any hardware-related operations are performed.
 */
void MCAL_init(void);

#endif /* MCAL_MCAL_H_ */
