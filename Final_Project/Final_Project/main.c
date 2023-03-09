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
	LCD_Init();
	SRVM_Init();
	BUZZER_Init();
	GI_Enable();

	DIO_SetPinDirection(DIO_PORTA, DIO_PIN0, DIO_PIN_INPUT);
	DIO_SetPinDirection(DIO_PORTA, DIO_PIN2, DIO_PIN_OUTPUT);
	TMR_Timer0Init();
	TMR_Timer0_OVF_SetCallBack(LM35_StartConversion);
	TMR_Timer0Start();
	ADC_ConversionCompleteSetCallback(LM35_TempControl);
	ADC_Init();
	KPD_Init();
	TMR_Timer2Init();
	DIO_SetPinDirection(DIO_PORTD, DIO_PIN0, DIO_PIN_INPUT); //Rx
	DIO_SetPinDirection(DIO_PORTD, DIO_PIN1, DIO_PIN_OUTPUT); //Tx
	UART_RxCompleteSetCallback(HC05_AdminUserInterface);
	UART_Init();
	Internal_EEPROM_ReadByte(HC05_ADMIN_SAVED_STATUS_MEM_ADDRESS, &Loc_u8Value);
	if (1 != Loc_u8Value)
	{
		LCD_WriteString("First Entry!");
		_delay_ms(2000);
		LCD_ClearDisplay();
		HC05_AdminUsernamePasswordSaver();
	}
	USER_PROGRAM_START();
	HC05_WelcomeMessage();
	u8 Loc_u8UserInput = KPD_NOT_PRESSED;
    while (1) 
    {
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
			USER_APP();
		}
		else if('2' == Loc_u8UserInput)
		{
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
	ADC_StartConversion(ADC_CHANNEL_0);

}
/*LM35 Temp Sensor gives us 10mv/degree*/
void LM35_TempControl(void)
{
	u16 Loc_u16ADCValue = 0;
	ADC_GetDigitalValueAsynchronous(&Loc_u16ADCValue);
	u8 Loc_u8Temp = Loc_u16ADCValue / 4; //LM35
	
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

