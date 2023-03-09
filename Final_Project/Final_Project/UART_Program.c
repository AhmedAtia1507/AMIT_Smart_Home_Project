/**
 * @file UART_Program.c
 * @author Ahmed Atia (atiaa6501@gmail.com)
 * 
 * @version 1.0
 * @date 2022-12-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "ATMEGA32_REG.h"
#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include "UART_Config.h"
#include "UART_Private.h"
#include "UART_Interface.h"

static ptr_to_func_t UART_TxComplete_PCallback = NULL;
static ptr_to_func_t UART_RxComplete_PCallback = NULL;
static ptr_to_func_t UART_DataRegEmpty_PCallback = NULL;

/**
 * @brief: Function to initialize the UART interface
 * 
 */
void UART_Init(void)
{
    u8 Loc_u8UCSRC = 0;

    SET_BIT(Loc_u8UCSRC, URSEL); //Writing the UCSRC

    #if UART_ASYNCHRONOUS_MODE == UART_MODE
        CLEAR_BIT(Loc_u8UCSRC, UMSEL);
    #elif UART_SYNCHRONOUS_MODE == UART_MODE
        SET_BIT(Loc_u8UCSRC, UMSEL);
    #else
        /*Do nothing*/
    #endif

    #if UART_PARITY_DISABLED == UART_PARITY_STATUS
        CLEAR_BIT(Loc_u8UCSRC, UPM0);
        CLEAR_BIT(Loc_u8UCSRC, UPM1);
    #elif UART_PARITY_EVEN == UART_PARITY_STATUS
        CLEAR_BIT(Loc_u8UCSRC, UPM0);
        SET_BIT(Loc_u8UCSRC, UPM1);
    #elif UART_PARITY_ODD == UART_PARITY_STATUS
        SET_BIT(Loc_u8UCSRC, UPM0);
        SET_BIT(Loc_u8UCSRC, UPM1);
    #else
        /*Do nothing*/
    #endif

    #if UART_ONE_STOP_BIT == UART_STOP_BITS_NUM
        CLEAR_BIT(Loc_u8UCSRC, USBS);
    #elif UART_TWO_STOP_BIT == UART_STOP_BITS_NUM
        SET_BIT(Loc_u8UCSRC, USBS);
    #else
        /*Do nothing*/
    #endif

    #if  UART_FIVE_DATA_BITS == UART_DATA_BITS_NUM
        CLEAR_BIT(Loc_u8UCSRC, UCSZ0);
        CLEAR_BIT(Loc_u8UCSRC, UCSZ1);
        CLEAR_BIT(UCSRB, UCSZ2);
    #elif UART_SIX_DATA_BITS == UART_DATA_BITS_NUM
        SET_BIT(Loc_u8UCSRC, UCSZ0);
        CLEAR_BIT(Loc_u8UCSRC, UCSZ1);
        CLEAR_BIT(UCSRB, UCSZ2);
    #elif UART_SEVEN_DATA_BITS == UART_DATA_BITS_NUM
        CLEAR_BIT(Loc_u8UCSRC, UCSZ0);
        SET_BIT(Loc_u8UCSRC, UCSZ1);
        CLEAR_BIT(UCSRB, UCSZ2);
    #elif UART_EIGHT_DATA_BITS == UART_DATA_BITS_NUM
        SET_BIT(Loc_u8UCSRC, UCSZ0);
        SET_BIT(Loc_u8UCSRC, UCSZ1);
        CLEAR_BIT(UCSRB, UCSZ2);
    #elif UART_NINE_DATA_BITS == UART_DATA_BITS_NUM
        SET_BIT(Loc_u8UCSRC, UCSZ0);
        SET_BIT(Loc_u8UCSRC, UCSZ1);
        SET_BIT(UCSRB, UCSZ2);
    #else
        /*Do nothing*/
    #endif

    UCSRC = Loc_u8UCSRC;

    u16 Loc_u16BaudRate = UART_BAUD_RATE;

    UBRRL = Loc_u16BaudRate & 0x0FF;
    UBRRH = Loc_u16BaudRate >> 8;

    #if UART_RX_COMPLETE_INTERRUPT_ENABLED == UART_RX_COMPLETE_INTERRUPT_STATUS
        SET_BIT(UCSRB, RXCIE);
    #elif UART_RX_COMPLETE_INTERRUPT_DISABLED == UART_RX_COMPLETE_INTERRUPT_STATUS
        CLEAR_BIT(UCSRB, RXCIE);
    #else
        /*Do nothing*/
    #endif

    #if UART_TX_COMPLETE_INTERRUPT_ENABLED == UART_TX_COMPLETE_INTERRUPT_STATUS
        SET_BIT(UCSRB, TXCIE);
    #elif UART_TX_COMPLETE_INTERRUPT_DISABLED == UART_TX_COMPLETE_INTERRUPT_STATUS
        CLEAR_BIT(UCSRB, TXCIE);
    #else
        /*Do nothing*/
    #endif

    #if UART_DATA_REG_EMPTY_INTERRUPT_ENABLED == UART_DATA_REG_EMPTY_INTERRUPT_STATUS
        SET_BIT(UCSRB, UDRIE);
    #elif UART_DATA_REG_EMPTY_INTERRUPT_DISABLED == UART_DATA_REG_EMPTY_INTERRUPT_STATUS
        CLEAR_BIT(UCSRB, UDRIE);
    #else
        /*Do nothing*/
    #endif

        //Enable Tx
    SET_BIT(UCSRB, TXEN);

        //Enable Rx
    SET_BIT(UCSRB, RXEN);

}

