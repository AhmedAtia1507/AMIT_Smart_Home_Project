/**
 * @file HC05_Program.c
 * @author Ahmed Atia (atiaa6501@gmail.com)
 * 
 * @version 1.0
 * @date 2023-02-26
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "ATMEGA32_REG.h"
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "UART_Interface.h"

#include "Internal_EEPROM_Interface.h"
#include "DIO_Interface.h"
#include "LCD_Interface.h"
#include "LED_Interface.h"
#include "BUZZER_Interface.h"
#include "TMR_Interface.h"
#include "SRVM_Interface.h"

#include "HC05_Interface.h"
#include "HC05_Config.h"

#define F_CPU 16000000
#include <util/delay.h>

static u8 glbl_u8AdminMode = ADMIN_MODE_OFF;
static u8 glbl_u8UserMode = USER_MODE_OFF;
static u8 glbl_u8AdminUserChoice[3] = {0};
static u8 glbl_u8AdminUserUsername[6] = {0};
static u8 glbl_u8AdminUserPassword[5] = {0};
static u8 glbl_u8PreviousScreen = 0;
static u8 glbl_u8CurrentScreen = 0;
static u8 glbl_u8LEDChoice = 0;
static u8 glbl_u8UserPasswordWrongCount = 0;
static u8 glbl_u8DimmingLEDStatus = 0;
static u8 glbl_u8DoorStatus = 0;
static u8 glbl_u8AdminApproval = ADMIN_NOT_REPLIED;

/********************************************************************************************************************/

/**
 * @brief: Function to send a welcome message to the user/admin
 * 
 */
void HC05_WelcomeMessage(void)
{
    UART_TxString("Hello! Welcome to Smart Home\n");
    UART_TxString("Please enter whether you are admin or a user\n");
    UART_TxString("1:Admin    2: User\n");
    glbl_u8CurrentScreen = HC05_WELCOME_SCREEN;
}

/********************************************************************************************************************/


/**
 * @brief: Function to set the admin username and password for the first time
 * 
 */
void HC05_AdminUsernamePasswordSaver(void)
{
    /*Write Admin UserName "2" to the specified Admin EEPROM Memory address "50"*/
    Internal_EEPROM_WriteByte(HC05_ADMIN_MEM_ADDRESS, HC05_ADMIN_USERNAME);

    u8 Loc_u8Index = 0; 
	u16 Loc_u8Address = 0;

    /*Save Admin Password in the EEPROM "123" */
    for(Loc_u8Index = 0; Loc_u8Index < HC05_PASSWD_SIZE; Loc_u8Index++)
    {
        Loc_u8Address = HC05_ADMIN_MEM_ADDRESS + Loc_u8Index + 1;
        Internal_EEPROM_WriteByte(Loc_u8Address, HC05_ADMIN_PASSWRD[Loc_u8Index]);
    }
    /*Set number of users to be 1 and save it in EEPROM*/
	Internal_EEPROM_WriteByte(HC05_NO_USERS_MEM_ADDRESS, 1);

    /*We save this status in EEPROM to show that the Admin username and password is successfully*/
    /*Saved in EEPROM*/
	Internal_EEPROM_WriteByte(HC05_ADMIN_SAVED_STATUS_MEM_ADDRESS, 1);
}

/********************************************************************************************************************/

/**
 * @brief: Function to check if the password is correct or not
 * 
 * @return u8: The result of the check
 */
u8 HC05_UsernamePasswordCheck(void)
{
    u8 Loc_u8Index = 0;
    u8 Loc_u8Username = 0; 
    u8 Loc_u8Pass = 0;

    if(glbl_u8AdminMode == 1) //Check if the User chose admin mode
    {
        /*Read Admin Username from EEPROM and save it in this variable*/
        Internal_EEPROM_ReadByte(HC05_ADMIN_MEM_ADDRESS, &Loc_u8Username);

        /*Check if the username read from memory equals the username entered by user/admin*/
        if(glbl_u8AdminUserUsername[0] == Loc_u8Username)
        {
            /*Username is correct*/
            for(Loc_u8Index = 0; Loc_u8Index < HC05_PASSWD_SIZE; Loc_u8Index++)
            {
                /*Read Admin Password from memory to check if the entered password is correct or not*/
                Internal_EEPROM_ReadByte((HC05_ADMIN_MEM_ADDRESS + Loc_u8Index + 1), &Loc_u8Pass);

                if(Loc_u8Pass != glbl_u8AdminUserPassword[Loc_u8Index])
                {
                    /*Means that the entered password is not correct*/
                    UART_TxString("Sorry, Invalid Password\n");
                    return HC05_USERNAME_PASSOWRD_INCORRECT;
                    break;
                }
            }
            /*Username and Password are correct*/
            return HC05_USERNAME_PASSOWRD_CORRECT;
        }
        else
        {
            /*Username is incorrect*/
            UART_TxString("Sorry, Invalid username\n");
            return HC05_USERNAME_PASSOWRD_INCORRECT;
        }
    }
    else if(glbl_u8UserMode == 1) //User has chosen user mode
    {
        u8 Loc_u8NoOfUsers = 0;
        u8 Loc_u8CorrectUserAddress = 0;

        /*Save the current number of users/admin*/
        Internal_EEPROM_ReadByte(HC05_NO_USERS_MEM_ADDRESS, &Loc_u8NoOfUsers);

        for(Loc_u8Index = 1; Loc_u8Index < Loc_u8NoOfUsers; Loc_u8Index++)
        {
            /*Read the existing Usernames of users saved and check if the entered username matches one of them*/
            /*or not*/
            Internal_EEPROM_ReadByte((HC05_ADMIN_MEM_ADDRESS + (4 * Loc_u8Index)) , &Loc_u8Username);
            if(glbl_u8AdminUserUsername[0] == Loc_u8Username)
            {
                /*means that the username exists in EEPROM*/
                /*We save this username address in order to check its password*/
                Loc_u8CorrectUserAddress = HC05_ADMIN_MEM_ADDRESS + (4 * Loc_u8Index);
            }
        }
        if(Loc_u8CorrectUserAddress == 0)
        {
            /*Means that the username does not exist*/
            UART_TxString("Sorry, Invalid username\n");
            return HC05_USERNAME_PASSOWRD_INCORRECT;
        }

        for(Loc_u8Index = 0; Loc_u8Index < HC05_PASSWD_SIZE; Loc_u8Index++)
        {
            /*Read the user ,whose username matches the entered username, password and check if it matches the*/
            /*entered password*/
            Internal_EEPROM_ReadByte((Loc_u8CorrectUserAddress + 1 + Loc_u8Index),&Loc_u8Pass);
            if(Loc_u8Pass != glbl_u8AdminUserPassword[Loc_u8Index])
            {
                /*Means that the password entered is incorrect*/
                UART_TxString("Sorry, Invalid password\n");
                return HC05_USERNAME_PASSOWRD_INCORRECT;
            } 
        }
        return HC05_USERNAME_PASSOWRD_CORRECT;
    }
    else
    {
        /*Means that the user input is wrong*/
        UART_TxString("Sorry, Wrong Input\n");
        return HC05_USERNAME_PASSOWRD_INCORRECT;
    }
}

