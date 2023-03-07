/**
 * @file TMR_Program.c
 * @author Ahmed Atia (atiaa6501@gmail.com)
 * 
 * @version 1.0
 * @date 2022-11-12
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "ATMEGA32_REG.h"
#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include "TMR_Config.h"
#include "TMR_Interface.h"
#include "TMR_Private.h"


static Ptr_to_func_t TMR_Timer0_CTC_PCallBack = NULL;
static Ptr_to_func_t TMR_Timer0_OVF_PCallBack = NULL;
static Ptr_to_func_t TMR_Timer1_OVF_PCallBack = NULL;
static Ptr_to_func_t TMR_Timer1_CTC1A_PCallBack = NULL;
static Ptr_to_func_t TMR_Timer1_CTC1B_PCallBack = NULL;
static Ptr_to_func_t TMR_Timer2_OVF_PCallBack = NULL;
static Ptr_to_func_t TMR_Timer2_CTC_PCallBack = NULL;

/**********************************************TIMER 0**********************************************/
/**
 * @brief: Function to initialize timer 0 peripheral
 * 
 */
void TMR_Timer0Init(void)
{
    #if TMR_TIMER0_MODE == TMR_TIMER0_NORMAL_MODE 
        //Select Mode = Normal Mode
        CLEAR_BIT(TCCR0, WGM00);
        CLEAR_BIT(TCCR0, WGM01);

        //Enable Timer0 overflow interrupt
        #if TMR_TIMER0_INTERRUPT_STATUS == TMR_TIMER0_INTERRUPT_ENABLED
            SET_BIT(TIMSK, TOIE0);
        #elif TMR_TIMER0_INTERRUPT_STATUS == TMR_TIMER0_INTERRUPT_DISABLED
            CLEAR_BIT(TIMSK, TOIE0);
        #endif
    #elif TMR_TIMER0_MODE == TMR_TIMER0_CTC_MODE
        //Select Mode = CTC Mode
        CLEAR_BIT(TCCR0, WGM00);
        SET_BIT(TCCR0, WGM01);

        
        #if TMR_TIMER0_INTERRUPT_STATUS == TMR_TIMER0_INTERRUPT_ENABLED
            //Enable Timer0 output compare match interrupt
            SET_BIT(TIMSK, OCIE0);
        #elif TMR_TIMER0_INTERRUPT_STATUS == TMR_TIMER0_INTERRUPT_DISABLED
            //Disable Timer0 output compare match interrupt
            CLEAR_BIT(TIMSK, OCIE0);
        #endif

    #elif TMR_TIMER0_MODE == TMR_TIMER0_FAST_PWM_MODE
        //Select Mode = Fast PWM Mode
        SET_BIT(TCCR0, WGM00);
        SET_BIT(TCCR0, WGM01);

        //Set OC0 as output
        SET_BIT(DDRB, 3);

        #if TMR_TIMER0_FAST_PWM_OPERATION == TMR_TIMER0_FAST_PWM_NON_INVERTING_MODE
            CLEAR_BIT(TCCR0, COM00);
            SET_BIT(TCCR0, COM01);
        #elif TMR_TIMER0_FAST_PWM_OPERATION == TMR_TIMER0_FAST_PWM_INVERTING_MODE
            SET_BIT(TCCR0, COM00);
            SET_BIT(TCCR0, COM01);
        #endif
    #elif TMR_TIMER0_MODE == TMR_TIMER0_PHASE_CORRECT_PWM_MODE
        //Select Mode = Fast PWM Mode
        SET_BIT(TCCR0, WGM00);
        CLEAR_BIT(TCCR0, WGM01);

        //Set OC0 as output
        SET_BIT(DDRB, 3);

        #if TMR_TIMER0_PHASE_CORRECT_PWM_OPERATION == TMR_TIMER0_PHASE_CORRECT_PWM_NON_INVERTING_MODE
            CLEAR_BIT(TCCR0, COM00);
            SET_BIT(TCCR0, COM01);
        #elif TMR_TIMER0_PHASE_CORRECT_PWM_OPERATION == TMR_TIMER0_PHASE_CORRECT_PWM_INVERTING_MODE
            SET_BIT(TCCR0, COM00);
            SET_BIT(TCCR0, COM01);
        #endif        
    #endif
    
}
/**
 * @brief: Function to start timer 0 peripheral
 * 
 */
