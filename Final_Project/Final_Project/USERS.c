/*
 * USERS.c
 *
 * Created: 2/26/2023 2:10:35 PM
 *  Author: Medhat
 */ 


#define F_CPU 16000000UL
#include <util/delay.h>

/* UTILES_LIB */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ATMEGA32_REG.h"

/* MCAL */
#include "DIO_interface.h"

/* HAL */
#include "LCD_interface.h"
#include "KPD_interface.h"
#include "Internal_EEPROM_Interface.h"
#include "USER_interface.h"
#include "BUZZER_Interface.h"
#include "UART_Interface.h"
#include "TMR_Interface.h"

#include "HC05_Interface.h"

//count number of users in program
static u8 counter = 50 ;
//variable to check if user exist or not
u8 user_exist = 0 ;
//BUZZER INDECATION WHEN USER ENTER WRONG PASS MORE THAN 3 TIMES
u8 buzzer_check = 0 ;


//FUNCTION TO START PROGRAM AND ENTER ADMIN DATA
void USER_PROGRAM_START(void)
{
	//activate KeyBad and LCD
	LCD_Init();
	KPD_Init();
	LCD_WriteString("WELCOME TO");
	LCD_SetCursorPosition(LCD_SECOND_ROW,0);
	LCD_WriteString("SMART HOME");
	_delay_ms(2000);
	LCD_ClearDisplay();
	
	
}


///////////////////////////////////////*************************///////////////////////////////


//FUNCTION TO LOGIN USER OR ADMIN
u8 USER_LOGIN(void)
{
	u8 original_id;
	u8 ID = KPD_NOT_PRESSED;
	u8 original_pass_arr[3];
	u8 PASS_Arr[3];

	
	//GET USER ID
	LCD_WriteString("ENTER USER ID");
	while(ID == KPD_NOT_PRESSED)
	{
		KPD_GetValue(&ID);
	}
	LCD_WriteChar4Bit(ID);
	_delay_ms(2000);
	LCD_ClearDisplay();
	
	LCD_WriteString("ENTER PASSWORD[3]");
	LCD_SetCursorPosition(LCD_SECOND_ROW, 0);
	u8 index = 0;
	//Take Password From User
	while(1)
	{
		KPD_GetValue(&PASS_Arr[index]);
		if (PASS_Arr[index] != KPD_NOT_PRESSED)
		{
			LCD_WriteChar4Bit(PASS_Arr[index]);
			index++;
			if (index == 3)
			{
				break;
			}
		}
	}
	_delay_ms(1000);
	LCD_ClearDisplay();

	u8 NoOfUsers = 0;
	u8 address = 0;
	u8 ID_Pass_Check = 0;
	u8 ID_Correct = 0;
	Internal_EEPROM_ReadByte(10, &NoOfUsers);
	for(index = 1; index < NoOfUsers; index++)
	{
		address = 50 + (4 * index);
		Internal_EEPROM_ReadByte(address, &ID_Pass_Check);
		if(ID_Pass_Check == ID)
		{
			ID_Correct = 1;
			break;
		}
	}
	if(ID_Correct == 1)
	{
		address++;
		for(index = 0; index < 3; index++)
		{
			Internal_EEPROM_ReadByte(address, &ID_Pass_Check);
			if(ID_Pass_Check != PASS_Arr[index])
			{
				LCD_WriteString("WRONG PASS");
				user_exist = 0;
				_delay_ms(1000);
				LCD_ClearDisplay();
				buzzer_check++;
				
				return user_exist;
				break;
			}
			address++;
		}
		user_exist = 1;
		LCD_WriteString("LOGIN SUCCESS");
		_delay_ms(1000);
		LCD_ClearDisplay();
		if (buzzer_check == 3 )
		{
			buzzer_check = 0 ;
			BUZZER_On();
			_delay_ms(3000);
			BUZZER_Off();
		}
		return user_exist;
	}
	else
	{
		LCD_WriteString("WRONG ID");
		user_exist = 0;
		_delay_ms(1000);
		LCD_ClearDisplay();
		buzzer_check++;
		if (buzzer_check == 3 )
		{
			buzzer_check = 0 ;
			BUZZER_On();
			_delay_ms(3000);
			BUZZER_Off();
		}
		return user_exist;
	}
}



///////////////////////////////////////*************************///////////////////////////////



