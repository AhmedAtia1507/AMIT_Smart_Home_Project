/**
 * @file UART_Private.h
 * @author Ahmed Atia (atiaa6501@gmail.com)
 * 
 * @version 1.0
 * @date 2022-12-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef UART_PRIVATE_H_
#define UART_PRIVATE_H_

/*********************UCSRA bit names*********************/
/*Multi-processor Communication Mode*/
#define MPCM                                    0
/*Double the UART Transmission Speed*/
#define U2X                                     1
/*Parity Error*/
#define PE                                      2
/*Data OverRun*/
#define DOR                                     3
/*Frame Error*/
#define FE                                      4
/*UART Data Register Empty*/
#define UDRE                                    5
/*UART Transmit Complete*/
#define TXC                                     6
/*UART Receive Complete*/
#define RXC                                     7

/*********************UCSRB bit names*********************/
/*Transmit Data Bit 8*/
#define TXB8                                    0
/*Receive Data Bit 8*/
#define RXB8                                    1
/*Character Size*/
#define UCSZ2                                   2
/*Transmitter Enable*/
#define TXEN                                    3
/*Receiver Enable*/
#define RXEN                                    4
/*UART Data Register Empty Interrupt Enable*/
#define UDRIE                                   5
/*TX Complete Interrupt Enable*/
#define TXCIE                                   6
/*RX Complete Interrupt Enable*/
#define RXCIE                                   7

/*********************UCSRC bit names*********************/
/*Clock Polarity*/          
#define UCPOL                                   0
/*Character Size*/          
#define UCSZ0                                   1
/*Character Size*/          
#define UCSZ1                                   2
/*Stop Bit Select*/         
#define USBS                                    3
/*Parity Mode*/         
#define UPM0                                    4
/*Parity Mode*/         
#define UPM1                                    5
/*UART Mode Select*/            
#define UMSEL                                   6
/*Register Select*/         
#define URSEL                                   7

/*UART mode*/           
#define UART_ASYNCHRONOUS_MODE                  1
#define UART_SYNCHRONOUS_MODE                   2

/*UART RX Complete Interrupt Status*/
#define UART_RX_COMPLETE_INTERRUPT_ENABLED      1
#define UART_RX_COMPLETE_INTERRUPT_DISABLED     2

/*UART TX Complete Interrupt Status*/
#define UART_TX_COMPLETE_INTERRUPT_ENABLED      1
#define UART_TX_COMPLETE_INTERRUPT_DISABLED     2

/*UART Data Register Empty Interrupt Status*/
#define UART_DATA_REG_EMPTY_INTERRUPT_ENABLED   1
#define UART_DATA_REG_EMPTY_INTERRUPT_DISABLED  2

/*UART Parity choices*/
#define UART_PARITY_DISABLED                    1
#define UART_PARITY_EVEN                        2
#define UART_PARITY_ODD                         3

/*UART number of stop bits*/            
#define UART_ONE_STOP_BIT                       1
#define UART_TWO_STOP_BIT                       2

/*UART Data Bits' number*/          
#define UART_FIVE_DATA_BITS                     1
#define UART_SIX_DATA_BITS                      2
#define UART_SEVEN_DATA_BITS                    3
#define UART_EIGHT_DATA_BITS                    4
#define UART_NINE_DATA_BITS                     5


/*UART Baud Rate Choices*/          
#define UART_BAUD_RATE_2400                     416
#define UART_BAUD_RATE_4800                     207
#define UART_BAUD_RATE_9600                     103
#define UART_BAUD_RATE_14400                    68
#define UART_BAUD_RATE_19200                    51
#define UART_BAUD_RATE_28800                    34
#define UART_BAUD_RATE_38400                    25
#define UART_BAUD_RATE_57600                    16


#endif /*UART_PRIVATE_H_*/