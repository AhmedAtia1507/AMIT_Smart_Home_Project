/**
 * @file LED_Program.c
 * @author Ahmed Atia (atiaa6501@gmail.com)
 * 
 * @version 1.0
 * @date 2023-02-02
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "ATMEGA32_REG.h"
#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include "DIO_Interface.h"

#include "LED_Interface.h"

/**
 * @brief: Function for turning on a LED
 * 
 * @param Copy_u8PortID: Port ID to which the LED is connected
 * @param Copy_u8PinID: Pin ID to which the LED is connected
 */
void LED_On(u8 Copy_u8PortID, u8 Copy_u8PinID)
{
    if(Copy_u8PortID >= DIO_PORTA && Copy_u8PortID <= DIO_PORTD)
    {
        if(Copy_u8PinID >= DIO_PIN0 && Copy_u8PinID <= DIO_PIN7)
        {
            u8 Loc_u8PinDirStatus = 7;
            DIO_ReadDDRPinValue(Copy_u8PortID, Copy_u8PinID, &Loc_u8PinDirStatus);
            if(Loc_u8PinDirStatus == DIO_PIN_OUTPUT || Loc_u8PinDirStatus == DIO_PIN_INPUT)
            {
                if(Loc_u8PinDirStatus == DIO_PIN_INPUT)
                {
                    DIO_SetPinDirection(Copy_u8PortID, Copy_u8PinID, DIO_PIN_OUTPUT);
                }
                else
                {
                    /*Do nothing*/
                }

                DIO_SetPinValue(Copy_u8PortID, Copy_u8PinID, DIO_PIN_HIGH);
            }
            else
            {
                /*Do nothing*/
            }
        }
        else
        {
            /*Do nothing*/
        }
    }
    else
    {
        /*Do nothing*/
    }
}
/**
 * @brief: Function for turning off a LED 
 * 
 * @param Copy_u8PortID:  Port ID to which the LED is connected 
 * @param Copy_u8PinID: Pin ID to which the LED is connected
 */
void LED_Off(u8 Copy_u8PortID, u8 Copy_u8PinID)
{
        if(Copy_u8PortID >= DIO_PORTA && Copy_u8PortID <= DIO_PORTD)
    {
        if(Copy_u8PinID >= DIO_PIN0 && Copy_u8PinID <= DIO_PIN7)
        {
            u8 Loc_u8PinDirStatus = 7;
            DIO_ReadDDRPinValue(Copy_u8PortID, Copy_u8PinID, &Loc_u8PinDirStatus);
            if(Loc_u8PinDirStatus == DIO_PIN_HIGH || Loc_u8PinDirStatus == DIO_PIN_LOW)
            {
                if(Loc_u8PinDirStatus == DIO_PIN_LOW)
                {
                    DIO_SetPinDirection(Copy_u8PortID, Copy_u8PinID, DIO_PIN_OUTPUT);
                }
                else
                {
                    /*Do nothing*/
                }
                DIO_SetPinValue(Copy_u8PortID, Copy_u8PinID, DIO_PIN_LOW);   
            }
            else
            {
                /*Do nothing*/
            }
        }
        else
        {
            /*Do nothing*/
        }
    }
    else
    {
        /*Do nothing*/
    }
}
/**
 * @brief: Function for toggling a LED
 * 
 * @param Copy_u8PortID: Port ID to which the LED is connected 
 * @param Copy_u8PinID: Pin ID to which the LED is connected
 */
void LED_Toggle(u8 Copy_u8PortID, u8 Copy_u8PinID)
{
        if(Copy_u8PortID >= DIO_PORTA && Copy_u8PortID <= DIO_PORTD)
    {
        if(Copy_u8PinID >= DIO_PIN0 && Copy_u8PinID <= DIO_PIN7)
        {
            u8 Loc_u8PinDirStatus = 7;
            DIO_ReadDDRPinValue(Copy_u8PortID, Copy_u8PinID, &Loc_u8PinDirStatus);
            if(Loc_u8PinDirStatus == DIO_PIN_HIGH || Loc_u8PinDirStatus == DIO_PIN_LOW)
            {
                if(Loc_u8PinDirStatus == DIO_PIN_LOW)
                {
                    DIO_SetPinDirection(Copy_u8PortID, Copy_u8PinID, DIO_PIN_OUTPUT);
                }
                else
                {
                    /*Do nothing*/
                }
                DIO_TogglePinValue(Copy_u8PortID, Copy_u8PinID);
            }
            else
            {
                /*Do nothing*/
            }
        }
        else
        {
            /*Do nothing*/
        }
    }
    else
    {
        /*Do nothing*/
    }
}