void TMR_Timer0Start(void)
{
    #if TMR_TIMER0_PRESCALAR == TMR_PRESCALAR_DIVIDE_BY_1
        //Set prescalar = 1
        SET_BIT(TCCR0, CS00);
        CLEAR_BIT(TCCR0, CS01);
        CLEAR_BIT(TCCR0, CS02);
    #elif TMR_TIMER0_PRESCALAR == TMR_PRESCALAR_DIVIDE_BY_8
        //Set prescalar = 8
        CLEAR_BIT(TCCR0, CS00);
        SET_BIT(TCCR0, CS01);
        CLEAR_BIT(TCCR0, CS02);
    #elif TMR_TIMER0_PRESCALAR == TMR_PRESCALAR_DIVIDE_BY_64
        //Set prescalar = 64
        SET_BIT(TCCR0, CS00);
        SET_BIT(TCCR0, CS01);
        CLEAR_BIT(TCCR0, CS02);
    #elif TMR_TIMER0_PRESCALAR == TMR_PRESCALAR_DIVIDE_BY_256
        //Set prescalar = 256
        CLEAR_BIT(TCCR0, CS00);
        CLEAR_BIT(TCCR0, CS01);
        SET_BIT(TCCR0, CS02);
    #elif TMR_TIMER0_PRESCALAR == TMR_PRESCALAR_DIVIDE_BY_1024
        //Set prescalar = 1024
        SET_BIT(TCCR0, CS00);
        CLEAR_BIT(TCCR0, CS01);
        SET_BIT(TCCR0, CS02);
    #elif TMR_TIMER0_PRESCALAR == TMR_EXTERNAL_CLOCK_ON_FALLING_EDGE
        //External clock source on T0 pin. Clock on falling edge.
        CLEAR_BIT(TCCR0, CS00);
        SET_BIT(TCCR0, CS01);
        SET_BIT(TCCR0, CS02);
    #elif TMR_TIMER0_PRESCALAR == TMR_EXTERNAL_CLOCK_ON_RISING_EDGE
        //External clock source on T0 pin. Clock on rising edge.
        SET_BIT(TCCR0, CS00);
        SET_BIT(TCCR0, CS01);
        SET_BIT(TCCR0, CS02);
    #endif
}
/**
 * @brief: Function to stop timer 0 peripheral
 * 
 */
void TMR_Timer0Stop(void)
{
    CLEAR_BIT(TCCR0, CS00);
    CLEAR_BIT(TCCR0, CS01);
    CLEAR_BIT(TCCR0, CS02); 
}
/**
 * @brief: Function to set the preload value of timer 0
 * 
 * @param Copy_u8PreloadValue: The value to be set in TCNT0 register
 */
void TMR_Timer0SetPreloadValue(u8 Copy_u8PreloadValue)
{
    if(Copy_u8PreloadValue >= 0 && Copy_u8PreloadValue <= TMR_TIMER0_MAX_VALUE)
    {
        TCNT0 = Copy_u8PreloadValue;
    }
    else
    {
        /*Do nothing*/
    }
}

/**
 * @brief: Function to set the value of the output compare register of timer0
 * 
 * @param Copy_u8CompareValue: The value to put in the OCR0
 */
void TMR_Timer0SetCompareMatchValue(u8 Copy_u8CompareValue)
{
    if(Copy_u8CompareValue >= 0 && Copy_u8CompareValue <= TMR_TIMER0_MAX_VALUE)
    {
        OCR0 = Copy_u8CompareValue;
    }
    else
    {
        /*Do nothing*/
    }
}

