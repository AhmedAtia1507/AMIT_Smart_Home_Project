/**
 * @file TMR_Private.h
 * @author Ahmed Atia (atiaa6501@gmail.com)
 * 
 * @version 1.0
 * @date 2022-11-12
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef TMR_PRIVATE_H_
#define TMR_PRIVATE_H_


#define TMR_TIMER1_ZERO_POSITION							0
#define TMR_TIMER0_MAX_VALUE                                255
#define TMR_TIMER1_MAX_VALUE                                65535
#define TMR_TIMER2_MAX_VALUE								255
#define TMR_MAX_CLK_FREQ                                    16000000

/*Timer0 modes of operation*/           
#define TMR_TIMER0_NORMAL_MODE                              1
#define TMR_TIMER0_CTC_MODE                                 2
#define TMR_TIMER0_FAST_PWM_MODE                            3
#define TMR_TIMER0_PHASE_CORRECT_PWM_MODE                   4

#define TMR_TIMER0_FAST_PWM_NON_INVERTING_MODE              1
#define TMR_TIMER0_FAST_PWM_INVERTING_MODE                  2

#define TMR_TIMER0_PHASE_CORRECT_PWM_NON_INVERTING_MODE     1
#define TMR_TIMER0_PHASE_CORRECT_PWM_INVERTING_MODE         2

#define TMR_TIMER0_INTERRUPT_ENABLED                        1
#define TMR_TIMER0_INTERRUPT_DISABLED                       2

/*Timer Clock Sources*/
#define TMR_PRESCALAR_DIVIDE_BY_1                           1
#define TMR_PRESCALAR_DIVIDE_BY_8                           8
#define TMR_PRESCALAR_DIVIDE_BY_32                          32
#define TMR_PRESCALAR_DIVIDE_BY_64                          64
#define TMR_PRESCALAR_DIVIDE_BY_128                         128
#define TMR_PRESCALAR_DIVIDE_BY_256                         256
#define TMR_PRESCALAR_DIVIDE_BY_1024                        1024
#define TMR_EXTERNAL_CLOCK_ON_FALLING_EDGE                  6
#define TMR_EXTERNAL_CLOCK_ON_RISING_EDGE                   7

/*TCCR0 bits names*/

/*Clock Select*/             
#define CS00                                                0     
/*Clock Select*/             
#define CS01                                                1   
/*Clock Select*/             
#define CS02                                                2         
/*Waveform Generation Mode*/ 
#define WGM01                                               3        
/*Compare Match Output Mode*/
#define COM00                                               4          
/*Compare Match Output Mode*/
#define COM01                                               5          
/*Waveform Generation Mode*/
#define WGM00                                               6  
/*Force Output Compare*/     
#define FOC0                                                7       

/*TIMSK bits names*/

/*Timer/Counter0 Overflow Interrupt Enable*/
#define TOIE0                                               0 
/*Timer/Counter0 Output Compare Match Interrupt Enable*/
#define OCIE0                                               1 
/*Timer/Counter1, Overflow Interrupt Enable*/
#define TOIE1                                               2
/*Timer/Counter1, Output Compare B Match Interrupt Enable*/
#define OCIE1B                                              3
/*Timer/Counter1, Output Compare A Match Interrupt Enable*/
#define OCIE1A                                              4
/*Timer/Counter1, Input Capture Interrupt Enable*/
#define TICIE1                                              5
/*Timer/Counter2, Overflow Interrupt Enable*/
#define TOIE2                                               6
/*Timer/Counter2 Output Compare Match Interrupt Enable*/
#define OCIE2                                               7

/*TIFR bits names*/      
/*Timer/Counter0 Overflow Flag*/
#define TOV0                                                0 
/*Output Compare Flag 0*/
#define OCF0                                                1 
/*Timer/Counter1, Overflow Flag*/
#define TOV1                                                2
/*Timer/Counter1, Output Compare B Match Flag*/
#define OCF1B                                               3
/*Timer/Counter1, Output Compare A Match Flag*/
#define OCF1A                                               4
/*Timer/Counter1, Input Capture Flag*/
#define ICF1                                                5
/*Timer/Counter2, Overflow Flag*/
#define TOV2                                                6
/*Output Compare Flag 2*/
#define OCF2                                                7

