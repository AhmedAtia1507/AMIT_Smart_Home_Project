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


#endif /* ADC_INTERFACE_H_ */