/********************************************************************************************************************/

/**
 * @brief: Function to check whether the admin is logged on or not
 * 
 * @return u8: Status of the Admin Login
 */
u8 HC05_AdminLoginCheck(void)
{
    /*Return the status of admin mode to check if admin is currently using the system or not*/
    return glbl_u8AdminMode;
}

/********************************************************************************************************************/

/**
 * @brief: Function to show the admin/user choice list after logging in
 * 
 */
void HC05_AdminUserChoiceList(void)
{ /*AC Automatic*/
    UART_TxString("Welcome\n");
    UART_TxString("Choose the service you wish to do\n");
    UART_TxString("1: Door\n");
    UART_TxString("2: LEDs\n");
	UART_TxString("3: Add User\n");
	UART_TxString("4: Delete User\n");
    UART_TxString("5: Log Out\n");
}

/**
 * @brief: Function to show the admin/user LED Choice list
 * 
 */
void HC05_AdminUserLEDChoice(void)
{
    UART_TxString("Please select the LED you wish to control\n");
    UART_TxString("1: LED 1\n");
    UART_TxString("2: LED 2\n");
    UART_TxString("3: LED 3\n");
    UART_TxString("4: LED 4\n");
    UART_TxString("5: LED 5\n");
    UART_TxString("6: Dimming LED\n");
}
/********************************************************************************************************************/

/**
 * @brief: Function to check if the username entered exists in EEPROM or not
 * 
 * @return u8 
 */
u8 HC05_UserNamePasswordExist(void)
{
    u8 Loc_u8NoOfUsers = 0;
    /*Read the current number of users/admin in the system*/
    Internal_EEPROM_ReadByte(HC05_NO_USERS_MEM_ADDRESS, &Loc_u8NoOfUsers);

    u8 Loc_u8Index = 0;
    u8 Loc_u8Username = 0;
    
    for(Loc_u8Index = 1; Loc_u8Index < Loc_u8NoOfUsers; Loc_u8Index++)
    {
        /*Read the users' usernames currently in EEPROM and check if entered username matches one of them*/
        Internal_EEPROM_ReadByte((HC05_ADMIN_MEM_ADDRESS + (4 * Loc_u8Index)) , &Loc_u8Username);
        if(glbl_u8AdminUserUsername[0] == Loc_u8Username)
        {
            /*User entered already exists in EEPROM*/
            UART_TxString("Sorry, User Already Exists\n");
            return HC05_USER_EXIST;
        }
    }
    /*Means that the username entered is not found in EEPROM*/
    return HC05_USER_NOT_EXIST;
}

/********************************************************************************************************************/

/**
 * @brief: Function to add new user to EEPROM
 * 
 */
void HC05_AddNewUser(void)
{
    u8 Loc_u8NoOfUsers = 0;
    /*Read number of users/admin from the EEPROM*/
    Internal_EEPROM_ReadByte(HC05_NO_USERS_MEM_ADDRESS, &Loc_u8NoOfUsers);

    /*Set the address to be the last address not accessed by system*/
    /*We add the user at the end*/
    u8 Loc_u8Address = HC05_ADMIN_MEM_ADDRESS + (4 * Loc_u8NoOfUsers);
    
    /*we enter the new username in the empty place in EEPROM*/
    Internal_EEPROM_WriteByte((Loc_u8Address), glbl_u8AdminUserUsername[0]);
    
    u8 Loc_u8Index = 0;

    /*We increment the address so that it points to the new user password address*/
    Loc_u8Address ++;

    for(Loc_u8Index = 0; Loc_u8Index < HC05_PASSWD_SIZE; Loc_u8Index++)
    {
        /*We enter the new user password in memory*/
        Internal_EEPROM_WriteByte((Loc_u8Address + Loc_u8Index), glbl_u8AdminUserPassword[Loc_u8Index]);
    }

    /*Increase the number of users by one and saving the new number of users*/
    Loc_u8NoOfUsers++;
    Internal_EEPROM_WriteByte(HC05_NO_USERS_MEM_ADDRESS, Loc_u8NoOfUsers);
    UART_TxString("User Successfully added\n");
}

