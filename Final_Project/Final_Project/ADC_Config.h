#ifndef ADC_CONFIG_H_
#define ADC_CONFIG_H_

#include "ADC_Private.h"
/*Options For Voltage References
 *1-VREF_AREF_PIN
 *1-VREF_AVCC_PIN
 *1-VREF_2_56V_INTERNAL*/

#define ADC_SET_VREF            VREF_AVCC_PIN

/*Options For Prescalar
 *1-PRESCALER_DIVIDE_BY_2
 *2-PRESCALER_DIVIDE_BY_4
 *3-PRESCALER_DIVIDE_BY_8
 *4-PRESCALER_DIVIDE_BY_16
 *5-PRESCALER_DIVIDE_BY_32
 *6-PRESCALER_DIVIDE_BY_64
 *7-PRESCALER_DIVIDE_BY_128*/

#define ADC_SET_PRESCALAR       PRESCALER_DIVIDE_BY_128

/*Options For Adjusting the ADC Register Value
 *1-ADC_RIGHT_ADJUST
 *1-ADC_LEFT_ADJUST*/

#define ADC_SET_ADJUST_LEVEL    ADC_RIGHT_ADJUST
#endif /*ADC_CONFIG_H_*/