/*Timer 1 modes of operation*/
#define TMR_TIMER1_NORMAL_MODE                              1
#define TMR_TIMER1_CTC_MODE                                 2
#define TMR_TIMER1_FAST_PWM_MODE                            3
#define TMR_TIMER1_PHASE_CORRECT_PWM_MODE                   4

/*Timer 1 Fast PWM modes*/
#define TMR_TIMER1_FAST_PWM_NON_INVERTING_MODE              1
#define TMR_TIMER1_FAST_PWM_INVERTING_MODE                  2

/*Timer 1 Interrupt Status*/
#define TMR_TIMER1_INTERRUPT_ENABLED                        1
#define TMR_TIMER1_INTERRUPT_DISABLED                       2

/*Timer 1 Phase Correct PWM modes*/
#define TMR_TIMER1_PHASE_CORRECT_PWM_NON_INVERTING_MODE     1
#define TMR_TIMER1_PHASE_CORRECT_PWM_INVERTING_MODE         2

/*TCCR1A bits names*/
/*Waveform Generation Mode*/          
#define WGM10                                               0        
/*Waveform Generation Mode*/          
#define WGM11                                               1       
/*Force Output Compare for Channel B*/
#define FOC1B                                               2  
/*Force Output Compare for Channel A*/
#define FOC1A                                               3  
/*Compare Output Mode for Channel B*/ 
#define COM1B0                                              4    
/*Compare Output Mode for Channel B*/ 
#define COM1B1                                              5   
/*Compare Output Mode for Channel A*/ 
#define COM1A0                                              6    
/*Compare Output Mode for Channel A*/ 
#define COM1A1                                              7     

/*TCCR1B bits names*/
/*Clock Select*/                
#define CS10                                                0
/*Clock Select*/                
#define CS11                                                1  
/*Clock Select*/                
#define CS12                                                2   
/*Waveform Generation Mode*/    
#define WGM12                                               3       
/*Waveform Generation Mode*/    
#define WGM13                                               4        
/*Input Capture Edge Select*/   
#define ICES1                                               6        
/*Input Capture Noise Canceler*/
#define ICNC1                                               7        


/*Timer2 modes of operation*/           
#define TMR_TIMER2_NORMAL_MODE                              1
#define TMR_TIMER2_CTC_MODE                                 2
#define TMR_TIMER2_FAST_PWM_MODE                            3
#define TMR_TIMER2_PHASE_CORRECT_PWM_MODE                   4

/*Timer 2 Fast PWM Modes*/
#define TMR_TIMER2_FAST_PWM_NON_INVERTING_MODE              1
#define TMR_TIMER2_FAST_PWM_INVERTING_MODE                  2

/*Timer 2 Phase Correct Modes*/
#define TMR_TIMER2_PHASE_CORRECT_PWM_NON_INVERTING_MODE     1
#define TMR_TIMER2_PHASE_CORRECT_PWM_INVERTING_MODE         2

/*Timer 2 Interrupt Status*/
#define TMR_TIMER2_INTERRUPT_ENABLED                        1
#define TMR_TIMER2_INTERRUPT_DISABLED                       2

/**********************TCCR2 Register Bits***********************/
/*Clock Select Bit 0*/
#define CS20                                                0
/*Clock Select Bit 1*/
#define CS21                                                1
/*Clock Select Bit 2*/
#define CS22                                                2
/*Waveform Generation Mode Bit 1*/
#define WGM21                                               3
/*Compare Match Output Mode Bit 0*/
#define COM20                                               4
/*Compare Match Output Mode Bit 1*/
#define COM21                                               5
/*Waveform Generation Mode Bit 0*/
#define WGM20                                               6
/*Force Output Compare*/
#define FOC2                                                7

#endif /*TMR_PRIVATE_H_*/