#ifndef ADC_PRIVATE_H_
#define ADC_PRIVATE_H_


/*ADMUX Bits Names*/
#define MUX0                        0  /*Analog Channel and Gain Selection Bits*/
#define MUX1                        1  /*Analog Channel and Gain Selection Bits*/
#define MUX2                        2  /*Analog Channel and Gain Selection Bits*/
#define MUX3                        3  /*Analog Channel and Gain Selection Bits*/
#define MUX4                        4  /*Analog Channel and Gain Selection Bits*/ 
#define ADLAR                       5  /*ADC Left Adjust Result*/
#define REFS0                       6  /*Reference Selection Bits*/
#define REFS1                       7  /*Reference Selection Bits*/

/*ADCSRA Bit Names*/        
#define ADPS0                       0  /*ADC Prescaler Select Bits*/
#define ADPS1                       1  /*ADC Prescaler Select Bits*/
#define ADPS2                       2  /*ADC Prescaler Select Bits*/
#define ADIE                        3  /*ADC Interrupt Enable*/
#define ADIF                        4  /*ADC Interrupt Flag*/ 
#define ADATE                       5  /*ADC Auto Trigger Enable*/
#define ADSC                        6  /*ADC Start Conversion*/
#define ADEN                        7  /*ADC Enable*/

/*SFIOR Bit Names*/
#define ADTS0                       5  /*ADC Auto Trigger Source*/
#define ADTS1                       6  /*ADC Auto Trigger Source*/
#define ADTS2                       7  /*ADC Auto Trigger Source*/

#define ADC_RIGHT_ADJUST            0
#define ADC_LEFT_ADJUST             1

#define PRESCALER_DIVIDE_BY_2 		1
#define PRESCALER_DIVIDE_BY_4 		2
#define PRESCALER_DIVIDE_BY_8 		3
#define PRESCALER_DIVIDE_BY_16 		4
#define PRESCALER_DIVIDE_BY_32 		5
#define PRESCALER_DIVIDE_BY_64 		6
#define PRESCALER_DIVIDE_BY_128 	7

#define VREF_AREF_PIN               0
#define VREF_AVCC_PIN               1
#define VREF_2_56V_INTERNAL         3

#endif /*ADC_PRIVATE_H_*/

//In this file, We put the macros which we doesn't want to be changed