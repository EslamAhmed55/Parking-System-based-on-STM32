

#ifndef LCD_H_
#define LCD_H_

/**
 * @file HAL_LCD.h
 * @brief Header file for the LCD (Liquid Crystal Display) module.
 *
 * This file contains the declarations of functions, enumerations, and data structures
 * related to the LCD module.
 */

#include "stdint.h"
#include "MCAL/Stm32_F103C6_GPIO.h"

/**
 * @brief Number of digits per line on the LCD.
 *
 * This macro defines the number of characters that can be displayed in a single line
 * on the LCD. Modify this macro to change the number of characters per line.
 */
#define LINE_DIGITS 16

/**
 * @brief Enumeration for the shift direction of the LCD.
 *
 * This enumeration defines the possible shift directions for the LCD display and cursor.
 */
typedef enum{
    CURSOR_LEFT  = 0x00, /**< Shift the cursor to the left. */
    CURSOR_RIGHT = 0x04, /**< Shift the cursor to the right. */
    DISP_LEFT    = 0x08, /**< Shift the entire display to the left. */
    DISP_RIGHT   = 0x0c  /**< Shift the entire display to the right. */
} e_ShiftDir_t;

/**
 * @brief Enumeration for the entry mode of the LCD.
 *
 * This enumeration defines the possible entry modes for the LCD.
 */
typedef enum{
    NOSHIFT_DECREMENT = 0, /**< Entry mode: No shift and decrement cursor position. */
    SHIFT_DECREMENT   = 1, /**< Entry mode: Shift cursor to the left and decrement cursor position. */
    NOSHIFT_INCREMENT = 2, /**< Entry mode: No shift and increment cursor position. */
    SHIFT_INCREMENT   = 3  /**< Entry mode: Shift cursor to the right and increment cursor position. */
} e_EntryMode_t;

/**
 * @brief Enumeration for the display control of the LCD.
 *
 * This enumeration defines the possible display control options for the LCD.
 */
typedef enum{
    OFFDISP_OFFCURSOR    = 0x00, /**< Display off, cursor off. */
    ONDISP_OFFCURSOR     = 0x04, /**< Display on, cursor off. */
    ONDISP_ONCURSOR      = 0x06, /**< Display on, cursor on. */
    ONDISP_BLINKCURSOR   = 0x07  /**< Display on, cursor blinking. */
} e_DispCtrl_t;

/**
 * @brief Enumeration for the operating mode of the LCD.
 *
 * This enumeration defines the possible operating modes (data length and lines) for the LCD.
 */
typedef enum{
    FOURBIT_1LINE_7DOT    = 0x00, /**< 4-bit data, 1-line display, 5x7 dot character font. */
    FOURBIT_1LINE_10DOT   = 0x04, /**< 4-bit data, 1-line display, 5x10 dot character font. */
    FOURBIT_2LINE_7DOT    = 0x08, /**< 4-bit data, 2-line display, 5x7 dot character font. */
    FOURBIT_2LINE_10DOT   = 0x0C, /**< 4-bit data, 2-line display, 5x10 dot character font. */
    EIGHTBIT_1LINE_7DOT   = 0x10, /**< 8-bit data, 1-line display, 5x7 dot character font. */
    EIGHTBIT_1LINE_10DOT  = 0x14, /**< 8-bit data, 1-line display, 5x10 dot character font. */
    EIGHTBIT_2LINE_7DOT   = 0x18, /**< 8-bit data, 2-line display, 5x7 dot character font. */
    EIGHTBIT_2LINE_10DOT  = 0x1C  /**< 8-bit data, 2-line display, 5x10 dot character font. */
} e_OperMode_t;

/**
 * @brief Data structure for the data pins of the LCD.
 *
 * This structure defines the GPIO port and the starting pin number
 * for the data pins of the LCD.
 */
typedef struct {
    GPIO_TypeDef *GPIOX;    /**< GPIO port for the data pins. */
    uint16_t DataPinStart;  /**< The pin number of the lowest data pin. */
} s_LCDDataPins_t;

/**
 * @brief Data structure for the control pins of the LCD.
 *
 * This structure defines the GPIO port and the pin numbers for the
 * register select (RS) pin and the enable (EN) pin of the LCD.
 */
typedef struct {
    GPIO_TypeDef *GPIOX;    /**< GPIO port for the control pins. */
    uint16_t rspin;         /**< Register select (RS) pin number. */
    uint16_t enpin;         /**< Enable (EN) pin number. */
} s_LCDCtrlPins_t;

/**
 * @brief Configuration structure for the LCD module.
 *
 * This structure holds the configuration parameters for the LCD module.
 */
