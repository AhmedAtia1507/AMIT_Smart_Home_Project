/**
 * @file ADC_Interface.h
 * @author Ahmed Atia (atiaa6501@gmail.com)
 * 
 * @version 1.0
 * @date 2022-11-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_

#define ADC_CHANNEL_0           0
#define ADC_CHANNEL_1           1
#define ADC_CHANNEL_2           2
#define ADC_CHANNEL_3           3
#define ADC_CHANNEL_4           4
#define ADC_CHANNEL_5           5
#define ADC_CHANNEL_6           6
#define ADC_CHANNEL_7           7


typedef void (*ptr_to_func_t) (void);

/**
 * @brief: Function to initialize the ADC
 * 
 */
void ADC_Init(void);
/**
 * @brief: Function to start the ADC conversion
 * 
 * @param Copy_u8ChannelNumber: The ADC channel
 * @param P_u16DigitalValue: Pointer to store the value of the conversion in
 */
void ADC_GetDigitalValue(u8 Copy_u8ChannelNumber, u16* P_u16DigitalValue);
/**
 * @brief: Function to get the digital value of conversion result "Using Interrupt"
 * 
 * @param P_u16DigitalValue: Digital Value
 */
void ADC_GetDigitalValueAsynchronous(u16* P_u16DigitalValue);
/**
 * @brief: Function to start the analog-to-digital conversion
 * 
 * @param Copy_u8ChannelNumber: Channel Number to which the analog signal is connected to
 */
void ADC_StartConversion(u8 Copy_u8ChannelNumber);
/**
 * @brief: Function to set the callback function for ADC Conversion Complete Interrupt
 * 
 * @param P_CallbackFunction 
 */
void ADC_ConversionCompleteSetCallback(ptr_to_func_t P_CallbackFunction);

#endif /* ADC_INTERFACE_H_ */