/********************************************************************************************************************/

/**
 * @brief: Function to delete a user from the EEPROM
 * 
 */
void HC05_DeleteUser(void)
{
    u8 Loc_u8NoOfUsers = 0;
    u8 Loc_u8Index = 0;
    u8 Loc_u8UserIndex = 0;
    u8 Loc_u8UserName = 0;
    u8 Loc_u8Address = 0;

    /*Read the number of users/admin from EEPROM*/
    Internal_EEPROM_ReadByte(HC05_NO_USERS_MEM_ADDRESS, &Loc_u8NoOfUsers);
    
    /*Check to see if the username entered exists or not*/
    for(Loc_u8Index = 1; Loc_u8Index < Loc_u8NoOfUsers; Loc_u8Index++)
    {
        Loc_u8Address = HC05_ADMIN_MEM_ADDRESS + (4 * Loc_u8Index);
        Internal_EEPROM_ReadByte(Loc_u8Address, &Loc_u8UserName);
        if(Loc_u8UserName == glbl_u8AdminUserUsername[0])
        {
            /*The entered username exists*/
            /*We take the user index and save it to be used in the delete operation*/
            Loc_u8UserIndex = Loc_u8Index; 
            break;
        }
    }
    if(Loc_u8UserIndex != 0)
    {
        /*User is found in EEPROM*/
        u8 Loc_u8SwapVariable = 0;
        Loc_u8Address = HC05_ADMIN_MEM_ADDRESS + (4 * Loc_u8UserIndex); //Address of user to be deleted

        /*Here, we don't literally delete the user from memory, we just overwrite on it with the next in line user's 
        data and we repeat that until all the data are in line and the user to be deleted data is removed*/ 
        for(Loc_u8Index = Loc_u8UserIndex; Loc_u8Index < (Loc_u8NoOfUsers * 4); Loc_u8Index++)
        {
            /*We here get the data from the address + 4 'user size + password size'  and put it in the address*/
            Internal_EEPROM_ReadByte((Loc_u8Address + 4), &Loc_u8SwapVariable);
            Internal_EEPROM_WriteByte(Loc_u8Address, Loc_u8SwapVariable);
            Loc_u8Address++;
        }
        UART_TxString("User Successfully Deleted\n");
    }
    else
    {
        /*User is not found in EEPROM*/
        UART_TxString("Sorry. User Not Found\n");
    }
}
/********************************************************************************************************************/


/**
 * @brief: Function to organize the operation of user/admin
 * 
 */