/**
 * @brief: Function to set the duty cycle of pulse wave modulation
 * 
 * @param Copy_u8DutyCycle: Duty cycle of the PWM
 */
void TMR_Timer0Set_PWM_DutyCycle(u8 Copy_u8DutyCycle)
{
    if(Copy_u8DutyCycle >= 0 && Copy_u8DutyCycle <= 100)
    {
        u8 Loc_u8CTCValue = 0;
        Loc_u8CTCValue = ((u32)(Copy_u8DutyCycle * 255)) / 100;
        OCR0 = Loc_u8CTCValue;
    }
    else
    {
        /*Do nothing*/
    }
}

void TMR_Timer0_CTC_SetCallBack(Ptr_to_func_t P_funcCallBack)
{
    if(P_funcCallBack != NULL)
    {
        TMR_Timer0_CTC_PCallBack = P_funcCallBack;
    }
    else
    {
        /*Do nothing*/
    }
}
void TMR_Timer0_OVF_SetCallBack(Ptr_to_func_t P_funcCallBack)
{
    if(P_funcCallBack != NULL)
    {
        TMR_Timer0_OVF_PCallBack = P_funcCallBack;
    }
    else
    {
        /*Do nothing*/
    }   
}

//ISR Function prototype for CTC0
void __vector_10(void) __attribute__ ((signal));
void __vector_10(void)
{
    if(TMR_Timer0_CTC_PCallBack != NULL)
    {
        TMR_Timer0_CTC_PCallBack();
    }
    else
    {
        /*Do nothing*/
    }
}

//ISR Function prototype for TOV0
void __vector_11(void) __attribute__ ((signal));
void __vector_11(void)
{
    if(TMR_Timer0_OVF_PCallBack != NULL)
    {
        TMR_Timer0_OVF_PCallBack();
    }
    else
    {
        /*Do nothing*/
    }
}

/**********************************************TIMER 1**********************************************/
/**
 * @brief: Function to initialize timer 1 peripheral
 * 
 */
