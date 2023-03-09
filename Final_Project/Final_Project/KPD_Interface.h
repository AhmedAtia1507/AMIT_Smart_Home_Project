/**
 * @file KPD_Interface.h
 * @author Ahmed Atia (atiaa6501@gmail.com)
 * 
 * @version 1.0
 * @date 2022-10-29
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef KPD_INTERFACE_H_
#define KPD_INTERFACE_H_

#define NO_COLUMNS      4
#define NO_ROWS         4

#define KPD_NOT_PRESSED 255
#define KPD_PRESSED     DIO_PIN_LOW
/**
 * @brief: Function to initialize the keypad
 *         (Set the directions and the initial values of the pins connected to the keypad)
 * 
 */
void KPD_Init       (void);
/**
 * @brief: Function to get the pressed button in the keypad
 * 
 * @param P_u8ReturnedValue: Pointer to put the pressed button in it 
 */
void KPD_GetValue   (u8* P_u8ReturnedValue);
#endif /*KPD_INTERFACE_H_*/