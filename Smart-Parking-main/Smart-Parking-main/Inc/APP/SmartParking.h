

#ifndef APP_SMART_PARKING_H_
#define APP_SMART_PARKING_H_

/**
 * @brief Initializes the Smart Parking system.
 *
 * This function initializes Smart Parking system.
 */
void SmartParking_init(void);

/**
 * @brief Main function for the Smart Parking system.
 *
 * This function is the main entry point of the Smart Parking application.
 * It runs the main loop that continuously monitors RFID and branches to entry
 * process or exit process
 */
void SmartParking_main(void);

#endif /* APP_SMART_PARKING_H_ */