void TMR_Timer1Init(void)
{
    #if TMR_TIMER1_MODE == TMR_TIMER1_NORMAL_MODE
        //Mode = Normal(0)
        CLEAR_BIT(TCCR1A, WGM10);
        CLEAR_BIT(TCCR1A, WGM11);
        CLEAR_BIT(TCCR1B, WGM12);
        CLEAR_BIT(TCCR1B, WGM13);

        #if TMR_TIMER1_INTERRUPT_STATUS == TMR_TIMER1_INTERRUPT_ENABLED
            //Enable Timer1 Overflow Interrupt
            SET_BIT(TIMSK, TOIE1);
        #elif TMR_TIMER1_INTERRUPT_STATUS == TMR_TIMER1_INTERRUPT_DISABLED
            CLEAR_BIT(TIMSK, TOIE1);
        #endif        
    #elif TMR_TIMER1_MODE == TMR_TIMER1_CTC_MODE
        //Mode = CTC(4)
        CLEAR_BIT(TCCR1A, WGM10);
        CLEAR_BIT(TCCR1A, WGM11);
        SET_BIT(TCCR1B, WGM12);
        CLEAR_BIT(TCCR1B, WGM13);

        #if TMR_TIMER1_INTERRUPT_STATUS == TMR_TIMER1_INTERRUPT_ENABLED
            //Enable Timer1 output compare match A interrupt
            SET_BIT(TIMSK, OCIE1A);
            //Enable Timer1 output compare match B interrupt
            SET_BIT(TIMSK, OCIE1B);
        #elif TMR_TIMER1_INTERRUPT_STATUS == TMR_TIMER1_INTERRUPT_DISABLED
            //Disable Timer1 output compare match A interrupt
            CLEAR_BIT(TIMSK, OCIE1A);
            //Disable Timer1 output compare match B interrupt
            CLEAR_BIT(TIMSK, OCIE1B);
        #endif

    #elif TMR_TIMER1_MODE == TMR_TIMER1_FAST_PWM_MODE
        //set OC1A as output pin (PIN D5)
        SET_BIT(DDRD, 5);
        //set OC1B as output pin (PIN D4)
        SET_BIT(DDRD, 4);

        //Mode = Fast PWM Mode(14)
        CLEAR_BIT(TCCR1A, WGM10);
        SET_BIT(TCCR1A, WGM11);
        SET_BIT(TCCR1B, WGM12);
        SET_BIT(TCCR1B, WGM13);

        #if TMR_TIMER1_FAST_PWM_OPERATION == TMR_TIMER1_FAST_PWM_NON_INVERTING_MODE
            //Non inverting mode
            CLEAR_BIT(TCCR1A, COM1A0);
            SET_BIT(TCCR1A,COM1A1);
        #elif TMR_TIMER1_FAST_PWM_OPERATION == TMR_TIMER1_FAST_PWM_INVERTING_MODE
            //Inverting mode
            SET_BIT(TCCR1A, COM1A0);
            SET_BIT(TCCR1A, COM1A1);
        #endif 
    #elif TMR_TIMER1_MODE == TMR_TIMER1_PHASE_CORRECT_PWM_MODE
        //Mode = Phase Correct PWM Mode(10)
        CLEAR_BIT(TCCR1A, WGM10);
        SET_BIT(TCCR1A, WGM11);
        CLEAR_BIT(TCCR1B, WGM12);
        SET_BIT(TCCR1B, WGM13);

        //set OC1A as output pin (PIN D5)
        SET_BIT(DDRD, 5);
        //set OC1B as output pin (PIN D4)
        SET_BIT(DDRD, 4);

        #if TMR_TIMER1_PHASE_CORRECT_PWM_OPERATION == TMR_TIMER1_PHASE_CORRECT_PWM_NON_INVERTING_MODE
            CLEAR_BIT(TCCR1A, COM1A0);
            SET_BIT(TCCR1A, COM1A1);
        #elif TMR_TIMER1_PHASE_CORRECT_PWM_OPERATION == TMR_TIMER1_PHASE_CORRECT_PWM_INVERTING_MODE
            SET_BIT(TCCR1A, COM1A0);
            SET_BIT(TCCR1A, COM1A1);
        #endif
    #endif


 //   //ICR1 >> Period time      ------> Make a function to change the frequency of the fast PWM
   // ICR1_u16 = 4999;
}
/**
 * @brief: Function to start timer 1 peripheral
 * 
 */
void TMR_Timer1Start(void)
{
    #if TMR_TIMER1_PRESCALAR == TMR_PRESCALAR_DIVIDE_BY_1
        //Set prescalar = 1
        SET_BIT(TCCR1B, CS10);
        CLEAR_BIT(TCCR1B, CS11);
        CLEAR_BIT(TCCR1B, CS12);
    #elif TMR_TIMER1_PRESCALAR == TMR_PRESCALAR_DIVIDE_BY_8
        //Set prescalar = 8
        CLEAR_BIT(TCCR1B, CS00);
        SET_BIT(TCCR1B, CS11);
        CLEAR_BIT(TCCR1B, CS12);
    #elif TMR_TIMER1_PRESCALAR == TMR_PRESCALAR_DIVIDE_BY_64
        //Set prescalar = 64
        SET_BIT(TCCR1B, CS10);
        SET_BIT(TCCR1B, CS11);
        CLEAR_BIT(TCCR1B, CS12);
    #elif TMR_TIMER1_PRESCALAR == TMR_PRESCALAR_DIVIDE_BY_256
        //Set prescalar = 256
        CLEAR_BIT(TCCR1B, CS10);
        CLEAR_BIT(TCCR1B, CS11);
        SET_BIT(TCCR1B, CS12);
    #elif TMR_TIMER1_PRESCALAR == TMR_PRESCALAR_DIVIDE_BY_1024
        //Set prescalar = 1024
        SET_BIT(TCCR1B, CS10);
        CLEAR_BIT(TCCR1B, CS11);
        SET_BIT(TCCR1B, CS12);
    #elif TMR_TIMER1_PRESCALAR == TMR_EXTERNAL_CLOCK_ON_FALLING_EDGE
        //External clock source on T0 pin. Clock on falling edge.
        CLEAR_BIT(TCCR1B, CS10);
        SET_BIT(TCCR1B, CS11);
        SET_BIT(TCCR1B, CS12);
    #elif TMR_TIMER1_PRESCALAR == TMR_EXTERNAL_CLOCK_ON_RISING_EDGE
        //External clock source on T0 pin. Clock on rising edge.
        SET_BIT(TCCR1B, CS10);
        SET_BIT(TCCR1B, CS11);
        SET_BIT(TCCR1B, CS12);
    #endif
}
/**
 * @brief: Function to stop timer 1 peripheral
 * 
 */