void HC05_AdminUserInterface(void)
{
    /*Here is the main function of HC05 Bluetooth module. It organizes the operations in the form of states*/
    switch(glbl_u8CurrentScreen)
    {
        case HC05_WELCOME_SCREEN:
        {
            /*Here, We get the user choice whether it is an admin or a user and save it*/
            UART_RxString(glbl_u8AdminUserChoice);

            /*Then, we check for the user's input*/
			if('1' == glbl_u8AdminUserChoice[0])
			{
                /*Means that the user has chosen to enter as an admin*/
				glbl_u8AdminMode = ADMIN_MODE_ON;
				UART_TxString("Hello Admin\n");
				UART_TxString("Please enter your username: \n");

                /*We here switch the state to be login username screen*/
				glbl_u8CurrentScreen = HC05_LOGIN_USERNAME_SCREEN;
			}
			else if('2' == glbl_u8AdminUserChoice[0])
			{
                /*Means that the user has chosen to enter as an admin*/
				glbl_u8UserMode = USER_MODE_ON;
				UART_TxString("Hello User\n");
				UART_TxString("Please enter your username: \n");

                /*We here switch the state to be login username screen*/
				glbl_u8CurrentScreen = HC05_LOGIN_USERNAME_SCREEN;
			}
			else
			{
                /*User has entered a wrong input*/
                UART_TxString("Sorry, Wrong Input\n");
                HC05_WelcomeMessage();
				/*Do nothing*/
			}
			break;
		}
        case HC05_LOGIN_USERNAME_SCREEN:
        {
            /*Here, we receive the entered login username*/
            UART_RxString(glbl_u8AdminUserUsername);
			UART_TxString("Please enter your password\n");

            /*Then, we switch the state to be the login password screen*/
            glbl_u8CurrentScreen = HC05_LOGIN_PASSWORD_SCREEN;
            break;
        }
        case HC05_LOGIN_PASSWORD_SCREEN:
        {
            /*Here, we receive the entered login password*/
            UART_RxString(glbl_u8AdminUserPassword);

            /*We check if the entered username and password are correct or not*/
            u8 Loc_u8UserPassCheck = HC05_UsernamePasswordCheck();

            if(Loc_u8UserPassCheck == HC05_USERNAME_PASSOWRD_CORRECT)
            {
                /*Means that the entered username and password are correct*/
                if(glbl_u8AdminMode == ADMIN_MODE_ON)
                {
                    glbl_u8AdminMode = ADMIN_LOGGED_ON;
                }
                else if(glbl_u8UserMode == USER_MODE_ON)
                {
                    glbl_u8UserMode = USER_LOGGED_ON;
                }
                else
                {
                    /*Do nothing*/
                }
                /*Here, we show the user/admin the list of choices to choose from*/
                HC05_AdminUserChoiceList();
                /*Then, we switch the state*/
                glbl_u8CurrentScreen = HC05_SERVICES_SCREEN;
            }
			else
			{
                /*Means that the entered username or password or both is incorrect*/
                /*We count the number of failed trials so that if the number of failed trials is 3*/
                /*We fire an alarm and reset the whole operation*/
				glbl_u8UserPasswordWrongCount++;
				if (glbl_u8UserPasswordWrongCount != 3)
				{
					UART_TxString("Please enter your username\n");
				}
                glbl_u8CurrentScreen = HC05_LOGIN_USERNAME_SCREEN;
			}
			if(glbl_u8UserPasswordWrongCount == 3)
			{
                /*number of failed trials = 3*/
                /*Fire Alarm*/
				BUZZER_On();
				_delay_ms(3000);
				BUZZER_Off();

                /*Reset System ---------------------------------->*/
				HC05_WelcomeMessage();
                glbl_u8AdminMode = ADMIN_MODE_OFF;
                glbl_u8UserMode = USER_MODE_OFF;
				glbl_u8UserPasswordWrongCount = 0;
			}
            break;
        }
		case HC05_SERVICES_SCREEN:
		{
            /*We receive the user/Admin service choice*/
			UART_RxString(glbl_u8AdminUserChoice);
            
            if('1' == glbl_u8AdminUserChoice[0])
            {
                /*Means the User or admin wants to control door but only admin can control it*/
                if(glbl_u8AdminMode == ADMIN_LOGGED_ON)
                {
                    UART_TxString("Please select the type of operation you wish to do:\n");
					UART_TxString("1: Open Door\n");
                    UART_TxString("2: Close Door\n");
                    glbl_u8CurrentScreen = HC05_DOOR_CONTROL;
                }
                else if(glbl_u8UserMode == USER_LOGGED_ON)
                {
                    UART_TxString("Sorry. Only Admin is allowed to control door\n");
                    HC05_AdminUserChoiceList();
                }
                else
                {
                    /*Do nothing*/
                }
            }
            else if('2' == glbl_u8AdminUserChoice[0]) 
            {
                /*Means that the user/admin wants to control LEDs*/
                HC05_AdminUserLEDChoice();
                glbl_u8CurrentScreen = HC05_LEDS_CHOICE;
            }
            else if('3' == glbl_u8AdminUserChoice[0])
            {
                /*Means that the user/admin wants to add a new user*/
                if(glbl_u8AdminMode == ADMIN_LOGGED_ON)
                {
                    /*Admin wants to add a new user "Allowed"*/
					UART_TxString("Please Enter the new user's ID(max.9)\n");
                    glbl_u8CurrentScreen = HC05_ADD_USER_USERNAME_SCREEN;
                }
                else if(glbl_u8UserMode == USER_LOGGED_ON)
                {
                    /*Admin wants to add a new user "NOT Allowed"*/
                    UART_TxString("Sorry. Only Admin is allowed to create new user\n");
                    HC05_AdminUserChoiceList();
                }
                else
                {
                    /*Do nothing*/
                }
            }
            else if('4' == glbl_u8AdminUserChoice[0])
            {
                /*Means that the user/admin wants to delete a user*/
                if(glbl_u8AdminMode == ADMIN_LOGGED_ON)
                {
                    /*Admin wants to delete a user "Allowed"*/
			UART_TxString("Please enter the user's ID that you wish to delete\n");
                    glbl_u8CurrentScreen = HC05_DELETE_USER_SCREEN;
                }
                else if(glbl_u8UserMode == USER_LOGGED_ON)
                {
                    /*User wants to delete a  user "NOT Allowed"*/
                    UART_TxString("Sorry. Only Admin is allowed to delete a user\n");
                    HC05_AdminUserChoiceList();
                }
                else
                {
                    /*Do nothing*/
                }
            }
            else if('5' == glbl_u8AdminUserChoice[0])
            {
                /*Means that the user/admin wants to log out*/
                glbl_u8AdminMode = ADMIN_MODE_OFF;
                glbl_u8UserMode = USER_MODE_OFF;
                glbl_u8PreviousScreen = 0;
                glbl_u8LEDChoice = 0;
                UART_TxString("Logged Out Successfully\n");
                HC05_WelcomeMessage();
            }
            else
            {
                UART_TxString("Sorry,Wrong Input\n");
                HC05_AdminUserChoiceList();
            }
			break;
		}
        case HC05_DOOR_CONTROL:
        {
            /*The Admin wants to control door*/
            /*We receive the admin response whether he wants to open or close the door*/
            UART_RxString(glbl_u8AdminUserChoice);
            if('1' == glbl_u8AdminUserChoice[0])
            {
                /*Admin wants to open door "Set the angle of the servo motor to be 0 degrees"*/
                TMR_Timer1Stop();
                SRVM_SetRotationAngle(SRVM_ANGLE_POSITIVE, 0);
                TMR_Timer1Start();
                UART_TxString("Door Opened Successfully\n");
                HC05_AdminUserChoiceList();
                glbl_u8CurrentScreen = HC05_SERVICES_SCREEN;
                glbl_u8DoorStatus = DOOR_OPENED;
            }
            else if('2' == glbl_u8AdminUserChoice[0]) //Close Door
            {
                /*Admin wants to close door "Set the angle of the servo motor to be -90 degrees"*/
                TMR_Timer1Stop();
                SRVM_SetRotationAngle(SRVM_ANGLE_NEGATIVE, 90);
                TMR_Timer1Start();
                UART_TxString("Door Closed Successfully\n");
                HC05_AdminUserChoiceList();
                glbl_u8CurrentScreen = HC05_SERVICES_SCREEN;
                glbl_u8DoorStatus = DOOR_CLOSED;
            }
            else
            {
                /*Admin has entered wrong input*/
                UART_TxString("Sorry, Wrong Input\n");
                UART_TxString("Please select the type of operation you wish to do:\n");
				UART_TxString("1: Open Door\n");
                UART_TxString("2: Close Door\n");
            }
            break;
        }
        case HC05_LEDS_CHOICE:
        {
            /*User/Admin wants to control leds*/
            UART_RxString(glbl_u8AdminUserChoice);
            if('1' == glbl_u8AdminUserChoice[0])
            {
                /*User/Admin wants to control LED 1*/
                glbl_u8LEDChoice = HC05_LED_1_CHOICE;
                UART_TxString("1: LED 1 On\n");
                UART_TxString("2: LED 1 Off\n");
                glbl_u8CurrentScreen = HC05_LEDS_CONTROL;
            }
            else if('2' == glbl_u8AdminUserChoice[0])
            {
                /*User/Admin wants to control LED 2*/
                glbl_u8LEDChoice = HC05_LED_2_CHOICE;
                UART_TxString("1: LED 2 On\n");
                UART_TxString("2: LED 2 Off\n");
                glbl_u8CurrentScreen = HC05_LEDS_CONTROL;
            }
            else if('3' == glbl_u8AdminUserChoice[0])
            {
                /*User/Admin wants to control LED 3*/
                glbl_u8LEDChoice = HC05_LED_3_CHOICE;
                UART_TxString("1: LED 3 On\n");
                UART_TxString("2: LED 3 Off\n");
                glbl_u8CurrentScreen = HC05_LEDS_CONTROL;
            }
            else if('4' == glbl_u8AdminUserChoice[0])
            {
                /*User/Admin wants to control LED 4*/
                glbl_u8LEDChoice = HC05_LED_4_CHOICE;
                UART_TxString("1: LED 4 On\n");
                UART_TxString("2: LED 4 Off\n");
                glbl_u8CurrentScreen = HC05_LEDS_CONTROL;
            }
            else if('5' == glbl_u8AdminUserChoice[0])
            {
                /*User/Admin wants to control LED 5*/
                glbl_u8LEDChoice = HC05_LED_5_CHOICE;
                UART_TxString("1: LED 5 On\n");
                UART_TxString("2: LED 5 Off\n");
                glbl_u8CurrentScreen = HC05_LEDS_CONTROL;
            }
            else if('6' == glbl_u8AdminUserChoice[0])
            {
                /*User/Admin wants to control Dimming LED*/
                glbl_u8LEDChoice = HC05_DIMMING_LED_CHOICE;
                UART_TxString("Please Choose the brightness of LED\n");
                UART_TxString("1: 0%\n");
                UART_TxString("2: 20%\n");
                UART_TxString("3: 40%\n");
                UART_TxString("4: 60%\n");
                UART_TxString("5: 80%\n");
                UART_TxString("6: 100%\n");
                glbl_u8CurrentScreen = HC05_LEDS_CONTROL;
            }
            else
            {
                /*Admin/User has entered wrong input*/
                UART_TxString("Sorry, Wrong Input\n");
                HC05_AdminUserLEDChoice();
            }
            break;
        }
        case HC05_LEDS_CONTROL:
        {
            UART_RxString(glbl_u8AdminUserChoice);
            if(HC05_LED_1_CHOICE == glbl_u8LEDChoice)
            {
                if('1' == glbl_u8AdminUserChoice[0])
                {
                    /*Admin/User wants to turn on LED 1*/
                    LED_On(HC05_LED_1_PORT_ID, HC05_LED_1_PIN_ID);
                    UART_TxString("LED 1 Turned On Successfully\n");
                    HC05_AdminUserChoiceList();
                    glbl_u8CurrentScreen = HC05_SERVICES_SCREEN;
                }
                else if('2' == glbl_u8AdminUserChoice[0])
                {
                    /*Admin/User wants to turn off LED 1*/
                    LED_Off(HC05_LED_1_PORT_ID, HC05_LED_1_PIN_ID);
                    UART_TxString("LED 1 Turned Off Successfully\n");
                    HC05_AdminUserChoiceList();
                    glbl_u8CurrentScreen = HC05_SERVICES_SCREEN;
                }
                else
                {
                    /*Admin/User has entered wrong input*/
                    UART_TxString("Sorry, Wrong Input\n");
                    UART_TxString("1: LED 1 On\n");
                    UART_TxString("2: LED 1 Off\n");
                }
            }
            else if(HC05_LED_2_CHOICE == glbl_u8LEDChoice)
            {
                if('1' == glbl_u8AdminUserChoice[0])
                {
                    /*Admin/User wants to turn on LED 2*/
                    LED_On(HC05_LED_2_PORT_ID, HC05_LED_2_PIN_ID);
                    UART_TxString("LED 2 Turned On Successfully\n");
                    HC05_AdminUserChoiceList();
                    glbl_u8CurrentScreen = HC05_SERVICES_SCREEN;
                }
                else if('2' == glbl_u8AdminUserChoice[0])
                {
                    /*Admin/User wants to turn off LED 2*/
                    LED_Off(HC05_LED_2_PORT_ID, HC05_LED_2_PIN_ID);
                    UART_TxString("LED 2 Turned Off Successfully\n");
                    HC05_AdminUserChoiceList();
                    glbl_u8CurrentScreen = HC05_SERVICES_SCREEN;
                }
                else
                {
                    /*Admin/User has entered wrong input*/
                    UART_TxString("Sorry, Wrong Input\n");
                    UART_TxString("1: LED 2 On\n");
                    UART_TxString("2: LED 2 Off\n");
				}
            }
            else if(HC05_LED_3_CHOICE == glbl_u8LEDChoice)
            {
                if('1' == glbl_u8AdminUserChoice[0])
                {
                    /*Admin/User wants to turn on LED 3*/
                    LED_On(HC05_LED_3_PORT_ID, HC05_LED_3_PIN_ID);
                    UART_TxString("LED 3 Turned On Successfully\n");
                    HC05_AdminUserChoiceList();
                    glbl_u8CurrentScreen = HC05_SERVICES_SCREEN;
                }
                else if('2' == glbl_u8AdminUserChoice[0])
                {
                    /*Admin/User wants to turn off LED 3*/
                    LED_Off(HC05_LED_3_PORT_ID, HC05_LED_3_PIN_ID);
                    UART_TxString("LED 3 Turned Off Successfully\n");
                    HC05_AdminUserChoiceList();
                    glbl_u8CurrentScreen = HC05_SERVICES_SCREEN;
                }
                else
                {
                    /*Admin/User has entered wrong input*/
                    UART_TxString("Sorry, Wrong Input\n");
                    UART_TxString("1: LED 3 On\n");
                    UART_TxString("2: LED 3 Off\n");
                }
            }
            else if(HC05_LED_4_CHOICE == glbl_u8LEDChoice)
            {
                if('1' == glbl_u8AdminUserChoice[0])
                {
                    /*Admin/User wants to turn on LED 4*/
                    LED_On(HC05_LED_4_PORT_ID, HC05_LED_4_PIN_ID);
                    UART_TxString("LED 4 Turned On Successfully\n");
                    HC05_AdminUserChoiceList();
                    glbl_u8CurrentScreen = HC05_SERVICES_SCREEN;
                }
                else if('2' == glbl_u8AdminUserChoice[0])
                {
                    /*Admin/User wants to turn off LED 4*/
                    LED_Off(HC05_LED_4_PORT_ID, HC05_LED_4_PIN_ID);
                    UART_TxString("LED 4 Turned Off Successfully\n");
                    HC05_AdminUserChoiceList();
                    glbl_u8CurrentScreen = HC05_SERVICES_SCREEN;
                }
                else
                {
                    /*Admin/User has entered wrong input*/
                    UART_TxString("Sorry, Wrong Input\n");
                    UART_TxString("1: LED 4 On\n");
                    UART_TxString("2: LED 4 Off\n");
                }
            }
            else if(HC05_LED_5_CHOICE == glbl_u8LEDChoice)
            {
                if('1' == glbl_u8AdminUserChoice[0])
                {
                    /*Admin/User wants to turn on LED 5*/
                    LED_On(HC05_LED_5_PORT_ID, HC05_LED_5_PIN_ID);
                    UART_TxString("LED 5 Turned On Successfully\n");
                    HC05_AdminUserChoiceList();
                    glbl_u8CurrentScreen = HC05_SERVICES_SCREEN;
                }
                else if('2' == glbl_u8AdminUserChoice[0])
                {
                    /*Admin/User wants to turn off LED 5*/
                    LED_Off(HC05_LED_5_PORT_ID, HC05_LED_5_PIN_ID);
                    UART_TxString("LED 5 Turned Off Successfully\n");
                    HC05_AdminUserChoiceList();
                    glbl_u8CurrentScreen = HC05_SERVICES_SCREEN;
                }
                else
                {
                    /*Admin/User has entered wrong input*/
                    UART_TxString("Sorry, Wrong Input\n");
                    UART_TxString("1: LED 5 On\n");
                    UART_TxString("2: LED 5 Off\n");
                }
            }
            else if(HC05_DIMMING_LED_CHOICE == glbl_u8LEDChoice)
            {
                if('1' == glbl_u8AdminUserChoice[0])
                {
                    /*Admin/User wants the brigtness of dimming LED to be 0*/
                    TMR_Timer2Stop();
                    LED_Off(HC05_DIMMING_LED_PORT_ID, HC05_DIMMING_LED_PIN_ID);
					HC05_AdminUserChoiceList();
					glbl_u8CurrentScreen = HC05_SERVICES_SCREEN;
                    glbl_u8DimmingLEDStatus = HC05_DIMMING_LED_0;
                }
                else if('2' == glbl_u8AdminUserChoice[0])
                {
                    /*Admin/User wants the brigtness of dimming LED to be 20%*/
                    TMR_Timer2Stop();
                    TMR_Timer2Set_PWM_DutyCycle(20);
                    TMR_Timer2Start();
					HC05_AdminUserChoiceList();
					glbl_u8CurrentScreen = HC05_SERVICES_SCREEN;
                }
                else if('3' == glbl_u8AdminUserChoice[0])
                {
                    /*Admin/User wants the brigtness of dimming LED to be 40%*/
                    TMR_Timer2Stop();
                    TMR_Timer2Set_PWM_DutyCycle(40);
                    TMR_Timer2Start();
					HC05_AdminUserChoiceList();
					glbl_u8CurrentScreen = HC05_SERVICES_SCREEN;
                }
                else if('4' == glbl_u8AdminUserChoice[0])
                {
                    /*Admin/User wants the brigtness of dimming LED to be 60%*/
                    TMR_Timer2Stop();
                    TMR_Timer2Set_PWM_DutyCycle(60);
					TMR_Timer2Start();
                    HC05_AdminUserChoiceList();
					glbl_u8CurrentScreen = HC05_SERVICES_SCREEN;
                }
                else if('5' == glbl_u8AdminUserChoice[0])
                {
                    /*Admin/User wants the brigtness of dimming LED to be 80%*/
                    TMR_Timer2Stop();
                    TMR_Timer2Set_PWM_DutyCycle(80);
					TMR_Timer2Start();
                    HC05_AdminUserChoiceList();
					glbl_u8CurrentScreen = HC05_SERVICES_SCREEN;
                }
                else if('6' == glbl_u8AdminUserChoice[0])
                {
                    /*Admin/User wants the brigtness of dimming LED to be 100%*/
                    TMR_Timer2Stop();
                    LED_On(HC05_DIMMING_LED_PORT_ID, HC05_DIMMING_LED_PIN_ID);
                    HC05_AdminUserChoiceList();
					glbl_u8CurrentScreen = HC05_SERVICES_SCREEN;
                }
                else
                {
                    UART_TxString("Sorry, Wrong Input");
                    UART_TxString("Please Choose the brightness of LED\n");
                    UART_TxString("1: 0%\n");
                    UART_TxString("2: 20%\n");
                    UART_TxString("3: 40%\n");
                    UART_TxString("4: 60%\n");
                    UART_TxString("5: 80%\n");
                    UART_TxString("6: 100%\n");
                }
            }
            else
            {
                /*Do nothing*/
            }
            break;
        }
        case HC05_ADD_USER_USERNAME_SCREEN:
        {
            /*Admin wants to add new user*/
            /*First, we take the new user username from admin*/
            UART_RxString(glbl_u8AdminUserUsername);
            UART_TxString("Please enter the new user's password:\n");
            glbl_u8CurrentScreen = HC05_ADD_USER_PASSWORD_SCREEN;
            break;
        }
        case HC05_ADD_USER_PASSWORD_SCREEN:
        {
            /*Second, We take the new user password*/
            UART_RxString(glbl_u8AdminUserPassword);

            /*Before we add the new user, we have to check if the user already exists or not*/
            u8 Loc_u8UserExistCheck = HC05_UserNamePasswordExist();
            if(Loc_u8UserExistCheck == HC05_USER_NOT_EXIST)
            {
                /*Means that the user doesn't exist in the EEPROM and we are ready to add it*/
                HC05_AddNewUser();
            }
            else if(Loc_u8UserExistCheck == HC05_USER_EXIST)
            {
                /*Means that the user already exists in the EEPROM and as a result, the new user will not be added*/
            }
            else
            {
                /*Do nothing*/
            }
            HC05_AdminUserChoiceList();
            glbl_u8CurrentScreen = HC05_SERVICES_SCREEN;
            break;
        }
        case HC05_DELETE_USER_SCREEN:
        {
            /*Admin wants to delete a user*/
            /*We take the user to be deleted username*/
            UART_RxString(glbl_u8AdminUserUsername);
            /*And then delete it*/
            HC05_DeleteUser();
            glbl_u8CurrentScreen = HC05_SERVICES_SCREEN;
            break;
        }
        case HC05_LCD_KPD_SYS_REQUEST_SCREEN:
        {
            /*If User in the LCD/Keypad System wants to do something while admin is logged in, Admin must approve
            First 
            */
            UART_RxString(glbl_u8AdminUserChoice);
            if('1' == glbl_u8AdminUserChoice[0])
            {
                /*Means that the admin approves*/
                glbl_u8AdminApproval = ADMIN_APPROVE;
            }
            else if('2' == glbl_u8AdminUserChoice[0])
            {
                /*Means that the admin disapproves*/
                glbl_u8AdminApproval = ADMIN_REFUSE;
            }
            glbl_u8CurrentScreen = glbl_u8PreviousScreen;
            break;
        }
        default:
        {
            /*Do nothing*/
            break;
        }
    }
}

