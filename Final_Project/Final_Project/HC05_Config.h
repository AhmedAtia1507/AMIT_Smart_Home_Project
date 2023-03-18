/**
 * @file HC05_Config.h
 * @author Ahmed Atia (atiaa6501@gmail.com)
 * 
 * @version 1.0
 * @date 2023-02-26
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef HC05_CONFIG_H_
#define HC05_CONFIG_H_

#define HC05_NO_USERS_MEM_ADDRESS           10
#define HC05_ADMIN_MEM_ADDRESS              50
#define HC05_USERNAME_SIZE                  1
#define HC05_PASSWD_SIZE                    3

#define HC05_ADMIN_USERNAME                 '2'
static u8 HC05_ADMIN_PASSWRD[3] =           {'1','2','3'};

#define HC05_LED_1_PORT_ID                  DIO_PORTC
#define HC05_LED_1_PIN_ID                   DIO_PIN2

#define HC05_LED_2_PORT_ID                  DIO_PORTC
#define HC05_LED_2_PIN_ID                   DIO_PIN7

#define HC05_DIMMING_LED_PORT_ID            DIO_PORTD
#define HC05_DIMMING_LED_PIN_ID             DIO_PIN7
#endif /*HC05_CONFIG_H_*/
