/**
 * @file BUZZER_Program.c
 * @author Ahmed Atia (atiaa6501@gmail.com)
 * 
 * @version 1.0
 * @date 2023-02-26
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "ATMEGA32_REG.h"
#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include "DIO_Interface.h"

#include "BUZZER_Interface.h"
#include "BUZZER_Config.h"

/**
 * @brief: Function to initialize the Buzzer Peripheral
 * 
 */
void BUZZER_Init(void)
{
    DIO_SetPinDirection(BUZZER_PORT_ID, BUZZER_PIN_ID, DIO_PIN_OUTPUT);
}
/**
 * @brief: Function to turn on the Buzzer Peripheral
 * 
 */
void BUZZER_On(void)
{
    DIO_SetPinValue(BUZZER_PORT_ID, BUZZER_PIN_ID, DIO_PIN_HIGH);
}
/**
 * @brief: Function to turn off the Buzzer Peripheral
 * 
 */
void BUZZER_Off(void)
{
    DIO_SetPinValue(BUZZER_PORT_ID, BUZZER_PIN_ID, DIO_PIN_LOW);
}