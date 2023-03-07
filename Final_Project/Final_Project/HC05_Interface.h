/**
 * @file HC05_Interface.h
 * @author Ahmed Atia (atiaa6501@gmail.com)
 * 
 * @version 1.0
 * @date 2023-02-26
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef HC05_INTERFACE_H_
#define HC05_INTERFACE_H_

#define HC05_ADMIN_SAVED_STATUS_MEM_ADDRESS		80
#define ADMIN_LOGGED_ON							7
#define ADMIN_MODE_OFF						    0
#define ADMIN_MODE_ON                           1

#define USER_MODE_ON                            1
#define USER_MODE_OFF                           0
#define USER_LOGGED_ON                          7
/**********Interface Screens************/
#define HC05_WELCOME_SCREEN                     1
#define HC05_LOGIN_USERNAME_SCREEN              2
#define HC05_LOGIN_PASSWORD_SCREEN              3
#define HC05_SERVICES_SCREEN                    4
#define HC05_LEDS_CHOICE                        5
#define HC05_LEDS_CONTROL                       6
#define HC05_DOOR_CONTROL                       8
#define HC05_ADD_USER_USERNAME_SCREEN           9
#define HC05_ADD_USER_PASSWORD_SCREEN           10
#define HC05_DELETE_USER_SCREEN                 11
#define HC05_LOG_OUT_SCREEN                     12
#define HC05_LCD_KPD_SYS_REQUEST_SCREEN         13



#define HC05_USERNAME_PASSOWRD_CORRECT          1
#define HC05_USERNAME_PASSOWRD_INCORRECT        2

#define HC05_USER_EXIST                         1
#define HC05_USER_NOT_EXIST                     2


#define DOOR_CLOSED                             0
#define DOOR_OPENED                             1

#define HC05_LED_1_CHOICE                       1
#define HC05_LED_2_CHOICE                       2
#define HC05_LED_3_CHOICE                       3
#define HC05_LED_4_CHOICE                       4
#define HC05_LED_5_CHOICE                       5
#define HC05_DIMMING_LED_CHOICE                 6


#define HC05_DIMMING_LED_0                      0
#define HC05_DIMMING_LED_20                     1
#define HC05_DIMMING_LED_40                     2
#define HC05_DIMMING_LED_60                     3
#define HC05_DIMMING_LED_80                     4
#define HC05_DIMMING_LED_100                    5
/**
 * @brief: Function to send a welcome message to the user/admin
 * 
 */
void HC05_WelcomeMessage(void);
/**
 * @brief: Function to set the admin username and password for the first time
 * 
 */
void HC05_AdminUsernamePasswordSaver(void);
/**
 * @brief: Function to check whether the admin is logged on or not
 * 
 * @return u8: Status of the Admin Login
 */
u8 HC05_AdminLoginCheck(void);
/**
 * @brief: Function to organize the operation of user/admin
 * 
 */
void HC05_AdminUserInterface(void);
/**
 * @brief: Function to check if the password is correct or not
 * 
 * @return u8: The result of the check
 */
u8 HC05_UsernamePasswordCheck(void);
/**
 * @brief: Function to show the running devices on LCD if the LCD-Keypad System is not used
 * 
 */
void HC05_ShowRunningDevices(void);

#define ADMIN_APPROVE               1
#define ADMIN_REFUSE                2
#define ADMIN_NOT_REPLIED           3
/**
 * @brief: Function to show if the admin agrees to an operation a user in LCD-Keypad System wants to do
 * 
 * @return u8: Approval or Refuse 
 */
u8 HC05_AdminApproval(void);
void HC05_ScreenChangeToAdminResponse(void);
#endif /*HC05_INTERFACE_H_*/