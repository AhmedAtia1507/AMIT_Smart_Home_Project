/**
 * @file HC05_Private.h
 * @author Ahmed Atia (atiaa6501@gmail.com)
 * 
 * @version 1.0
 * @date 2023-02-26
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef HC05_PRIVATE_H_
#define HC05_PRIVATE_H_
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
#define HC05_DIMMING_LED_CHOICE                 6


#define HC05_DIMMING_LED_0                      0
#define HC05_DIMMING_LED_20                     1
#define HC05_DIMMING_LED_40                     2
#define HC05_DIMMING_LED_60                     3
#define HC05_DIMMING_LED_80                     4
#define HC05_DIMMING_LED_100                    5

#define HC05_NEW_LINE_CHAR                      13
#endif /*HC05_PRIVATE_H_*/