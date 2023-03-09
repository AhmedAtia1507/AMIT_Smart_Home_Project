/**
 * @file UART_Config.h
 * @author Ahmed Atia (atiaa6501@gmail.com)
 * 
 * @version 1.0
 * @date 2022-12-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef UART_CONFIG_H_
#define UART_CONFIG_H_

#include "UART_Private.h"

/*          UART mode
1) UART_ASYNCHRONOUS_MODE
2) UART_SYNCHRONOUS_MODE
*/
#define UART_MODE                               UART_ASYNCHRONOUS_MODE

/*
            UART RX Complete Interrupt Status
1) UART_RX_COMPLETE_INTERRUPT_ENABLED 
2) UART_RX_COMPLETE_INTERRUPT_DISABLED
*/
#define UART_RX_COMPLETE_INTERRUPT_STATUS       UART_RX_COMPLETE_INTERRUPT_ENABLED

/*
            UART TX Complete Interrupt Status
1) UART_TX_COMPLETE_INTERRUPT_ENABLED 
2) UART_TX_COMPLETE_INTERRUPT_DISABLED
*/
#define UART_TX_COMPLETE_INTERRUPT_STATUS       UART_TX_COMPLETE_INTERRUPT_DISABLED

/*
            UART Data Register Empty Interrupt Status
1) UART_DATA_REG_EMPTY_INTERRUPT_ENABLED   
2) UART_DATA_REG_EMPTY_INTERRUPT_DISABLED 
*/
#define UART_DATA_REG_EMPTY_INTERRUPT_STATUS    UART_DATA_REG_EMPTY_INTERRUPT_DISABLED

/*    
            UART Parity choices
1) UART_PARITY_DISABLED   
2) UART_PARITY_EVEN        
3) UART_PARITY_ODD 
*/
#define UART_PARITY_STATUS                      UART_PARITY_DISABLED

/*
            UART number of stop bits
1) UART_ONE_STOP_BIT         
2) UART_TWO_STOP_BIT
*/
#define UART_STOP_BITS_NUM                      UART_ONE_STOP_BIT
/*
            UART Data Bits' number
1) UART_FIVE_DATA_BITS       
2) UART_SIX_DATA_BITS        
3) UART_SEVEN_DATA_BITS      
4) UART_EIGHT_DATA_BITS      
5) UART_NINE_DATA_BITS 
*/   
#define UART_DATA_BITS_NUM                      UART_EIGHT_DATA_BITS

/*          UART Baud Rate Choices
1) UART_BAUD_RATE_2400       
2) UART_BAUD_RATE_4800       
3) UART_BAUD_RATE_9600       
4) UART_BAUD_RATE_14400      
5) UART_BAUD_RATE_19200      
6) UART_BAUD_RATE_28800      
7) UART_BAUD_RATE_38400      
8) UART_BAUD_RATE_57600   
*/   
#define UART_BAUD_RATE                          UART_BAUD_RATE_9600
#endif /*UART_CONFIG_H_*/