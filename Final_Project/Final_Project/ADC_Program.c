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

static ptr_to_func_t ADC_ConversionComplete_PCallback = NULL;

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

    #if ADC_INTERRUPT_ENABLED == ADC_INTERRUPT_STATUS
        SET_BIT(ADCSRA, ADIE);
    #elif ADC_INTERRUPT_DISABLED == ADC_INTERRUPT_STATUS
        CLEAR_BIT(ADCSRA, ADIE);
    #else
        /*Do nothing*/
    #endif

    #if ADC_SINGLE_CONVERSION_MODE == ADC_CONVERSION_MODE
        //Single Conversion mode
        CLEAR_BIT(ADCSRA, ADATE);
    #elif ADC_AUTO_TRIGGER_MODE == ADC_CONVERSION_MODE
        //Auto Trigger Enable
        SET_BIT(ADCSRA, ADATE);

        ADMUX &= 0b11100000;
        #if ADC_FREE_RUNNING_MODE == ADC_AUTO_TRIGGER_SOURCE
            CLEAR_BIT(SFIOR, ADTS0);
            CLEAR_BIT(SFIOR, ADTS1);
            CLEAR_BIT(SFIOR, ADTS2);
        #elif ADC_ANALOG_COMPARATOR_TRIGGER == ADC_AUTO_TRIGGER_SOURCE
            SET_BIT(SFIOR, ADTS0);
            CLEAR_BIT(SFIOR, ADTS1);
            CLEAR_BIT(SFIOR, ADTS2);
        #elif ADC_EXT_INT0_TRIGGER == ADC_AUTO_TRIGGER_SOURCE
            CLEAR_BIT(SFIOR, ADTS0);
            SET_BIT(SFIOR, ADTS1);
            CLEAR_BIT(SFIOR, ADTS2);
        #elif ADC_TIMER0_COMPARE_MATCH_TRIGGER == ADC_AUTO_TRIGGER_SOURCE
            SET_BIT(SFIOR, ADTS0);
            SET_BIT(SFIOR, ADTS1);
            CLEAR_BIT(SFIOR, ADTS2);
        #elif ADC_TIMER0_OVERFLOW_TRIGGER == ADC_AUTO_TRIGGER_SOURCE
            CLEAR_BIT(SFIOR, ADTS0);
            CLEAR_BIT(SFIOR, ADTS1);
            SET_BIT(SFIOR, ADTS2);
        #elif ADC_TIMER1_COMPARE_MATCH_B_TRIGGER == ADC_AUTO_TRIGGER_SOURCE
            SET_BIT(SFIOR, ADTS0);
            CLEAR_BIT(SFIOR, ADTS1);
            SET_BIT(SFIOR, ADTS2);
        #elif ADC_TIMER1_OVERFLOW_TRIGGER == ADC_AUTO_TRIGGER_SOURCE
            CLEAR_BIT(SFIOR, ADTS0);
            SET_BIT(SFIOR, ADTS1);
            SET_BIT(SFIOR, ADTS2);
        #elif ADC_TIMER1_CAPTURE_EVENT_TRIGGER == ADC_AUTO_TRIGGER_SOURCE
            SET_BIT(SFIOR, ADTS0);
            SET_BIT(SFIOR, ADTS1);
            SET_BIT(SFIOR, ADTS2);
        #else
            /*Do nothing*/
        #endif
    #else
        /*Do nothing*/
    #endif



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
    SET_BIT(ADCSRA, ADEN);
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

/**
 * @brief: Function to start the analog-to-digital conversion
 * 
 * @param Copy_u8ChannelNumber: Channel Number to which the analog signal is connected to
 */
void ADC_StartConversion(u8 Copy_u8ChannelNumber)
{
    if(Copy_u8ChannelNumber >= ADC_CHANNEL_0 && Copy_u8ChannelNumber <= ADC_CHANNEL_7)
    {
        //clear the first 5 bits of the ADMUX register
        ADMUX &= 0b11100000; 
        //Set the values of the first 5 bits as the channel number
        ADMUX |= Copy_u8ChannelNumber; 
        //Start Conversion
        SET_BIT(ADCSRA, ADSC);
    }
    else
    {
        /*Do nothing*/
    }
}
/**
 * @brief: Function to set the callback function for ADC Conversion Complete Interrupt
 * 
 * @param P_CallbackFunction 
 */
void ADC_ConversionCompleteSetCallback(ptr_to_func_t P_CallbackFunction)
{
    if(P_CallbackFunction != NULL)
    {
        ADC_ConversionComplete_PCallback = P_CallbackFunction;
    }
    else
    {
        /*Do nothing*/
    }
}
/**
 * @brief: Function to get the digital value of conversion result "Using Interrupt"
 * 
 * @param P_u16DigitalValue: Digital Value
 */
void ADC_GetDigitalValueAsynchronous(u16* P_u16DigitalValue)
{
    if(P_u16DigitalValue != NULL)
    {
        *P_u16DigitalValue = ADC_u16;
    }
    else
    {
        /*Do nothing*/
    }
}
//ISR Function prototype for ADC Conversion Complete
void __vector_16(void) __attribute__ ((signal));
void __vector_16(void)
{
    if(ADC_ConversionComplete_PCallback != NULL)
    {
        //Clear ADC Flag
        SET_BIT(ADCSRA,ADIF);
        ADC_ConversionComplete_PCallback();
    }
    else
    {
        /*Do nothing*/
    }
    //Clear ADC Flag
    SET_BIT(ADCSRA,ADIF);
}