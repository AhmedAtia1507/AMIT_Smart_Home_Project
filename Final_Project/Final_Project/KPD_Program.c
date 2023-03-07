/**
 * @file KPD_Program.c
 * @author Ahmed Atia (atiaa6501@gmail.com)
 * 
 * @version 1.0
 * @date 2022-10-29
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <stdio.h>
/*UTILES LIB*/
#include "ATMEGA32_REG.h"
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/*MCAL*/
#include "DIO_Interface.h"

/*HAL*/
#include "KPD_Interface.h"
#include "KPD_Config.h"

static u8 KPD_ColumnsPins[NO_COLUMNS] = {KPD_COL0_PIN, KPD_COL1_PIN ,KPD_COL2_PIN ,KPD_COL3_PIN};
static u8 KPD_RowsPins[NO_ROWS] = {KPD_ROW0_PIN, KPD_ROW1_PIN, KPD_ROW2_PIN, KPD_ROW3_PIN};

/**
 * @brief: Function to initialize the keypad
 *         (Set the directions and the initial values of the pins connected to the keypad)
 * 
 */
void KPD_Init(void)
{
    DIO_SetPinDirection(KPD_COLS_PORT, KPD_COL0_PIN, DIO_PIN_OUTPUT);
    DIO_SetPinDirection(KPD_COLS_PORT, KPD_COL1_PIN, DIO_PIN_OUTPUT);
    DIO_SetPinDirection(KPD_COLS_PORT, KPD_COL2_PIN, DIO_PIN_OUTPUT);
    DIO_SetPinDirection(KPD_COLS_PORT, KPD_COL3_PIN, DIO_PIN_OUTPUT);

    DIO_SetPinDirection(KPD_ROWS_PORT, KPD_ROW0_PIN, DIO_PIN_INPUT);
    DIO_SetPinDirection(KPD_ROWS_PORT, KPD_ROW1_PIN, DIO_PIN_INPUT);
    DIO_SetPinDirection(KPD_ROWS_PORT, KPD_ROW2_PIN, DIO_PIN_INPUT);
    DIO_SetPinDirection(KPD_ROWS_PORT, KPD_ROW3_PIN, DIO_PIN_INPUT);

    DIO_SetPinValue(KPD_COLS_PORT, KPD_COL0_PIN, DIO_PIN_HIGH);
    DIO_SetPinValue(KPD_COLS_PORT, KPD_COL1_PIN, DIO_PIN_HIGH);
    DIO_SetPinValue(KPD_COLS_PORT, KPD_COL2_PIN, DIO_PIN_HIGH);
    DIO_SetPinValue(KPD_COLS_PORT, KPD_COL3_PIN, DIO_PIN_HIGH);

    DIO_ActivatePullUp(KPD_ROWS_PORT, KPD_ROW0_PIN);
    DIO_ActivatePullUp(KPD_ROWS_PORT, KPD_ROW1_PIN);
    DIO_ActivatePullUp(KPD_ROWS_PORT, KPD_ROW2_PIN);
    DIO_ActivatePullUp(KPD_ROWS_PORT, KPD_ROW3_PIN);
}
/**
 * @brief: Function to get the pressed button in the keypad
 * 
 * @param P_u8ReturnedValue: Pointer to put the pressed button in it 
 */
void KPD_GetValue(u8* P_u8ReturnedValue)
{
    if(P_u8ReturnedValue != NULL)
    {
        u8 Loc_u8KPD_Keys[NO_COLUMNS][NO_ROWS] = {
                                                    {'1', '2', '3', 'A'},
                                                    {'4', '5', '6', 'B'},
                                                    {'7', '8', '9', 'C'},
                                                    {'*', '0', '#', 'D'}
                                                };
		*P_u8ReturnedValue = KPD_NOT_PRESSED;
        u8 Loc_u8ColsCounter = 0, Loc_u8RowsCounter = 0, Loc_u8PinValue, Loc_u8PinFlag = 0;
        for(Loc_u8ColsCounter = 0; Loc_u8ColsCounter < NO_COLUMNS; Loc_u8ColsCounter++)
        {
            //Activate column
            DIO_SetPinValue(KPD_COLS_PORT, KPD_ColumnsPins[Loc_u8ColsCounter], DIO_PIN_LOW);

            /*Read the value of the rows and find the pressed button*/
            for(Loc_u8RowsCounter = 0; Loc_u8RowsCounter < NO_ROWS; Loc_u8RowsCounter++)
            {
                DIO_ReadPinValue(KPD_ROWS_PORT, KPD_RowsPins[Loc_u8RowsCounter], &Loc_u8PinValue);
                if(KPD_PRESSED == Loc_u8PinValue)
                {
                    *P_u8ReturnedValue = Loc_u8KPD_Keys[Loc_u8RowsCounter][Loc_u8ColsCounter];
                    while(Loc_u8PinValue == 0)
                    {
                        DIO_ReadPinValue(KPD_ROWS_PORT, KPD_RowsPins[Loc_u8RowsCounter], &Loc_u8PinValue);
                    }
                    Loc_u8PinFlag = 1;
                    break;
                }
                else
                {
                    /*Do nothing*/
                }
            }
            //Deactivate column
            DIO_SetPinValue(KPD_COLS_PORT, KPD_ColumnsPins[Loc_u8ColsCounter], DIO_PIN_HIGH);

            if(Loc_u8PinFlag == 1)
            {
                break;
            }
            else
            {
                /*Do nothing*/
            }
        }
    }
    else
    {
        /*Do nothing*/
    }
}