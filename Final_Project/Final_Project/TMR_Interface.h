/**
 * @file TMR_Interface.h
 * @author Ahmed Atia (atiaa6501@gmail.com)
 * 
 * @version 1.0
 * @date 2022-11-12
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#ifndef TMR_INTERFACE_H_
#define TMR_INTERFACE_H_

typedef void (*Ptr_to_func_t) (void);
#define TMR_TIMER1_ZERO_POSITION							0
/**********************************************TIMER 0**********************************************/
/**
 * @brief: Function to initialize timer 0 peripheral
 * 
 */
void TMR_Timer0Init(void);
/**
 * @brief: Function to start timer 0 peripheral
 * 
 */
void TMR_Timer0Start(void);
/**
 * @brief: Function to stop timer 0 peripheral
 * 
 */
void TMR_Timer0Stop(void);
/**
 * @brief: Function to set the value of the output compare register of timer0
 * 
 * @param Copy_u8CompareValue: The value to put in the OCR0
 */
void TMR_Timer0SetCompareMatchValue (u8 Copy_u8CompareValue);
/**
 * @brief: Function to set the preload value of timer 0
 * 
 * @param Copy_u8PreloadValue: The value to be set in TCNT0 register
 */
void TMR_Timer0SetPreloadValue(u8 Copy_u8PreloadValue);
/**
 * @brief: Function to set the duty cycle of pulse wave modulation in Timer 0
 * 
 * @param Copy_u8DutyCycle: Duty cycle of the PWM
 */
void TMR_Timer0Set_PWM_DutyCycle(u8 Copy_u8DutyCycle);
/**
 * @brief: Function to set the callback function of Compare match interrupt of Timer 0
 * 
 * @param P_funcCallBack: CTC Callback function of Timer 0
 */
void TMR_Timer0_CTC_SetCallBack     (Ptr_to_func_t P_funcCallBack);
/**
 * @brief: Function to set the callback function of overflow interrupt of Timer 0
 * 
 * @param P_funcCallBack: Overflow callback function of Timer 0
 */
void TMR_Timer0_OVF_SetCallBack     (Ptr_to_func_t P_funcCallBack);

/**********************************************TIMER 1**********************************************/
/**
 * @brief: Function to initialize timer 1 peripheral
 * 
 */
void TMR_Timer1Init(void);
/**
 * @brief: Function to start timer 1 peripheral
 * 
 */
void TMR_Timer1Start(void);
/**
 * @brief: Function to stop timer 1 peripheral
 * 
 */
void TMR_Timer1Stop(void);
/**
 * @brief: Function to set the preload value of Timer 0
 * 
 * @param Copy_u16PreloadValue: The preload value to be set
 */
void TMR_Timer1SetPreloadValue(u16 Copy_u16PreloadValue);

#define TMR_TIMER1_OCR1A            1
#define TMR_TIMER1_OCR1B            2
/**
 * @brief: Function to set the value of the output compare register of timer1
 * 
 * @param Copy_u8OCRSelect: OCR register select (OCR1A, OCR1B)
 * @param Copy_u16CompareValue: The value to be put in the OCR
 */
void TMR_Timer1SetCompareMatchValue (u8 Copy_u8OCRSelect ,u16 Copy_u16CompareValue);
/**
 * @brief: Function to set the PWM Frequency
 * 
 * @param Copy_u32PWMFreq: PWM Frequency to be set
 */
void TMR_Timer1SetFastPWMFreq(u32 Copy_u32PWMFreq);
/**
 * @brief: Function to set the duty cycle of pulse wave modulation in Timer 1
 * 
 * @param Copy_u8OCRSelect: OCR register select (OCR1A, OCR1B)
 * @param Copy_u8DutyCycle: Duty cycle of the PWM
 */
void TMR_Timer1SetPWMDutyCycle(u8 Copy_u8OCRSelect,u8 Copy_u8DutyCycle);
/**
 * @brief: Function to set the callback function of overflow interrupt of Timer 1
 * 
 * @param P_funcCallBack: Overflow callback function of Timer 1
 */
void TMR_Timer1_OVF1_SetCallBack      (Ptr_to_func_t P_funcCallBack);
/**
 * @brief: Function to set the callback function of Compare match A interrupt of Timer 1
 * 
 * @param P_funcCallBack: Compare match A callback function of Timer 1
 */
void TMR_Timer1_CTC1A_SetCallBack     (Ptr_to_func_t P_funcCallBack);
/**
 * @brief: Function to set the callback function of Compare match B interrupt of Timer 1
 * 
 * @param P_funcCallBack: Compare match B callback function of Timer 1
 */
void TMR_Timer1_CTC1B_SetCallBack     (Ptr_to_func_t P_funcCallBack);

/**********************************************TIMER 2**********************************************/
/**
 * @brief: Function to initialize timer 2 peripheral
 * 
 */
void TMR_Timer2Init(void);
/**
 * @brief: Function to start timer 2 peripheral
 * 
 */
void TMR_Timer2Start(void);
/**
 * @brief: Function to stop timer 2 peripheral
 * 
 */
void TMR_Timer2Stop(void);
/**
 * @brief: Function to set the value of the output compare register of timer 2
 * 
 * @param Copy_u8CompareValue: The value to put in the OCR2
 */
void TMR_Timer2SetCompareMatchValue (u8 Copy_u8CompareValue);
/**
 * @brief: Function to set the preload value of timer 2
 * 
 * @param Copy_u8PreloadValue: The value to be set in TCNT2 register
 */
void TMR_Timer2SetPreloadValue      (u8 Copy_u8PreloadValue);
/**
 * @brief: Function to set the duty cycle of pulse wave modulation in Timer 2
 * 
 * @param Copy_u8DutyCycle: Duty cycle of the PWM
 */
void TMR_Timer2Set_PWM_DutyCycle    (u8 Copy_u8DutyCycle);
/**
 * @brief: Function to set the callback function of Compare match interrupt of Timer 2
 * 
 * @param P_funcCallBack: CTC Callback function of Timer 2
 */
void TMR_Timer2_CTC_SetCallBack     (Ptr_to_func_t P_funcCallBack);
/**
 * @brief: Function to set the callback function of overflow interrupt of Timer 2
 * 
 * @param P_funcCallBack: Overflow callback function of Timer 2
 */
void TMR_Timer2_OVF_SetCallBack     (Ptr_to_func_t P_funcCallBack);
#endif /* TMR_INTERFACE_H_ */