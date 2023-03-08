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
#include "DCM_Interface.h"
#include "SRVM_Interface.h"
#include "LED_Interface.h"
#include "TMR_Interface.h"
#include "ADC_Interface.h"
#include "KPD_Interface.h"

#include "USER_interface.h"
#include "HC05_Interface.h"

#define F_CPU 16000000UL
#include <util/delay.h>
int main(void)
{
	u8 Loc_u8Value = 0;
	LCD_Init();
	SRVM_Init();
	ADC_Init();
	KPD_Init();
	
	TMR_Timer2Init();
	DIO_SetPinDirection(DIO_PORTD, DIO_PIN0, DIO_PIN_INPUT); //Rx
	DIO_SetPinDirection(DIO_PORTD, DIO_PIN1, DIO_PIN_OUTPUT); //Tx
	DIO_SetPinDirection(DIO_PORTC, DIO_PIN2, DIO_PIN_OUTPUT);
	GI_Enable();
	UART_RxCompleteSetCallback(HC05_AdminUserInterface);
	UART_Init();
	Internal_EEPROM_ReadByte(HC05_ADMIN_SAVED_STATUS_MEM_ADDRESS, &Loc_u8Value);
	if (1 != Loc_u8Value)
	{
		LCD_WriteString("First Entry");
		_delay_ms(2000);
		LCD_ClearDisplay();
		HC05_AdminUsernamePasswordSaver();
	}
	USER_PROGRAM_START();
	HC05_WelcomeMessage();
	u8 user_input = KPD_NOT_PRESSED;
    while (1) 
    {
		LCD_WriteString("WANT TO");
		LCD_SetCursorPosition(LCD_SECOND_ROW, 0);
		LCD_WriteString("LOGIN?");
		_delay_ms(1000);
		LCD_ClearDisplay();
		LCD_WriteString("1.Yes    2.No");
		LCD_SetCursorPosition(LCD_SECOND_ROW, 0);
		while(1)
		{
			if(user_input==KPD_NOT_PRESSED)
			{
				KPD_GetValue(&user_input);
			}
			else
			{
				break;
			}
		}
		if(user_input == '1')
		{
			USER_APP();
		}
		else if(user_input == '2')
		{
			user_input = KPD_NOT_PRESSED;
			AC_Auto();
			HC05_ShowRunningDevices();
		}
    }
}

