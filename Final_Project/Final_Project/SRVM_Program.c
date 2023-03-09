/**
 * @file SRVM_Program.c
 * @author Ahmed Atia (atiaa6501@gmail.com)
 * 
 * @version 1.0
 * @date 2023-03-04
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "ATMEGA32_REG.h"
#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include "TMR_Interface.h"


#include "SRVM_Interface.h"
#include "SRVM_Private.h"
#include "SRVM_Config.h"
/**
 * @brief: Function to initialize the Servo motor Peripheral
 * 
 */
void SRVM_Init(void)
{
    TMR_Timer1Init();
    TMR_Timer1SetFastPWMFreq(50);
    TMR_Timer1Start();
}
/**
 * @brief: Function to set the angle of the servo motor
 * 
 * @param Copy_u8RotationAngleSign: Sign of angle of servo motor 
 * @param Copy_u8RotationAngle: : Angle of Servo motor 
 */
void SRVM_SetRotationAngle(u8 Copy_u8RotationAngleSign,u8 Copy_u8RotationAngle)
{
/*
    Duty Cycle = 5 --> Angle = -90           DutyCycle - 5    Angle + 90
                                    ------>  ------------- = -------------
    Duty Cycle = 10 --> Angle = 90              10 - 5            180
    
                  540 + (2 x Angle)
    DutyCycle = --------------------  Note: Angle can be positive or negative
                        72
*/
    if((Copy_u8RotationAngle >= 0) && (Copy_u8RotationAngle <= 90))
    {
        if(Copy_u8RotationAngle == 0)
        {
            TMR_Timer1SetPWMDutyCycle(SRVM_OC_CONNECTED, TMR_TIMER1_ZERO_POSITION);
        }
        else
        {
            u8 Loc_u8DutyCycle = 0;
            switch(Copy_u8RotationAngleSign)
            {
                case SRVM_ANGLE_POSITIVE:
                {
                    Loc_u8DutyCycle = (u32)(((u32)(540 + (u32)(2 * (u32)Copy_u8RotationAngle))) / 72);
                    TMR_Timer1SetPWMDutyCycle(SRVM_OC_CONNECTED, Loc_u8DutyCycle);
                    break;
                }
                case SRVM_ANGLE_NEGATIVE:
                {
                    Loc_u8DutyCycle = (u32)(((u32)(540 - (u32)(2 * (u32)Copy_u8RotationAngle))) / 72);
                    TMR_Timer1SetPWMDutyCycle(SRVM_OC_CONNECTED, Loc_u8DutyCycle);
                    break;
                }
                default:
                {
                    /*Do nothing*/
                    break;
                }
            }
        }
    }
    else
    {
        /*Do nothing*/
    }
}