//function contain all options of program so user can do what he want
u8 USER_PROGRAM(void)
{
	u8 user_input = KPD_NOT_PRESSED ;
	LCD_WriteString("choose the task");
	_delay_ms(2000);
	LCD_ClearDisplay();
	
	LCD_WriteString("1.control lamp");
	_delay_ms(2000);
	LCD_ClearDisplay();
	
	LCD_WriteString("2.Log out");
	_delay_ms(2000);
	LCD_ClearDisplay();

	LCD_WriteString("choose now");
	_delay_ms(2000);
	LCD_ClearDisplay();
	
	
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
	LCD_WriteChar4Bit(user_input);
	_delay_ms(1000);
	LCD_ClearDisplay();
	u8 AdminAnswer = 0;

	switch(user_input)
	{
		case '1':
		{
			if(HC05_AdminLoginCheck() == ADMIN_LOGGED_ON)
			{
				UART_TxString("User wants to control a LED. Do you allow it?\n");
				UART_TxString("1: Yes        2: No\n");
				HC05_ScreenChangeToAdminResponse();
				while(1)
				{
					AdminAnswer = HC05_AdminApproval();
					if(AdminAnswer != ADMIN_NOT_REPLIED)
					{
						break;
					}
				}
			}
			if(AdminAnswer == ADMIN_APPROVE)
			{
				USER_Control_Leds();
			}
			else if(AdminAnswer == ADMIN_REFUSE)
			{
				LCD_WriteString("ADMIN REFUSED");
			}
			break;
		}
		
		case '2':
		{
			USER_LOGOUT();
			return 0 ;
			break;
		}
	}
	return 1 ;
}



///////////////////////////////////////*************************///////////////////////////////