typedef struct {
    s_LCDCtrlPins_t s_LCDCtrlPins; /**< Control pins configuration. */
    s_LCDDataPins_t s_LCDDataPins; /**< Data pins configuration. */
    e_EntryMode_t e_EntryMode;     /**< Entry mode configuration. */
    e_DispCtrl_t e_DispCtrl;       /**< Display control configuration. */
    e_OperMode_t e_OperMode;       /**< Operating mode (data length and lines) configuration. */
    uint8_t Ch_Counter;            /**< Internal character counter. */
} s_LCD_Config_t;

/**
 * @brief Enumeration for the type of character to be sent to the LCD.
 *
 * This enumeration defines the possible types of characters that can be sent to the LCD,
 * either a command or data (character to be displayed).
 */
typedef enum {
    COMMAND, /**< The character to be sent is a command to the LCD. */
    DATA     /**< The character to be sent is data to be displayed on the LCD. */
} e_LCDCharType_t;

/**
 * @brief Admin LCD configuration for the LCD module.
 *
 * This variable represents the admin LCD's configuration that's used to initialize the admin LCD
 * @note You must not edit this variable.
 */
extern s_LCD_Config_t LCD_admin;

/**
 * @brief Entry configuration for the LCD module.
 *
 * This variable represents the entry gate LCD's configuration to initialize the entry gate LCD
 * @note You must not edit this variable.
 *
 */
extern s_LCD_Config_t LCD_user;

/**
 * @brief Initialize the LCD module.
 *
 * This function initializes the LCD module based on the provided configuration.
 *
 * @param LCD Pointer to the LCD configuration structure.
 */
void LCD_init(s_LCD_Config_t *LCD);

/**
 * @brief Display a character or send a command to the LCD.
 *
 * This function sends a character or a command to the LCD module based on the
 * specified character type (data or command).
 *
 * @param LCD Pointer to the LCD configuration structure.
 * @param data The character or command to be sent to the LCD.
 * @param e_LCDCharType Character type (DATA or COMMAND).
 */
void LCD_sendchar(s_LCD_Config_t *LCD, unsigned char data, e_LCDCharType_t e_LCDCharType);

/**
 * @brief Display a string on the LCD.
 *
 * This function displays the whole string on the LCD module.
 *
 * @param LCD Pointer to the LCD configuration structure.
 * @param data The string to be displayed on the LCD.
 */
void LCD_sendstring(s_LCD_Config_t *LCD, const char *data);

/**
 * @brief Check the busy flag of the LCD.
 *
 * This function checks the busy flag of the LCD to determine if the LCD is busy
 * processing a command.
 *
 * @note This function may not work in 4-bit mode.
 *
 * @param LCD Pointer to the LCD configuration structure.
 */
void LCDIsbusy(s_LCD_Config_t *LCD);

/**
 * @brief Clear the LCD screen.
 *
 * This function clears the entire content of the LCD screen.
 *
 * @param LCD Pointer to the LCD configuration structure.
 */
void LCD_clearscreen(s_LCD_Config_t *LCD);

/**
 * @brief Return the cursor to the home position (0, 0).
 *
 * This function moves the cursor to the home position (0, 0) of the LCD.
 *
 * @param LCD Pointer to the LCD configuration structure.
 */
void LCD_returnhome(s_LCD_Config_t *LCD);

/**
 * @brief Move the cursor to the specified position.
 *
 * This function moves the cursor to the specified position on the LCD.
 *
 * @param LCD Pointer to the LCD configuration structure.
 * @param x The column position (0 to 15).
 * @param y The row position (0 or 1 for two-line LCD).
 */
void LCD_gotoxy(s_LCD_Config_t *LCD, unsigned char x, unsigned char y);

/**
 * @brief Build a custom character for the LCD.
 *
 * This function builds a custom character at the specified location in the LCD
 * character generator RAM. The custom character can later be displayed on the LCD.
 *
 * @param LCD Pointer to the LCD configuration structure.
 * @param location The location (0 to 7) to store the custom character.
 * @param pattern Pointer to the pattern data for the custom character.
 */
void LCD_buildcustom(s_LCD_Config_t *LCD, unsigned char location, const unsigned char *pattern);

/**
 * @brief Display a custom character on the LCD.
 *
 * This function displays a custom character stored in the character generator RAM
 * at the specified location on the LCD.
 *
 * @param LCD Pointer to the LCD configuration structure.
 * @param location The location (0 to 7) of the custom character in the character generator RAM.
 */
void LCD_dispcustom(s_LCD_Config_t *LCD, unsigned char location);

/**
 * @brief Shift the display and/or cursor.
 *
 * This function shifts the display and/or cursor to the left or right based on the specified direction.
 *
 * @param LCD Pointer to the LCD configuration structure.
 * @param e_ShiftDir Shift direction for the display and/or cursor.
 */
void LCD_shift(s_LCD_Config_t *LCD, e_ShiftDir_t e_ShiftDir);

#endif /* LCD_H_ */
