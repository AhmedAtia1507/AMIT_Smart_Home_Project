/**
 * @file ADC_Program.c
 * @author Ahmed Atia (atiaa6501@gmail.com)
 * 
 * @version 1.0
 * @date 2022-11-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "ATMEGA32_REG.h"
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "ADC_Interface.h"
#include "ADC_Private.h"
#include "ADC_Config.h"
/**
 * @brief: Function to initialize the ADC
 * 
 */
void ADC_Init(void)
{
    //Select Vref = AVCC
    #if ADC_SET_VREF == VREF_AREF_PIN
        CLEAR_BIT(ADMUX, REFS0);
        CLEAR_BIT(ADMUX, REFS1);
    #elif ADC_SET_VREF == VREF_AVCC_PIN
        SET_BIT(ADMUX, REFS0);
        CLEAR_BIT(ADMUX, REFS1);
    #elif ADC_SET_VREF == VREF_2_56V_INTERNAL
        SET_BIT(ADMUX, REFS0);
        SET_BIT(ADMUX, REFS1);
    #else
        #error "Wrong Voltage Reference Chosen" 
    #endif

    //Right Adjust
    #if ADC_SET_ADJUST_LEVEL == ADC_RIGHT_ADJUST
        CLEAR_BIT(ADMUX, ADLAR);
    #elif ADC_SET_ADJUST_LEVEL == ADC_LEFT_ADJUST
        SET_BIT(ADMUX, ADLAR);
    #else
        #error "Wrong Adjustment Chosen"
    #endif

    //Single Conversion mode
    CLEAR_BIT(ADCSRA, ADATE);

    //Prescalar 128 for 16MHZ
    #if   ADC_SET_PRESCALAR == PRESCALER_DIVIDE_BY_2
        CLEAR_BIT(ADCSRA, ADPS0);
        CLEAR_BIT(ADCSRA, ADPS1);
        CLEAR_BIT(ADCSRA, ADPS2);
    #elif ADC_SET_PRESCALAR == PRESCALER_DIVIDE_BY_4
        CLEAR_BIT(ADCSRA, ADPS0);
        SET_BIT(ADCSRA, ADPS1);
        CLEAR_BIT(ADCSRA, ADPS2);
    #elif ADC_SET_PRESCALAR == PRESCALER_DIVIDE_BY_8
        SET_BIT(ADCSRA, ADPS0);
        SET_BIT(ADCSRA, ADPS1);
        CLEAR_BIT(ADCSRA, ADPS2);
    #elif ADC_SET_PRESCALAR == PRESCALER_DIVIDE_BY_16
        CLEAR_BIT(ADCSRA, ADPS0);
        CLEAR_BIT(ADCSRA, ADPS1);
        SET_BIT(ADCSRA, ADPS2);
    #elif ADC_SET_PRESCALAR == PRESCALER_DIVIDE_BY_32
        SET_BIT(ADCSRA, ADPS0);
        CLEAR_BIT(ADCSRA, ADPS1);
        SET_BIT(ADCSRA, ADPS2);
    #elif ADC_SET_PRESCALAR == PRESCALER_DIVIDE_BY_64
        CLEAR_BIT(ADCSRA, ADPS0);
        SET_BIT(ADCSRA, ADPS1);
        SET_BIT(ADCSRA, ADPS2);
    #elif ADC_SET_PRESCALAR == PRESCALER_DIVIDE_BY_128
        SET_BIT(ADCSRA, ADPS0);
        SET_BIT(ADCSRA, ADPS1);
        SET_BIT(ADCSRA, ADPS2);
    #else
        #error "Wrong Prescalar Chosen"
    #endif

    //ADC Enable
    SET_BIT(ADCSRA, 7);
}
/**
 * @brief: Function to start the ADC conversion
 * 
 * @param Copy_u8ChannelNumber: The ADC channel
 * @param P_u16DigitalValue: Pointer to store the value of the conversion in
 */
void ADC_GetDigitalValue(u8 Copy_u8ChannelNumber, u16* P_u16DigitalValue)
{
    if(P_u16DigitalValue != NULL)
    {
        if(Copy_u8ChannelNumber >= ADC_CHANNEL_0 && Copy_u8ChannelNumber <= ADC_CHANNEL_7)
        {
            //clear the first 5 bits of the ADMUX register
            ADMUX &= 0b11100000; 
            //Set the values of the first 5 bits as the channel number
            ADMUX |= Copy_u8ChannelNumber; 
            //Start Conversion
            SET_BIT(ADCSRA, ADSC);

            //Wait for the flag of ADC
            while(GET_BIT(ADCSRA, ADIF) == 0);

            //Clear ADC Flag
            SET_BIT(ADCSRA,ADIF);

            //Read Digital Value
            *P_u16DigitalValue = ADC_u16;
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