void TMR_Timer1Stop(void)
{
    CLEAR_BIT(TCCR1B, CS10);
    CLEAR_BIT(TCCR1B, CS11);
    CLEAR_BIT(TCCR1B, CS12);
}
/**
 * @brief: Function to set the value of the output compare register of timer1
 * 
 * @param Copy_u8OCRSelect: OCR register select (OCR1A, OCR1B)
 * @param Copy_u16CompareValue: The value to be put in the OCR
 */
void TMR_Timer1SetCompareMatchValue   (u8 Copy_u8OCRSelect ,u16 Copy_u16CompareValue)
{
    if(Copy_u16CompareValue >= 0 && Copy_u16CompareValue <= TMR_TIMER1_MAX_VALUE)
    {
        switch(Copy_u8OCRSelect)
        {
            case TMR_TIMER1_OCR1A:
            {
                OCR1A_u16 = Copy_u16CompareValue;
                break;
            }
            case TMR_TIMER1_OCR1B:
            {
                OCR1B_u16 = Copy_u16CompareValue;
                break;
            }
            default:
            {
                /*Do nothing*/
                break;
            }
        }
        
    }
    else
    {
        /*Do nothing*/
    }
}
/**
 * @brief: Function to set the duty cycle of pulse wave modulation in Timer 1
 * 
 * @param Copy_u8OCRSelect: OCR register select (OCR1A, OCR1B)
 * @param Copy_u8DutyCycle: Duty cycle of the PWM
 */
void TMR_Timer1SetPWMDutyCycle(u8 Copy_u8OCRSelect,u8 Copy_u8DutyCycle)
{
    if(Copy_u8DutyCycle >= 0 && Copy_u8DutyCycle <= 100)
    {
		u16 Loc_u16RegisterValue = 0;
		if (Copy_u8DutyCycle == TMR_TIMER1_ZERO_POSITION)
		{
			Loc_u16RegisterValue = 374;
		}
		else
		{
			Loc_u16RegisterValue = ((u32)(((u32)Copy_u8DutyCycle * (ICR1_u16 + 1)) / 100)) - 1;		
		}

	    switch(Copy_u8OCRSelect)
	    {
		    case TMR_TIMER1_OCR1A:
		    {
			    OCR1A_u16 = Loc_u16RegisterValue;
			    break;
		    }
		    case TMR_TIMER1_OCR1B:
		    {
			    OCR1B_u16 = Loc_u16RegisterValue;
			    break;
		    }
		    default:
		    {
			    /*Do nothing*/
			    break;
		    }
	    }
	    
    }
    else
    {
	    /*Do nothing*/
    }	
}
/**
 * @brief: Function to set the PWM Frequency
 * 
 * @param Copy_u32PWMFreq: PWM Frequency to be set
 */
