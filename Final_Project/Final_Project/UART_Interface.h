/**
 * @file UART_Interface.h
 * @author Ahmed Atia (atiaa6501@gmail.com)
 * 
 * @version 1.0
 * @date 2022-12-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_

typedef void (*ptr_to_func_t)(void);
/**
 * @brief: Function to initialize the UART interface
 * 
 */
void UART_Init                      (void);
/**
 * @brief: Function to transmit a character using UART protocol
 * 
 * @param Copy_u8TxChar: Character to be transmitted
 */
void UART_TxChar                    (u8 Copy_u8TxChar);
/**
 * @brief: Function to transmit a character using UART protocol (Interrupt Enabled)
 * 
 * @param Copy_u8TxChar: Character to be transmitted
 */
void UART_TxCharAsynchronous        (u8 Copy_u8TxChar);
/**
 * @brief: Function to receive a character from another device using UART
 * 
 * @param P_u8RxChar: Character received
 */
void UART_RxChar                    (u8* P_u8RxChar);
/**
 * @brief: Function to receive a character from another device using UART (Interrupt Enabled)
 * 
 * @param P_u8RxChar: Character received 
 */
void UART_RxCharAsynchronous        (u8* P_u8RxChar);
/**
 * @brief: Function to transmit a string using UART
 * 
 * @param P_u8TxString: String to be transmitted
 */
void UART_TxString                  (u8* P_u8TxString);
/**
 * @brief: Function to receive a string from another device using UART
 * 
 * @param P_u8RxString: String to be received
 */
void UART_RxString                  (u8* P_u8RxString);
/**
 * @brief: Function to set the callback function for the UART Tx Complete Interrupt Callback Function
 * 
 * @param P_TxCompleteSetCallback: The callback function to be set
 */
void UART_TxCompleteSetCallback     (ptr_to_func_t P_TxCompleteSetCallback);
/**
 * @brief: Function to set the callback function for the UART Rx Complete Interrupt Callback Function
 * 
 * @param P_RxCompleteSetCallback: The callback function to be set 
 */
void UART_RxCompleteSetCallback     (ptr_to_func_t P_RxCompleteSetCallback);
/**
 * @brief: Function to set the callback function for the UART Data Register Empty Interrupt Callback Function
 * 
 * @param P_DataRegEmptySetCallback: The callback function to be set 
 */
void UART_DataRegEmptySetCallback   (ptr_to_func_t P_DataRegEmptySetCallback);
#endif /*UART_INTERFACE_H_*/