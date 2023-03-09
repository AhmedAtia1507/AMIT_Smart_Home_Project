/**
 * @file DIO_Interface.h
 * @author Ahmed Atia (atiaa6501@gmail.com)
 * 
 * @version 1.0
 * @date 2022-11-02
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_

#define DIO_PORTA			0
#define DIO_PORTB			1
#define DIO_PORTC			2
#define DIO_PORTD			3

#define DIO_PIN_INPUT		0
#define DIO_PIN_OUTPUT		1

#define DIO_PIN_LOW			0
#define DIO_PIN_HIGH		1 

#define DIO_PIN0			0
#define DIO_PIN1			1
#define DIO_PIN2			2
#define DIO_PIN3			3
#define DIO_PIN4			4
#define DIO_PIN5			5
#define DIO_PIN6			6
#define DIO_PIN7			7


/**
 * @brief: Function to set the direction of the desired bit
 * 
 * @param Copy_u8PortID: The ID of the port containing the pin
 * @param Copy_u8PinID: The ID of the pin
 * @param Copy_u8PinDirection: The direction of the pin (output or input)
 */
void DIO_SetPinDirection    (u8 Copy_u8PortID, u8 Copy_u8PinID, u8 Copy_u8PinDirection);
/**
 * @brief: Function to set the value of the pin
 * 
 * @param Copy_u8PortID: The ID of the port containing the pin
 * @param Copy_u8PinID: The ID of the desired pin
 * @param Copy_u8PinValue: The value of the pin (High or Low)
 */
void DIO_SetPinValue	    (u8 Copy_u8PortID, u8 Copy_u8PinID, u8 Copy_u8PinValue);
/**
 * @brief: Function to read the value on the input pin
 * 
 * @param Copy_u8PortID: The ID of the port containing the pin
 * @param Copy_u8PinID: The ID of the desired pin
 * @param P_u8PinValue: Pointer to save the value on the pin in
 */
void DIO_ReadPinValue	    (u8 Copy_u8PortID, u8 Copy_u8PinID, u8* P_u8PinValue);
/**
 * @brief: Function to read the value on the output pin
 * 
 * @param Copy_u8PortID: The ID of the port containing the pin
 * @param Copy_u8PinID: The ID of the desired pin
 * @param P_u8PinValue: Pointer to save the value on the pin in
 */
void DIO_ReadOutputPinValue	    (u8 Copy_u8PortID, u8 Copy_u8PinID, u8* P_u8PinValue);
/**
 * @brief: Function to toggle the value on the output pin
 * 
 * @param Copy_u8PortID: The ID of the port containing the pin
 * @param Copy_u8PinID: The ID of the desired pin
 */
void DIO_TogglePinValue	    (u8 Copy_u8PortID, u8 Copy_u8PinID);
/**
 * @brief: Function to write a value onto four consecutive output pins
 * 
 * @param Copy_u8PortID: The ID of the port containing the four pins
 * @param Copy_u8StartPinID: The ID of the starting pin
 * @param Copy_u8HalfPortValue: The value to be written
 */
void DIO_WriteHalfPort      (u8 Copy_u8PortID, u8 Copy_u8StartPinID, u8 Copy_u8HalfPortValue);
/**
 * @brief: Function to read the value of the output port
 *          (Port register)
 * @param Copy_u8PortID: The ID of the port to be read
 * @param P_u8PortValue: Pointer in which we save the desired value
 */
void DIO_ReadPortRegister   (u8 Copy_u8PortID, u8* P_u8PortValue);
/**
 * @brief: Function to read the value of the input port
 *          (Pin register)
 * @param Copy_u8PortID: The ID of the port to be read
 * @param P_u8PortValue: Pointer in which we save the desired value
 */
void DIO_ReadPinRegister    (u8 Copy_u8PortID, u8* P_u8PortValue);
/**
 * @brief: Function for reading the value of the DDR register corresponding to the specified pin
 * 
 * @param Copy_u8PortID: The ID of the port containing the pin
 * @param Copy_u8PinID: The ID of the desired pin 
 * @param P_u8DDRPinValue: Pointer in which we save the desired value
 */
void DIO_ReadDDRPinValue    (u8 Copy_u8PortID, u8 Copy_u8PinID, u8* P_u8DDRPinValue);
/**
 * @brief: Function to read the value of the direction register of the specified port
 *          (DDR register)
 * @param Copy_u8PortID: The ID of the port to be read
 * @param P_u8DDRValue: Pointer in which we save the desired value
 */
void DIO_ReadDDRRegister    (u8 Copy_u8PortID, u8* P_u8DDRValue);
/**
 * @brief: Function to activate internal pull up resistor of the input pin
 * 
 * @param Copy_u8PortID: The ID of the Port containing the desired pin
 * @param Copy_u8PinID: The pin for its pull-up resistor to be activated
 */
void DIO_ActivatePullUp     (u8 Copy_u8PortID, u8 Copy_u8PinID);
#endif /* DIO_INTERFACE_H_ */