void TMR_Timer1SetFastPWMFreq(u32 Copy_u32PWMFreq)
{
    if(Copy_u32PWMFreq >= 0 && Copy_u32PWMFreq <= TMR_MAX_CLK_FREQ)
    {
        u16 Loc_u16ICRvalue = 0;
        Loc_u16ICRvalue = ((u32)(TMR_MAX_CLK_FREQ) / ((u32)(Copy_u32PWMFreq * TMR_TIMER1_PRESCALAR))) - 1;
        ICR1_u16 = Loc_u16ICRvalue; 
    }
    else
    {
        /*Do nothing*/
    }
}
// ------> Implement these functions
void TMR_Timer1_OVF1_SetCallBack      (Ptr_to_func_t P_funcCallBack)
{
    if(P_funcCallBack != NULL)
    {
        TMR_Timer1_OVF_PCallBack = P_funcCallBack;
    }
    else
    {
        /*Do nothing*/
    }
}
void TMR_Timer1_CTC1A_SetCallBack     (Ptr_to_func_t P_funcCallBack)
{
    if(P_funcCallBack != NULL)
    {
        TMR_Timer1_CTC1A_PCallBack = P_funcCallBack;
    }
    else
    {
        /*Do nothing*/
    }
}
void TMR_Timer1_CTC1B_SetCallBack     (Ptr_to_func_t P_funcCallBack)
{
    if(P_funcCallBack != NULL)
    {
        TMR_Timer1_CTC1B_PCallBack = P_funcCallBack;
    }
    else
    {
        /*Do nothing*/
    }
}


//ISR Function prototype for OCR1A
void __vector_7(void) __attribute__ ((signal));
void __vector_7(void)
{
    if(TMR_Timer1_CTC1A_PCallBack != NULL)
    {
        TMR_Timer1_CTC1A_PCallBack();
    }
    else
    {
        /*Do nothing*/
    }  
}

//ISR Function prototype for OCR1B
void __vector_8(void) __attribute__ ((signal));
void __vector_8(void)
{
    if(TMR_Timer1_CTC1B_PCallBack != NULL)
    {
        TMR_Timer1_CTC1B_PCallBack();
    }
    else
    {
        /*Do nothing*/
    }
}

//ISR Function prototype for OVF1
void __vector_9(void) __attribute__ ((signal));
void __vector_9(void)
{
    if(TMR_Timer1_OVF_PCallBack != NULL)
    {
        TMR_Timer1_OVF_PCallBack();
    }
    else
    {
        /*Do nothing*/
    }
}

/**********************************************TIMER 2**********************************************/
/**
 * @brief: Function to initialize timer 2 peripheral
 * 
 */