/********************************************************************************************************************/


/**
 * @brief: Function to show the running devices on LCD if the LCD-Keypad System is not used
 * 
 */
void HC05_ShowRunningDevices(void)
{
    u8 Loc_u8LEDStatus = 0;
    DIO_ReadOutputPinValue(HC05_LED_1_PORT_ID, HC05_LED_1_PIN_ID, &Loc_u8LEDStatus);
    if(Loc_u8LEDStatus == DIO_PIN_HIGH)
    {
        LCD_WriteString("LED 1: On");
    }
    else if(Loc_u8LEDStatus == DIO_PIN_LOW)
    {
        LCD_WriteString("LED 1: Off");
    }
    else
    {
        /*Do nothing*/
    }

    LCD_SetCursorPosition(LCD_SECOND_ROW, 0);
    
    DIO_ReadOutputPinValue(HC05_LED_2_PORT_ID, HC05_LED_2_PIN_ID, &Loc_u8LEDStatus);
    if(Loc_u8LEDStatus == DIO_PIN_HIGH)
    {
        LCD_WriteString("LED 2: On");
    }
    else if(Loc_u8LEDStatus == DIO_PIN_LOW)
    {
        LCD_WriteString("LED 2: Off");
    }
    else
    {
        /*Do nothing*/
    }

    _delay_ms(1000);
    LCD_ClearDisplay();

    DIO_ReadOutputPinValue(HC05_LED_3_PORT_ID, HC05_LED_3_PIN_ID, &Loc_u8LEDStatus);
    if(Loc_u8LEDStatus == DIO_PIN_HIGH)
    {
        LCD_WriteString("LED 3: On");
    }
    else if(Loc_u8LEDStatus == DIO_PIN_LOW)
    {
        LCD_WriteString("LED 3: Off");
    }
    else
    {
        /*Do nothing*/
    }

    LCD_SetCursorPosition(LCD_SECOND_ROW, 0);

    DIO_ReadOutputPinValue(HC05_LED_4_PORT_ID, HC05_LED_4_PIN_ID, &Loc_u8LEDStatus);
    if(Loc_u8LEDStatus == DIO_PIN_HIGH)
    {
        LCD_WriteString("LED 4: On");
    }
    else if(Loc_u8LEDStatus == DIO_PIN_LOW)
    {
        LCD_WriteString("LED 4: Off");
    }
    else
    {
        /*Do nothing*/
    }

    _delay_ms(1000);
    LCD_ClearDisplay();
    
    DIO_ReadOutputPinValue(HC05_LED_5_PORT_ID, HC05_LED_5_PIN_ID, &Loc_u8LEDStatus);
    if(Loc_u8LEDStatus == DIO_PIN_HIGH)
    {
        LCD_WriteString("LED 5: On");
    }
    else if(Loc_u8LEDStatus == DIO_PIN_LOW)
    {
       LCD_WriteString("LED 5: Off");
    }
    else
    {
        /*Do nothing*/
    }

    LCD_SetCursorPosition(LCD_SECOND_ROW, 0);

    switch(glbl_u8DimmingLEDStatus)
    {
        case HC05_DIMMING_LED_0:
        {
            LCD_WriteString("Dimming LED: 0");
            break;
        }
        case HC05_DIMMING_LED_20:
        {
            LCD_WriteString("Dimming LED: 20%");
            break;
        }
        case HC05_DIMMING_LED_40:
        {
            LCD_WriteString("Dimming LED: 40%");
            break;
        }
        case HC05_DIMMING_LED_60:
        {
            LCD_WriteString("Dimming LED: 60%");
            break;
        }
        case HC05_DIMMING_LED_80:
        {
            LCD_WriteString("Dimming LED: 80%");
            break;
        }
        case HC05_DIMMING_LED_100:
        {
            LCD_WriteString("Dimming LED:100%");
            break;
        }
        default:
        {
            /*Do nothing*/
            break;
        }
    }

    _delay_ms(1000);
    LCD_ClearDisplay();
    
    if(glbl_u8DoorStatus == DOOR_CLOSED)
    {
        LCD_WriteString("Door Closed");
    }
    else if(glbl_u8DoorStatus == DOOR_OPENED)
    {
        LCD_WriteString("Door Opened");
    }
    else
    {
        /*Do nothing*/
    }
    _delay_ms(1000);
    LCD_ClearDisplay();
}

/********************************************************************************************************************/

/**
 * @brief: Function to show if the admin agrees to an operation a user in LCD-Keypad System wants to do
 * 
 * @return u8: Approval or Refuse 
 */
u8 HC05_AdminApproval(void)
{
    switch (glbl_u8AdminApproval)
    {
    case ADMIN_APPROVE:
        {
            glbl_u8AdminApproval = ADMIN_NOT_REPLIED;
            return ADMIN_APPROVE;
            break;
        }
    case ADMIN_REFUSE:
        {
            glbl_u8AdminApproval = ADMIN_NOT_REPLIED;
            return ADMIN_REFUSE;
            break;
        }
    default:
        {
            return ADMIN_NOT_REPLIED;
            break;
        }
    }
}

/********************************************************************************************************************/

/**
 * @brief: Function to change the screen to admin response screen so that admin can choose to approve or disapprove
 * 
 */
void HC05_ScreenChangeToAdminResponse(void)
{
    glbl_u8PreviousScreen = glbl_u8CurrentScreen;
    glbl_u8CurrentScreen = HC05_LCD_KPD_SYS_REQUEST_SCREEN;
}

/********************************************************************************************************************/
