/*
 * Final_Project.c
 *
 * Created: 2/19/2023 4:48:20 PM
 * Author : hp
 */ 

#include "ATMEGA32_REG.h"
#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include "DIO_Interface.h"
#include "UART_Interface.h"
#include "GI_Interface.h"

#include "Internal_EEPROM_Interface.h"
#include "LCD_Interface.h"
#include "BUZZER_Interface.h"
#include "SRVM_Interface.h"
#include "LED_Interface.h"
#include "TMR_Interface.h"
#include "ADC_Interface.h"
#include "KPD_Interface.h"

#include "USER_interface.h"
#include "HC05_Interface.h"

#define F_CPU 16000000UL
#include <util/delay.h>

void LM35_StartConversion(void);
void LM35_TempControl(void);

int main(void)
{
	u8 Loc_u8Value = 0;
	/*Here, We initialize the peripherals used*/
	LCD_Init();
	SRVM_Init();
	BUZZER_Init();
	GI_Enable();
	/*We set the ADC channel 0 pin to be input*/
	DIO_SetPinDirection(DIO_PORTA, DIO_PIN0, DIO_PIN_INPUT);
	/*We set the pin connected to relay to be output*/
	DIO_SetPinDirection(DIO_PORTA, DIO_PIN2, DIO_PIN_OUTPUT);
	/*We initialize timer 0 in Normal mode and set the ADC start conversion function as the Overflow*/
	/*Interrupt function*/
	TMR_Timer0Init();
	TMR_Timer0_OVF_SetCallBack(LM35_StartConversion); //Timer trigger ADC
	TMR_Timer0Start();
	/*We initialize ADC peripheral as single conversion mode and set the temperature control function as*/
	/*The ADC conversion complete interrupt function*/
	ADC_ConversionCompleteSetCallback(LM35_TempControl);
	ADC_Init();
	KPD_Init();
	/*We initialize timer 2 to which its OC pin connected to dimming LED*/
	TMR_Timer2Init();

	/*We set the Rx Pin of UART Peripheral to be input "Receive whats comming from bluetooth module"*/
	/*We set the Tx pin of UART Peripheral to be output "Send Strings which we want to display on mobile"*/
	DIO_SetPinDirection(DIO_PORTD, DIO_PIN0, DIO_PIN_INPUT); //Rx
	DIO_SetPinDirection(DIO_PORTD, DIO_PIN1, DIO_PIN_OUTPUT); //Tx

	/*We set the Interface function as the UART Rx Complete Interrupt Function*/
	UART_RxCompleteSetCallback(HC05_AdminUserInterface);
	/*Then, We initialize UART*/
	UART_Init();

	/*We Check to see if the Admin Username and password are already saved in the memory or not*/
	Internal_EEPROM_ReadByte(HC05_ADMIN_SAVED_STATUS_MEM_ADDRESS, &Loc_u8Value);

	/*
		As a default, we set the Admin's information as follows:
		Username: 2
		Password: 123
	*/
	if (1 != Loc_u8Value)
	{
		/*Means that the Admin's information is not saved and needs to be saved*/
		LCD_WriteString("First Entry!");
		_delay_ms(2000);
		LCD_ClearDisplay();
		HC05_AdminUsernamePasswordSaver();
	}
	/*We send the welcoming message on both the LCD and Mobile*/
	USER_PROGRAM_START();
	HC05_WelcomeMessage();

	u8 Loc_u8UserInput = KPD_NOT_PRESSED;
    while (1) 
    {
		/*Here, we check to see if the user wants to login or not*/
		LCD_WriteString("WANT TO LOGIN?");
		
		LCD_SetCursorPosition(LCD_SECOND_ROW, 0);
		LCD_WriteString("1:Yes    2:No");
		_delay_ms(1000);
		LCD_ClearDisplay();
		while(Loc_u8UserInput == KPD_NOT_PRESSED)
		{
			KPD_GetValue(&Loc_u8UserInput);
		}
		if('1' == Loc_u8UserInput)
		{
			/*Means that the user wants to login*/
			USER_APP();
		}
		else if('2' == Loc_u8UserInput)
		{
			/*Means that the user doesn't want to login at the moment*/
			/*In that case, we display the status of the devices on LCD*/
			LCD_ClearDisplay();
			HC05_ShowRunningDevices();
		}
		else
		{
			/*Do nothing*/
		}
		Loc_u8UserInput = KPD_NOT_PRESSED;
	}
	return 0;
}

void LM35_StartConversion(void)
{
	/*We set timer 0 to start ADC conversion approximately every 4ms which is more than the ADC peripheral*/
	/*needs to convert analog signal coming from temperature sensor (max. 260 us)*/
	ADC_StartConversion(ADC_CHANNEL_0);
}
/*LM35 Temp Sensor gives us 10mv/degree*/
/*-15 ---> 55*/
void LM35_TempControl(void)
{
	u16 Loc_u16ADCValue = 0;
	ADC_GetDigitalValueAsynchronous(&Loc_u16ADCValue);
	/*
							ADC_DigitalValue * 2.56
		ADC_Voltage_Value = -----------------------
									1024
		LM35_Temperature = ADC_Voltage_Value * 100
		So, LM35_Temperature approximately equal to ADC_DigitalValue / 4
	*/
	u8 Loc_u8Temp = Loc_u16ADCValue / 4; 
	/*
		If Temperature is greater than 28 degrees ----> Turn on Air conditioner "Relay"
		If Temperature is less than 21 degrees ----> Turn off Air conditioner "Relay"
	*/
	if(Loc_u8Temp < 21)
	{
		DIO_SetPinValue(DIO_PORTA,DIO_PIN2,DIO_PIN_LOW);
	}
	else if(Loc_u8Temp > 28)
	{
		DIO_SetPinValue(DIO_PORTA,DIO_PIN2,DIO_PIN_HIGH);
	}
	else
	{
		/*Do nothing*/
	}
	
}

