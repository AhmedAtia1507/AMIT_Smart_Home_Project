/**
 * @file LCD_Program.c
 * @author Ahmed Atia (atiaa6501@gmail.com)
 * 
 * @version 1.0
 * @date 2022-11-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#include "ATMEGA32_REG.h"
#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include "DIO_Interface.h"

#include "LCD_Interface.h"
#include "LCD_Private.h"
#include "LCD_Config.h"

#define F_CPU   16000000UL
#include <util/delay.h>

/**
 * @brief: Function to initialize the LCD
 * 
 */
void LCD_Init(void)
{
    DIO_SetPinDirection(LCD_RS_PORT_ID, LCD_RS_PIN_ID, DIO_PIN_OUTPUT);
    DIO_SetPinDirection(LCD_RW_PORT_ID, LCD_RW_PIN_ID, DIO_PIN_OUTPUT);
    DIO_SetPinDirection(LCD_E_PORT_ID, LCD_E_PIN_ID, DIO_PIN_OUTPUT);
    DIO_SetPinDirection(LCD_INPUT_PORTS_ID, LCD_D4_PIN_ID, DIO_PIN_OUTPUT);
    DIO_SetPinDirection(LCD_INPUT_PORTS_ID, LCD_D5_PIN_ID, DIO_PIN_OUTPUT);
    DIO_SetPinDirection(LCD_INPUT_PORTS_ID, LCD_D6_PIN_ID, DIO_PIN_OUTPUT);
    DIO_SetPinDirection(LCD_INPUT_PORTS_ID, LCD_D7_PIN_ID, DIO_PIN_OUTPUT);
    _delay_ms(35);

    LCD_WriteCommand4Bit(MODE_4_BIT);
    _delay_ms(1);
    
    LCD_WriteCommand4Bit(FUNCTION_SET_COMMAND);
    _delay_ms(1);

    LCD_WriteCommand4Bit(DISPLAY_SET_COMMAND);
    _delay_ms(1);

    LCD_ClearDisplay();
    _delay_ms(2);

    LCD_WriteCommand4Bit(FIRST_LINE_OFFSET);
    _delay_ms(2);
}
/**
 * @brief: Function to write a command in the LCD
 * 
 * @param Copy_u8Command: The command to be written
 */
void LCD_WriteCommand4Bit(u8 Copy_u8Command)
{
    DIO_SetPinValue(LCD_RS_PORT_ID, LCD_RS_PIN_ID, DIO_PIN_LOW);
    DIO_SetPinValue(LCD_RW_PORT_ID, LCD_RW_PIN_ID, DIO_PIN_LOW);
    _delay_ms(2);

    DIO_WriteHalfPort(LCD_INPUT_PORTS_ID, LCD_D4_PIN_ID, (Copy_u8Command >> 4));
    _delay_ms(2);
    LCD_Peek();
    _delay_ms(2);

    DIO_WriteHalfPort(LCD_INPUT_PORTS_ID, LCD_D4_PIN_ID, (Copy_u8Command & 0x0F));
    _delay_ms(2);
    LCD_Peek();
    _delay_ms(2);
}
/**
 * @brief: Function to display a character in the LCD
 * 
 * @param Copy_u8Char: The character to be displayed
 */
void LCD_WriteChar4Bit(u8 Copy_u8Char)
{
    DIO_SetPinValue(LCD_RS_PORT_ID, LCD_RS_PIN_ID, DIO_PIN_HIGH);
    DIO_SetPinValue(LCD_RW_PORT_ID, LCD_RW_PIN_ID, DIO_PIN_LOW);
    _delay_ms(2);

    DIO_WriteHalfPort(LCD_INPUT_PORTS_ID, LCD_D4_PIN_ID, (Copy_u8Char >> 4));
    _delay_ms(2);
    LCD_Peek();
    _delay_ms(2);

    DIO_WriteHalfPort(LCD_INPUT_PORTS_ID, LCD_D4_PIN_ID, (Copy_u8Char & 0x0F));
    _delay_ms(2);
    LCD_Peek();
    _delay_ms(2);
}
/**
 * @brief: Function to change the LCD cursor's position
 * 
 * @param Copy_u8RowID: The ID of the row in which the cursor will be in (first row or second row) 
 * @param Copy_u8ColumnID: The ID of the column in which the cursor will be in
 */
void LCD_SetCursorPosition(u8 Copy_u8RowID, u8 Copy_u8ColumnID)
{
    if(Copy_u8RowID == LCD_FIRST_ROW || Copy_u8RowID == LCD_SECOND_ROW)
    {
        if(Copy_u8ColumnID >= 0 && Copy_u8ColumnID <= 15)
        {
            u8 Loc_u8CursorPos = 0;
            switch (Copy_u8RowID)
            {
                case LCD_FIRST_ROW:
                {
                    Loc_u8CursorPos = FIRST_LINE_OFFSET;
                    break;
                }
                case LCD_SECOND_ROW:
                {
                    Loc_u8CursorPos = SECOND_LINE_OFFSET;
                    break;
                }
                default:
                {
                    /*Do nothing*/
                    break;
                }
            }
            Loc_u8CursorPos += Copy_u8ColumnID;
            LCD_WriteCommand4Bit(Loc_u8CursorPos);
        }
    }
    else
    {
        /*Do nothing*/
    }
}
/**
 * @brief: Function to Display a string in the LCD
 * 
 * @param P_u8String: The String to be displayed
 */
void LCD_WriteString(u8* P_u8String)
{
    if(P_u8String != NULL)
    {
        u8 Loc_u8Index = 0;
        while(P_u8String[Loc_u8Index] != '\0')
        {
            LCD_WriteChar4Bit(P_u8String[Loc_u8Index]);
            Loc_u8Index++;
        }
    }
    else
    {
        /*Do Nothing*/
    }
}
/**
 * @brief: Function to display an integer in the LCD
 * 
 * @param Copy_u32Value: The integer value to be displayed
 */
void LCD_WriteIntegerValue(u32 Copy_u32Value)
{
    if(Copy_u32Value == 0)
    {
        LCD_WriteChar4Bit((Copy_u32Value + 48));
    }
    else
    {
        u32 Loc_u8TempValue = Copy_u32Value;
        u8 Loc_u8CharArray[20] = {0},Loc_u8Count = 0, Loc_u8Index = 0;
        while(Loc_u8TempValue != 0)
        {
            Loc_u8CharArray[Loc_u8Count] = ((Loc_u8TempValue % 10) + 48);
            Loc_u8TempValue /= 10;
            Loc_u8Count++;
        }
        
        for(Loc_u8Index = 0; Loc_u8Index < Loc_u8Count; Loc_u8Index++)
        {
            LCD_WriteChar4Bit(Loc_u8CharArray[Loc_u8Count - Loc_u8Index - 1]);
        }
    }
}
/**
 * @brief: Function to toggle the enable pin of the LCD for a short amount of time
 * 
 */
void LCD_Peek(void)
{
    DIO_SetPinValue(LCD_E_PORT_ID, LCD_E_PIN_ID, DIO_PIN_HIGH);
    _delay_ms(1);
    DIO_SetPinValue(LCD_E_PORT_ID, LCD_E_PIN_ID, DIO_PIN_LOW);
}
/**
 * @brief: Function to clear the LCD display
 * 
 */
void LCD_ClearDisplay(void)
{
    LCD_WriteCommand4Bit(CLEAR_DISPLAY);
}