/**
 * @file KPD_Config.h
 * @author Ahmed Atia (atiaa6501@gmail.com)
 * 
 * @version 1.0
 * @date 2022-10-29
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef KPD_CONFIG_H_
#define KPD_CONFIG_H_

/*Macros for columns and rows*/
#define KPD_COLS_PORT	  DIO_PORTB
#define KPD_COL0_PIN    DIO_PIN4
#define KPD_COL1_PIN    DIO_PIN5
#define KPD_COL2_PIN    DIO_PIN6
#define KPD_COL3_PIN    DIO_PIN7

#define KPD_ROWS_PORT   DIO_PORTC
#define KPD_ROW0_PIN    DIO_PIN3
#define KPD_ROW1_PIN    DIO_PIN4
#define KPD_ROW2_PIN    DIO_PIN5
#define KPD_ROW3_PIN    DIO_PIN6

#endif /*KPD_CONFIG_H_*/

/*Config File is a file that affects the program file without the need to change anything in the
	program file
  ex: Keypad doesn't need to be in the same port forever
*/