//Function To Control LED By user
void USER_Control_Leds(void)
{
	//Make directions of Led Pins OUTPUT
	DIO_SetPinDirection(DIO_PORTC,DIO_PIN2,DIO_PIN_OUTPUT);
	DIO_SetPinDirection(DIO_PORTC,DIO_PIN7,DIO_PIN_OUTPUT);
	DIO_SetPinDirection(DIO_PORTD,DIO_PIN3,DIO_PIN_OUTPUT);
	DIO_SetPinDirection(DIO_PORTC,DIO_PIN0,DIO_PIN_OUTPUT);
	DIO_SetPinDirection(DIO_PORTC,DIO_PIN1,DIO_PIN_OUTPUT);
	DIO_SetPinDirection(DIO_PORTD,DIO_PIN7,DIO_PIN_OUTPUT);
	
	//give user options to control
	u8 user_input1 = KPD_NOT_PRESSED ;
	LCD_WriteString("choose LED ");
	_delay_ms(2000);
	LCD_ClearDisplay();
	
	LCD_WriteString("1.LED1");
	_delay_ms(2000);
	LCD_ClearDisplay();
	
	LCD_WriteString("2.LED2");
	_delay_ms(2000);
	LCD_ClearDisplay();

	LCD_WriteString("3.LED3");
	_delay_ms(2000);
	LCD_ClearDisplay();
	
	LCD_WriteString("4.LED4");
	_delay_ms(2000);
	LCD_ClearDisplay();
	
	LCD_WriteString("5.LED5");
	_delay_ms(2000);
	LCD_ClearDisplay();
	
	LCD_WriteString("6.DIMMING LED");
	_delay_ms(2000);
	LCD_ClearDisplay();

	//TAKE INPUT FROM USER
	while(1)
	{
		if(user_input1==KPD_NOT_PRESSED)
		{
			KPD_GetValue(&user_input1);
		}
		else
		{
			break;
		}
	}
	LCD_WriteChar4Bit(user_input1);
	_delay_ms(1000);
	LCD_ClearDisplay();
	
	//CHOOSE ON OR OFF
	LCD_WriteString("1.ON");
	_delay_ms(2000);
	LCD_ClearDisplay();
	
	LCD_WriteString("2.OFF");
	_delay_ms(2000);
	LCD_ClearDisplay();
	
	u8 user_input2 = KPD_NOT_PRESSED ;
	while(1)
	{
		if(user_input2==KPD_NOT_PRESSED)
		{
			KPD_GetValue(&user_input2);
		}
		else
		{
			break;
		}
	}
	LCD_WriteChar4Bit(user_input2);
	_delay_ms(1000);
	LCD_ClearDisplay();
	
	////ON
	if (user_input1=='1' && user_input2=='1')
	{
		DIO_SetPinValue(DIO_PORTC,DIO_PIN2,DIO_PIN_HIGH);
		LCD_WriteString("TASK DONE");
		_delay_ms(2000);
		LCD_ClearDisplay();
	}
	
	else if (user_input1=='2' && user_input2=='1')
	{
		DIO_SetPinValue(DIO_PORTC,DIO_PIN7,DIO_PIN_HIGH);
		LCD_WriteString("TASK DONE");
		_delay_ms(2000);
		LCD_ClearDisplay();
	}
	
	else if (user_input1=='3' && user_input2=='1')
	{
		DIO_SetPinValue(DIO_PORTD,DIO_PIN3,DIO_PIN_HIGH);
		LCD_WriteString("TASK DONE");
		_delay_ms(2000);
		LCD_ClearDisplay();
	}
		else if (user_input1=='4' && user_input2=='1')
	{
		DIO_SetPinValue(DIO_PORTC,DIO_PIN0,DIO_PIN_HIGH);
		LCD_WriteString("TASK DONE");
		_delay_ms(2000);
		LCD_ClearDisplay();
	}
	else if (user_input1=='5' && user_input2=='1')
	{
		DIO_SetPinValue(DIO_PORTC,DIO_PIN1,DIO_PIN_HIGH);
		LCD_WriteString("TASK DONE");
		_delay_ms(2000);
		LCD_ClearDisplay();
	}
	else if (user_input1=='6' && user_input2=='1')
	{
		LCD_WriteString("CHOOSE BRIGHT");
		_delay_ms(2000);
		LCD_ClearDisplay();

		LCD_WriteString("1.20%    2.40%");
		LCD_SetCursorPosition(LCD_SECOND_ROW,0);
		LCD_WriteString("3.60%    2.80%");

		_delay_ms(2000);
		LCD_ClearDisplay();

		LCD_WriteString("5.100%");
		LCD_SetCursorPosition(LCD_SECOND_ROW, 0);

		u8 user_input3 = KPD_NOT_PRESSED;
		while(1)
		{
			if(user_input3==KPD_NOT_PRESSED)
			{
				KPD_GetValue(&user_input3);
			}
			else
			{
				break;
			}
		}

		switch(user_input3)
		{
			case '1':
			{
				TMR_Timer2Stop();
                TMR_Timer2Set_PWM_DutyCycle(20);
                TMR_Timer2Start();
				break;
			}
			case '2':
			{
				TMR_Timer2Stop();
                TMR_Timer2Set_PWM_DutyCycle(40);
                TMR_Timer2Start();
				break;
			}
			case '3':
			{
				TMR_Timer2Stop();
                TMR_Timer2Set_PWM_DutyCycle(60);
                TMR_Timer2Start();
				break;
			}
			case '4':
			{
				TMR_Timer2Stop();
                TMR_Timer2Set_PWM_DutyCycle(80);
                TMR_Timer2Start();
				break;
			}
			case '5':
			{
				TMR_Timer2Stop();
                TMR_Timer2Set_PWM_DutyCycle(100);
                TMR_Timer2Start();
				break;
			}
			default:
			{
				break;
			}
		}	
	}
	
	///OFF	
	
	if (user_input1=='1' && user_input2=='2')
	{
		DIO_SetPinValue(DIO_PORTC,DIO_PIN2,DIO_PIN_LOW);
		LCD_WriteString("TASK DONE");
		_delay_ms(2000);
		LCD_ClearDisplay();
	}

	else if (user_input1=='2' && user_input2=='2')
	{
		DIO_SetPinValue(DIO_PORTC,DIO_PIN7,DIO_PIN_LOW);
		LCD_WriteString("TASK DONE");
		_delay_ms(2000);
		LCD_ClearDisplay();
	}

	else if (user_input1=='3' && user_input2=='2')
	{
		DIO_SetPinValue(DIO_PORTD,DIO_PIN3,DIO_PIN_LOW);
	LCD_WriteString("TASK DONE");
	_delay_ms(2000);
	LCD_ClearDisplay();
	}
	
	else if (user_input1=='4' && user_input2=='2')
	{
		DIO_SetPinValue(DIO_PORTC,DIO_PIN0,DIO_PIN_LOW);
	LCD_WriteString("TASK DONE");
	_delay_ms(2000);
	LCD_ClearDisplay();
	}

	else if (user_input1=='5' && user_input2=='2')
	{
	DIO_SetPinValue(DIO_PORTC,DIO_PIN1,DIO_PIN_LOW);
	LCD_WriteString("TASK DONE");
	_delay_ms(2000);
	LCD_ClearDisplay();
	}

	else if (user_input1=='6' && user_input2=='2')
	{
		TMR_Timer2Stop();
		DIO_SetPinValue(DIO_PORTD,DIO_PIN7,DIO_PIN_LOW);
		LCD_WriteString("TASK DONE");
		_delay_ms(2000);
		LCD_ClearDisplay();
	}
}



///////////////////////////////////////*************************///////////////////////////////


//FUNCTION MAKE USER LOG OUT
void USER_LOGOUT(void)
{
	LCD_WriteString("Thank You");
	_delay_ms(2000);
	LCD_ClearDisplay();
	
	user_exist = 0 ;
	
}



///////////////////////////////////////*************************///////////////////////////////



u8 USER_EXIST(void)
{
	return user_exist;
}

///////////////////////////////////////*************************///////////////////////////////


void USER_APP(void)
{
	u8 check1 = 0 ;
	u8 check2 = 0 ;
	check1 = USER_LOGIN();
	if(check1==1)
	{
		while(1)
		{
			check2 = USER_PROGRAM();
			AC_Auto();
			if(check2==0)
			{
				break;	
			}
		}
	}
	else
	{
	}
}