void TMR_Timer2Init(void)
{
    #if TMR_TIMER2_NORMAL_MODE == TMR_TIMER2_MODE
        //Select mode = normal mode
        CLEAR_BIT(TCCR2, WGM20);
        CLEAR_BIT(TCCR2, WGM21);

        #if TMR_TIMER2_INTERRUPT_ENABLED == TMR_TIMER2_INTERRUPT_STATUS
            //Timer 2 overflow interrupt enabled
            SET_BIT(TIMSK, TOIE2);
        #elif TMR_TIMER2_INTERRUPT_DISABLED == TMR_TIMER2_INTERRUPT_STATUS
            //Timer 2 overflow interrupt disabled
            CLEAR_BIT(TIMSK, TOIE2);
        #else
            /*Do nothing*/
        #endif
    #elif TMR_TIMER2_CTC_MODE == TMR_TIMER2_MODE
        //Select mode = CTC mode
        CLEAR_BIT(TCCR2, WGM20);
        SET_BIT(TCCR2, WGM21);

        #if TMR_TIMER2_INTERRUPT_ENABLED == TMR_TIMER2_INTERRUPT_STATUS
            //Timer 2 output compare match interrupt enabled
            SET_BIT(TIMSK, OCIE2);
        #elif TMR_TIMER2_INTERRUPT_DISABLED == TMR_TIMER2_INTERRUPT_STATUS
            //Timer 2 output compare match interrupt disabled
            CLEAR_BIT(TIMSK, OCIE2);
        #else
            /*Do nothing*/
        #endif
    #elif TMR_TIMER2_FAST_PWM_MODE == TMR_TIMER2_MODE
        //Select mode = Fast PWM
        SET_BIT(TCCR2, WGM20);
        SET_BIT(TCCR2, WGM21);
        
        //Set OC2 Pin to be Output
        SET_BIT(DDRD,7);

        #if TMR_TIMER2_FAST_PWM_NON_INVERTING_MODE == TMR_TIMER2_FAST_PWM_OPERATION
            CLEAR_BIT(TCCR2, COM20);
            SET_BIT(TCCR2, COM21);
        #elif TMR_TIMER2_FAST_PWM_INVERTING_MODE == TMR_TIMER2_FAST_PWM_OPERATION
            SET_BIT(TCCR2,COM20);
            SET_BIT(TCCR2,COM21);
        #else
            /*Do nothing*/
        #endif
    #elif TMR_TIMER2_PHASE_CORRECT_PWM_MODE == TMR_TIMER2_MODE
        //Select mode = Phase Correct PWM
        SET_BIT(TCCR2, WGM20);
        CLEAR_BIT(TCCR2, WGM21);
        
        //Set OC2 Pin to be Output
        SET_BIT(DDRD,7);

        #if TMR_TIMER2_PHASE_CORRECT_PWM_NON_INVERTING_MODE == TMR_TIMER2_PHASE_CORRECT_PWM_OPERATION
            CLEAR_BIT(TCCR2, COM20);
            SET_BIT(TCCR2, COM21);
        #elif TMR_TIMER2_PHASE_CORRECT_PWM_INVERTING_MODE == TMR_TIMER2_PHASE_CORRECT_PWM_OPERATION
            SET_BIT(TCCR2,COM20);
            SET_BIT(TCCR2,COM21);
        #else
            /*Do nothing*/
        #endif 
    #else
        /*Do nothing*/
    #endif
}
/**
 * @brief: Function to start timer 2 peripheral
 * 
 */
void TMR_Timer2Start(void)
{
    #if TMR_PRESCALAR_DIVIDE_BY_1 == TMR_TIMER2_PRESCALAR
        SET_BIT(TCCR2, CS20);
        CLEAR_BIT(TCCR2, CS21);
        CLEAR_BIT(TCCR2, CS22);
    #elif TMR_PRESCALAR_DIVIDE_BY_8 == TMR_TIMER2_PRESCALAR
        CLEAR_BIT(TCCR2, CS20);
        SET_BIT(TCCR2, CS21);
        CLEAR_BIT(TCCR2, CS22);
    #elif TMR_PRESCALAR_DIVIDE_BY_32 == TMR_TIMER2_PRESCALAR
        SET_BIT(TCCR2, CS20);
        SET_BIT(TCCR2, CS21);
        CLEAR_BIT(TCCR2, CS22);
    #elif TMR_PRESCALAR_DIVIDE_BY_64 == TMR_TIMER2_PRESCALAR
        CLEAR_BIT(TCCR2, CS20);
        CLEAR_BIT(TCCR2, CS21);
        SET_BIT(TCCR2, CS22);
    #elif TMR_PRESCALAR_DIVIDE_BY_128 == TMR_TIMER2_PRESCALAR
        SET_BIT(TCCR2, CS20);
        CLEAR_BIT(TCCR2, CS21);
        SET_BIT(TCCR2, CS22);
    #elif TMR_PRESCALAR_DIVIDE_BY_256 == TMR_TIMER2_PRESCALAR
        CLEAR_BIT(TCCR2, CS20);
        SET_BIT(TCCR2, CS21);
        SET_BIT(TCCR2, CS22);
    #elif TMR_PRESCALAR_DIVIDE_BY_1024 == TMR_TIMER2_PRESCALAR
        SET_BIT(TCCR2, CS20);
        SET_BIT(TCCR2, CS21);
        SET_BIT(TCCR2, CS22);
    #else
        /*Do nothing*/
    #endif
}
/**
 * @brief: Function to stop timer 2 peripheral
 * 
 */
