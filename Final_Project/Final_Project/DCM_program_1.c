
/* UTILES_LIB */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ATMEGA32_REG.h"

/* MCAL */

#include "DIO_Interface.h"
#include "ADC_Interface.h"




void AC_On(void)
{
	DIO_SetPinDirection(DIO_PORTA,DIO_PIN2,DIO_PIN_OUTPUT);
	DIO_SetPinValue(DIO_PORTA,DIO_PIN2,DIO_PIN_HIGH);
	
}

void AC_Off(void)
{
	DIO_SetPinDirection(DIO_PORTA,DIO_PIN2,DIO_PIN_OUTPUT);
	DIO_SetPinValue(DIO_PORTA,DIO_PIN2,DIO_PIN_LOW);
}


void AC_Auto(void)
{
	static u16 AnalogValue=0;
	static u16 DigitalValue=0;
	//ADC_init();
	
	
	ADC_GetDigitalValue(ADC_CHANNEL_1,&DigitalValue);
	
	AnalogValue = (((u32)DigitalValue *5000UL)/1024);
	
	if (AnalogValue < 2000) //Temp < 21
	{
		DIO_SetPinDirection(DIO_PORTA,DIO_PIN2,DIO_PIN_OUTPUT);
	    DIO_SetPinValue(DIO_PORTA,DIO_PIN2,DIO_PIN_LOW);
	}
		
	else if(AnalogValue > 4000)//Temp > 28
	{
		DIO_SetPinDirection(DIO_PORTA,DIO_PIN2,DIO_PIN_OUTPUT);
		DIO_SetPinValue(DIO_PORTA,DIO_PIN2,DIO_PIN_HIGH);
	}
	
}
