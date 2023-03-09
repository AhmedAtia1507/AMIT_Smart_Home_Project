/**
 * @file BUZZER_Interface.h
 * @author Ahmed Atia (atiaa6501@gmail.com)
 * 
 * @version 1.0
 * @date 2023-02-26
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef BUZZER_INTERFACE_H_
#define BUZZER_INTERFACE_H_

/**
 * @brief: Function to initialize the Buzzer Peripheral
 * 
 */
void BUZZER_Init(void);
/**
 * @brief: Function to turn on the Buzzer Peripheral
 * 
 */
void BUZZER_On(void);
/**
 * @brief: Function to turn off the Buzzer Peripheral
 * 
 */
void BUZZER_Off(void);
#endif /*BUZZER_INTERFACE_H_*/