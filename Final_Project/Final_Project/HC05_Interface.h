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
/**
 * @brief: Function to change the screen to admin response screen so that admin can choose to approve or disapprove
 * 
 */
void HC05_ScreenChangeToAdminResponse(void);
/**
 * @brief: Function to reset the system after 3 wrong login attempts
 * 
 */
void HC05_SystemReset(void);
#endif /*HC05_INTERFACE_H_*/