/**
 * @brief: Function to transmit a character using UART protocol
 * 
 * @param Copy_u8TxChar: Character to be transmitted
 */
void UART_TxChar(u8 Copy_u8TxChar)
{
    UDR = Copy_u8TxChar;
    while(0 == GET_BIT(UCSRA, UDRE));
}

/**
 * @brief: Function to transmit a character using UART protocol (Interrupt Enabled)
 * 
 * @param Copy_u8TxChar: Character to be transmitted
 */
void UART_TxCharAsynchronous(u8 Copy_u8TxChar)
{
    UDR = Copy_u8TxChar;
}
/**
 * @brief: Function to receive a character from another device using UART
 * 
 * @param P_u8RxChar: Character received
 */
void UART_RxChar(u8* P_u8RxChar)
{
    if(P_u8RxChar != NULL)
    {
        while(0 == GET_BIT(UCSRA, RXC));
        *P_u8RxChar = UDR;
    }
    else
    {
        /*Do nothing*/
    }
}
/**
 * @brief: Function to receive a character from another device using UART (Interrupt Enabled)
 * 
 * @param P_u8RxChar: Character received 
 */
void UART_RxCharAsynchronous(u8* P_u8RxChar)
{
    if(P_u8RxChar != NULL)
    {
        *P_u8RxChar = UDR;
    }
    else
    {
        /*Do nothing*/
    }
}
/**
 * @brief: Function to transmit a string using UART
 * 
 * @param P_u8TxString: String to be transmitted
 */
void UART_TxString(u8* P_u8TxString)
{
    if(P_u8TxString != NULL)
    {
        u8 Loc_u8Index = 0;
        while(P_u8TxString[Loc_u8Index] != '\0')
        {
            UART_TxChar(P_u8TxString[Loc_u8Index]);
            Loc_u8Index++;
        }
        /*Carriage return character "Reset device position to beginning of line"*/
        UART_TxChar(13);
    }
    else
    {
        /*Do nothing*/
    }
}

/**
 * @brief: Function to receive a string from another device using UART
 * 
 * @param P_u8RxString: String to be received
 */
void UART_RxString(u8* P_u8RxString)
{
    if(P_u8RxString != NULL)
    {
        u8 Loc_u8Index = 0;
        u8 Loc_u8ReceivedChar = 0;
        while(1)
        {
            UART_RxChar(&Loc_u8ReceivedChar);
            P_u8RxString[Loc_u8Index] = Loc_u8ReceivedChar;
            if(P_u8RxString[Loc_u8Index] == '\n')
            {
				P_u8RxString[Loc_u8Index - 1] = '\0';
                break;
            }
            else
            {
                /*Do nothing*/
            }
            Loc_u8Index++;
        }
    }
    else
    {
        /*Do nothing*/
    }
}
/**
 * @brief: Function to set the callback function for the UART Tx Complete Interrupt Callback Function
 * 
 * @param P_TxCompleteSetCallback: The callback function to be set
 */
void UART_TxCompleteSetCallback (ptr_to_func_t P_TxCompleteSetCallback)
{
    if(P_TxCompleteSetCallback != NULL)
    {
        UART_TxComplete_PCallback = P_TxCompleteSetCallback;
    }
    else
    {
        /*Do nothing*/
    }
}
/**
 * @brief: Function to set the callback function for the UART Rx Complete Interrupt Callback Function
 * 
 * @param P_RxCompleteSetCallback: The callback function to be set 
 */
void UART_RxCompleteSetCallback (ptr_to_func_t P_RxCompleteSetCallback)
{
    if(P_RxCompleteSetCallback != NULL)
    {
        UART_RxComplete_PCallback = P_RxCompleteSetCallback;
    }
    else
    {
        /*Do nothing*/
    }
}
/**
 * @brief: Function to set the callback function for the UART Data Register Empty Interrupt Callback Function
 * 
 * @param P_DataRegEmptySetCallback: The callback function to be set 
 */
void UART_DataRegEmptySetCallback   (ptr_to_func_t P_DataRegEmptySetCallback)
{
    if(P_DataRegEmptySetCallback != NULL)
    {
        UART_DataRegEmpty_PCallback = P_DataRegEmptySetCallback;
    }
    else
    {
        /*Do nothing*/
    }
}

/*ISR Function for UART Rx Complete Interrupt*/
void __vector_13(void) __attribute__ ((signal));
void __vector_13(void)
{
    if(UART_RxComplete_PCallback != NULL)
    {
        UART_RxComplete_PCallback();
    }
    else
    {
        /*Do nothing*/
    }
}

/*ISR Function for UART Data Register Empty Interrupt*/
void __vector_14(void) __attribute__ ((signal));
void __vector_14(void)
{
    if(UART_DataRegEmpty_PCallback != NULL)
    {
        UART_DataRegEmpty_PCallback();
    }
    else
    {
        /*Do nothing*/
    }
}

/*ISR Function for UART Tx Complete Interrupt*/
void __vector_15(void) __attribute__ ((signal));
void __vector_15(void)
{
    if(UART_TxComplete_PCallback != NULL)
    {
        UART_TxComplete_PCallback();
    }
    else
    {
        /*Do nothing*/
    }
}