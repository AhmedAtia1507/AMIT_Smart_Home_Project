/**
 * @file LED_Interface.h
 * @author Ahmed Atia (atiaa6501@gmail.com)
 * 
 * @version 1.0
 * @date 2023-02-02
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef LED_INTERFACE_H_
#define LED_INTERFACE_H_

/**
 * @brief: Function for turning on a LED
 * 
 * @param Copy_u8PortID: Port ID to which the LED is connected
 * @param Copy_u8PinID: Pin ID to which the LED is connected
 */
void LED_On(u8 Copy_u8PortID, u8 Copy_u8PinID);
/**
 * @brief: Function for turning off a LED 
 * 
 * @param Copy_u8PortID:  Port ID to which the LED is connected 
 * @param Copy_u8PinID: Pin ID to which the LED is connected
 */
void LED_Off(u8 Copy_u8PortID, u8 Copy_u8PinID);
/**
 * @brief: Function for toggling a LED
 * 
 * @param Copy_u8PortID: Port ID to which the LED is connected 
 * @param Copy_u8PinID: Pin ID to which the LED is connected
 */
void LED_Toggle(u8 Copy_u8PortID, u8 Copy_u8PinID);
#endif /*LED_INTERFACE_H_*/