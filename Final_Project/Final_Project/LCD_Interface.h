/**
 * @file LCD_Interface.h
 * @author Ahmed Atia (atiaa6501@gmail.com)
 * 
 * @version 1.0
 * @date 2022-11-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_



#define LCD_FIRST_ROW           0
#define LCD_SECOND_ROW          1


/**
 * @brief: Function to initialize the LCD
 * 
 */
void LCD_Init(void);
/**
 * @brief: Function to write a command in the LCD
 * 
 * @param Copy_u8Command: The command to be written
 */
void LCD_WriteCommand4Bit(u8 Copy_u8Command);
/**
 * @brief: Function to display a character in the LCD
 * 
 * @param Copy_u8Char: The character to be displayed
 */
void LCD_WriteChar4Bit(u8 Copy_u8Char);
/**
 * @brief: Function to change the LCD cursor's position
 * 
 * @param Copy_u8RowID: The ID of the row in which the cursor will be in (first row or second row) 
 * @param Copy_u8ColumnID: The ID of the column in which the cursor will be in
 */
void LCD_SetCursorPosition(u8 Copy_u8RowID, u8 Copy_u8ColumnID);
/**
 * @brief: Function to Display a string in the LCD
 * 
 * @param P_u8String: The String to be displayed
 */
void LCD_WriteString(u8* P_u8String);
/**
 * @brief: Function to display an integer in the LCD
 * 
 * @param Copy_u32Value: The integer value to be displayed
 */
void LCD_WriteIntegerValue(u32 Copy_u32Value);
/**
 * @brief: Function to toggle the enable pin of the LCD for a short amount of time
 * 
 */
void LCD_Peek(void);
/**
 * @brief: Function to clear the LCD display
 * 
 */
void LCD_ClearDisplay(void);
#endif /*LCD_INTERFACE_H_*/