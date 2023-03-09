/*
 * USER_interface.h
 *
 * Created: 2/26/2023 3:11:28 PM
 *  Author: Medhat
 */ 


#ifndef USER_INTERFACE_H_
#define USER_INTERFACE_H_

void USER_PROGRAM_START(void);
u8 USER_LOGIN(void);
u8 USER_PROGRAM(void);
void USER_Control_Leds(void);
void USER_LOGOUT(void);
void USER_APP(void);
u8 USER_EXIST(void);

#endif /* USER_INTERFACE_H_ */