void TMR_Timer2Stop(void)
{
    CLEAR_BIT(TCCR2, CS20);
    CLEAR_BIT(TCCR2, CS21);
    CLEAR_BIT(TCCR2, CS22);
}
/**
 * @brief: Function to set the value of the output compare register of timer 2
 * 
 * @param Copy_u8CompareValue: The value to put in the OCR2
 */
void TMR_Timer2SetCompareMatchValue (u8 Copy_u8CompareValue)
{
    if(Copy_u8CompareValue >= 0 && Copy_u8CompareValue <= TMR_TIMER2_MAX_VALUE)
    {
        OCR2 = Copy_u8CompareValue;
    }
    else
    {
        /*Do nothing*/
    }
}
/**
 * @brief: Function to set the preload value of timer 2
 * 
 * @param Copy_u8PreloadValue: The value to be set in TCNT2 register
 */
void TMR_Timer2SetPreloadValue      (u8 Copy_u8PreloadValue)
{
    if(Copy_u8PreloadValue >= 0 && Copy_u8PreloadValue <= TMR_TIMER2_MAX_VALUE)
    {
        TCNT2 = Copy_u8PreloadValue;
    }
    else
    {
        /*Do nothing*/
    }
}
/**
 * @brief: Function to set the duty cycle of pulse wave modulation in Timer 2
 * 
 * @param Copy_u8DutyCycle: Duty cycle of the PWM
 */
void TMR_Timer2Set_PWM_DutyCycle    (u8 Copy_u8DutyCycle)
{
	    if(Copy_u8DutyCycle >= 0 && Copy_u8DutyCycle <= 100)
	    {
		    u8 Loc_u8CTCValue = 0;
		    Loc_u8CTCValue = ((u32)(Copy_u8DutyCycle * 255)) / 100;
		    OCR2 = Loc_u8CTCValue;
	    }
	    else
	    {
		    /*Do nothing*/
	    }
}
/**
 * @brief: Function to set the callback function of Compare match interrupt of Timer 2
 * 
 * @param P_funcCallBack: CTC Callback function of Timer 2
 */
void TMR_Timer2_CTC_SetCallBack     (Ptr_to_func_t P_funcCallBack)
{
    if(P_funcCallBack != NULL)
    {
        TMR_Timer2_CTC_PCallBack = P_funcCallBack;
    }
    else
    {
        /*Do nothing*/
    }
}
/**
 * @brief: Function to set the callback function of overflow interrupt of Timer 2
 * 
 * @param P_funcCallBack: Overflow callback function of Timer 2
 */
void TMR_Timer2_OVF_SetCallBack     (Ptr_to_func_t P_funcCallBack)
{
    if(P_funcCallBack != NULL)
    {
        TMR_Timer2_OVF_PCallBack = P_funcCallBack;
    }
    else
    {
        /*Do nothing*/
    }
}
//ISR Function prototype for CTC2
void __vector_4(void) __attribute__ ((signal));
void __vector_4(void)
{
    if(TMR_Timer2_CTC_PCallBack != NULL)
    {
        TMR_Timer2_CTC_PCallBack();
    }
    else
    {
        /*Do nothing*/
    }
}

//ISR Function prototype for OVF2
void __vector_5(void) __attribute__ ((signal));
void __vector_5(void)
{
    if(TMR_Timer2_OVF_PCallBack != NULL)
    {
        TMR_Timer2_OVF_PCallBack();
    }
    else
    {
        /*Do nothing*/
    }
}
