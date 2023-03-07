/**
 * @file DIO_Program.c
 * @author Ahmed Atia (atiaa6501@gmail.com)
 * 
 * @version 1.0
 * @date 2022-11-02
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ATMEGA32_REG.h"


#include "DIO_Interface.h"

/**
 * @brief: Function to set the direction of the desired bit
 * 
 * @param Copy_u8PortID: The ID of the port containing the pin
 * @param Copy_u8PinID: The ID of the pin
 * @param Copy_u8PinDirection: The direction of the pin (output or input)
 */
void DIO_SetPinDirection(u8 Copy_u8PortID, u8 Copy_u8PinID, u8 Copy_u8PinDirection)
{
	if (Copy_u8PortID >= DIO_PORTA && Copy_u8PortID <= DIO_PORTD)
	{
		if (Copy_u8PinID >= DIO_PIN0 && Copy_u8PinID <= DIO_PIN7)
		{
			switch(Copy_u8PortID)
			{
				case DIO_PORTA:
				{
					if(Copy_u8PinDirection == DIO_PIN_OUTPUT)
					{
						SET_BIT(DDRA, Copy_u8PinID);
					}
					else if(Copy_u8PinDirection == DIO_PIN_INPUT)
					{
						CLEAR_BIT(DDRA, Copy_u8PinID);
					}
					break;
				}
				case DIO_PORTB:
				{
					if(Copy_u8PinDirection == DIO_PIN_OUTPUT)
					{
						SET_BIT(DDRB, Copy_u8PinID);
					}
					else if(Copy_u8PinDirection == DIO_PIN_INPUT)
					{
						CLEAR_BIT(DDRB, Copy_u8PinID);
					}
					break;
				}
				case DIO_PORTC:
				{
					if(Copy_u8PinDirection == DIO_PIN_OUTPUT)
					{
						SET_BIT(DDRC, Copy_u8PinID);
					}
					else if(Copy_u8PinDirection == DIO_PIN_INPUT)
					{
						CLEAR_BIT(DDRC, Copy_u8PinID);
					}
					break;
				}
				case DIO_PORTD:
				{
					if(Copy_u8PinDirection == DIO_PIN_OUTPUT)
					{
						SET_BIT(DDRD, Copy_u8PinID);
					}
					else if(Copy_u8PinDirection == DIO_PIN_INPUT)
					{
						CLEAR_BIT(DDRD, Copy_u8PinID);
					}
					break;
				}
				default:
				{
					/*Do nothing*/
					break;
				}
			}
		}
		else
		{
			/*Do nothing*/
		}
	}
	else
	{
		/*Do nothing*/
	}
}
/**
 * @brief: Function to set the value of the pin
 * 
 * @param Copy_u8PortID: The ID of the port containing the pin
 * @param Copy_u8PinID: The ID of the desired pin
 * @param Copy_u8PinValue: The value of the pin (High or Low)
 */
void DIO_SetPinValue	(u8 Copy_u8PortID, u8 Copy_u8PinID, u8 Copy_u8PinValue)
{
	if (Copy_u8PortID >= DIO_PORTA && Copy_u8PortID <= DIO_PORTD)
	{
		if (Copy_u8PinID >= DIO_PIN0 && Copy_u8PinID <= DIO_PIN7)
		{
			switch(Copy_u8PortID)
			{
				case DIO_PORTA:
				{
					if(Copy_u8PinValue == DIO_PIN_HIGH)
					{
						SET_BIT(PORTA, Copy_u8PinID);
					}
					else if(Copy_u8PinValue == DIO_PIN_LOW)
					{
						CLEAR_BIT(PORTA, Copy_u8PinID);
					}
					break;
				}
				case DIO_PORTB:
				{
					if(Copy_u8PinValue == DIO_PIN_HIGH)
					{
						SET_BIT(PORTB, Copy_u8PinID);
					}
					else if(Copy_u8PinValue == DIO_PIN_LOW)
					{
						CLEAR_BIT(PORTB, Copy_u8PinID);
					}
					break;
				}
				case DIO_PORTC:
				{
					if(Copy_u8PinValue == DIO_PIN_HIGH)
					{
						SET_BIT(PORTC, Copy_u8PinID);
					}
					else if(Copy_u8PinValue == DIO_PIN_LOW)
					{
						CLEAR_BIT(PORTC, Copy_u8PinID);
					}
					break;
				}
				case DIO_PORTD:
				{
					if(Copy_u8PinValue == DIO_PIN_HIGH)
					{
						SET_BIT(PORTD, Copy_u8PinID);
					}
					else if(Copy_u8PinValue == DIO_PIN_LOW)
					{
						CLEAR_BIT(PORTD, Copy_u8PinID);
					}
					break;
				}
				default:
				{
					/*Do nothing*/
					break;
				}
			}
		}
		else
		{
			/*Do nothing*/
		}
	}
	else
	{
		/*Do nothing*/
	}
}
/**
 * @brief: Function to read the value on the input pin
 * 
 * @param Copy_u8PortID: The ID of the port containing the pin
 * @param Copy_u8PinID: The ID of the desired pin
 * @param Copy_u8PinValue: Pointer to save the value on the pin in
 */
void DIO_ReadPinValue		(u8 Copy_u8PortID, u8 Copy_u8PinID, u8* P_u8PinValue)
{
	if(P_u8PinValue != NULL)
	{
		if (Copy_u8PortID >= DIO_PORTA && Copy_u8PortID <= DIO_PORTD)
		{
			if (Copy_u8PinID >= DIO_PIN0 && Copy_u8PinID <= DIO_PIN7)
			{
				switch(Copy_u8PortID)
				{
					case DIO_PORTA:
					{
						if(DIO_PIN_HIGH == GET_BIT(PINA, Copy_u8PinID))
						{
							*P_u8PinValue = DIO_PIN_HIGH;
						}
						else if(DIO_PIN_LOW == GET_BIT(PINA, Copy_u8PinID))
						{
							*P_u8PinValue = DIO_PIN_LOW;
						}
						break;
					}
					case DIO_PORTB:
					{
						if(DIO_PIN_HIGH == GET_BIT(PINB, Copy_u8PinID))
						{
							*P_u8PinValue = DIO_PIN_HIGH;
						}
						else if(DIO_PIN_LOW == GET_BIT(PINB, Copy_u8PinID))
						{
							*P_u8PinValue = DIO_PIN_LOW;
						}
						break;
					}
					case DIO_PORTC:
					{
						if(DIO_PIN_HIGH == GET_BIT(PINC, Copy_u8PinID))
						{
							*P_u8PinValue = DIO_PIN_HIGH;
						}
						else if(DIO_PIN_LOW == GET_BIT(PINC, Copy_u8PinID))
						{
							*P_u8PinValue = DIO_PIN_LOW;
						}
						break;
					}
					case DIO_PORTD:
					{
						if(DIO_PIN_HIGH == GET_BIT(PIND, Copy_u8PinID))
						{
							*P_u8PinValue = DIO_PIN_HIGH;
						}
						else if(DIO_PIN_LOW == GET_BIT(PIND, Copy_u8PinID))
						{
							*P_u8PinValue = DIO_PIN_LOW;
						}
						break;
					}
					default:
					{
						/*Do nothing*/
						break;
					}
				}		
			}
			else
			{
				/*Do nothing*/
			}
		}
		else
		{
			/*Do nothing*/
		}
		
	}
	else
	{
		/*Do nothing*/
	}
}
/**
 * @brief: Function to read the value on the output pin
 * 
 * @param Copy_u8PortID: The ID of the port containing the pin
 * @param Copy_u8PinID: The ID of the desired pin
 * @param P_u8PinValue: Pointer to save the value on the pin in
 */
void DIO_ReadOutputPinValue	    (u8 Copy_u8PortID, u8 Copy_u8PinID, u8* P_u8PinValue)
{
	if(P_u8PinValue != NULL)
	{
		if (Copy_u8PortID >= DIO_PORTA && Copy_u8PortID <= DIO_PORTD)
		{
			if (Copy_u8PinID >= DIO_PIN0 && Copy_u8PinID <= DIO_PIN7)
			{
				switch(Copy_u8PortID)
				{
					case DIO_PORTA:
					{
						if(DIO_PIN_HIGH == GET_BIT(PORTA, Copy_u8PinID))
						{
							*P_u8PinValue = DIO_PIN_HIGH;
						}
						else if(DIO_PIN_LOW == GET_BIT(PORTA, Copy_u8PinID))
						{
							*P_u8PinValue = DIO_PIN_LOW;
						}
						break;
					}
					case DIO_PORTB:
					{
						if(DIO_PIN_HIGH == GET_BIT(PORTB, Copy_u8PinID))
						{
							*P_u8PinValue = DIO_PIN_HIGH;
						}
						else if(DIO_PIN_LOW == GET_BIT(PORTB, Copy_u8PinID))
						{
							*P_u8PinValue = DIO_PIN_LOW;
						}
						break;
					}
					case DIO_PORTC:
					{
						if(DIO_PIN_HIGH == GET_BIT(PORTC, Copy_u8PinID))
						{
							*P_u8PinValue = DIO_PIN_HIGH;
						}
						else if(DIO_PIN_LOW == GET_BIT(PORTC, Copy_u8PinID))
						{
							*P_u8PinValue = DIO_PIN_LOW;
						}
						break;
					}
					case DIO_PORTD:
					{
						if(DIO_PIN_HIGH == GET_BIT(PORTD, Copy_u8PinID))
						{
							*P_u8PinValue = DIO_PIN_HIGH;
						}
						else if(DIO_PIN_LOW == GET_BIT(PORTD, Copy_u8PinID))
						{
							*P_u8PinValue = DIO_PIN_LOW;
						}
						break;
					}
					default:
					{
						/*Do nothing*/
						break;
					}
				}		
			}
			else
			{
				/*Do nothing*/
			}
		}
		else
		{
			/*Do nothing*/
		}
		
	}
	else
	{
		/*Do nothing*/
	}
}
/**
 * @brief: Function to toggle the value on the output pin
 * 
 * @param Copy_u8PortID: The ID of the port containing the pin
 * @param Copy_u8PinID: The ID of the desired pin
 */
void DIO_TogglePinValue	(u8 Copy_u8PortID, u8 Copy_u8PinID)
{
	if(Copy_u8PortID >= DIO_PORTA && Copy_u8PortID <= DIO_PORTD)
	{
		if(Copy_u8PinID >= DIO_PIN0 && Copy_u8PinID <= DIO_PIN7)
		{
			switch (Copy_u8PortID)
			{
				case DIO_PORTA:
				{
					TOGGLE_BIT(PORTA, Copy_u8PinID);
					break;
				}
				case DIO_PORTB:
				{
					TOGGLE_BIT(PORTB, Copy_u8PinID);
					break;
				}
				case DIO_PORTC:
				{
					TOGGLE_BIT(PORTC, Copy_u8PinID);
					break;
				}
				case DIO_PORTD:
				{
					TOGGLE_BIT(PORTD, Copy_u8PinID);
					break;
				}
				default:
				{
					/*Do nothing*/
					break;
				}
			}		
		}
		else
		{
			/*Do nothing*/
		}
	}
	else
	{
		/*Do nothing*/
	}
}

/**
 * @brief: Function to write a value onto four consecutive output pins
 * 
 * @param Copy_u8PortID: The ID of the port containing the four pins
 * @param Copy_u8StartPinID: The ID of the starting pin
 * @param Copy_u8HalfPortValue: The value to be written
 */
void DIO_WriteHalfPort  (u8 Copy_u8PortID, u8 Copy_u8StartPinID, u8 Copy_u8HalfPortValue)
{
	if(Copy_u8PortID >= DIO_PORTA && Copy_u8PortID <= DIO_PORTD)
	{
		if(Copy_u8StartPinID >= DIO_PIN0 && Copy_u8StartPinID <= DIO_PIN4)
		{
			if(Copy_u8HalfPortValue >= 0 && Copy_u8HalfPortValue <= 15)
			{
				u8 index = 0;
				for(index = 0; index < 4; index++)
				{
					if(GET_BIT(Copy_u8HalfPortValue, index) == 1)
					{
						DIO_SetPinValue(Copy_u8PortID, (Copy_u8StartPinID + index), DIO_PIN_HIGH);
					}
					else
					{
						DIO_SetPinValue(Copy_u8PortID, (Copy_u8StartPinID + index), DIO_PIN_LOW);
					}
				}
			}
			else
			{
				/*Do nothing*/
			}
		}
		else
		{
			/*Do nothing*/
		}
	}
	else
	{
		/*Do nothing*/
	}
}

/**
 * @brief: Function to read the value of the output port
 *          (Port register)
 * @param Copy_u8PortID: The ID of the port to be read
 * @param P_u8PortValue: Pointer in which we save the desired value
 */
void DIO_ReadPortRegister   (u8 Copy_u8PortID, u8* P_u8PortValue)
{
	if(P_u8PortValue != NULL)
	{
		if(Copy_u8PortID >= DIO_PORTA && Copy_u8PortID <= DIO_PORTD)
		{
			switch(Copy_u8PortID)
			{
				case DIO_PORTA:
				{
					*P_u8PortValue = PORTA;
					break;
				}
				case DIO_PORTB:
				{
					*P_u8PortValue = PORTB;
					break;
				}
				case DIO_PORTC:
				{
					*P_u8PortValue = PORTC;
					break;
				}
				case DIO_PORTD:
				{
					*P_u8PortValue = PORTD;
					break;
				}
				default:
				{
					break;
				}
			}
		}
		else
		{
			/*Do nothing*/
		}
	}
	else
	{
		/*Do nothing*/
	}
}

/**
 * @brief: Function to read the value of the input port
 *          (Pin register)
 * @param Copy_u8PortID: The ID of the port to be read
 * @param P_u8PortValue: Pointer in which we save the desired value
 */
void DIO_ReadPinRegister    (u8 Copy_u8PortID, u8* P_u8PortValue)
{
	if(P_u8PortValue != NULL)
	{
		if(Copy_u8PortID >= DIO_PORTA && Copy_u8PortID <= DIO_PORTD)
		{
			switch(Copy_u8PortID)
			{
				case DIO_PORTA:
				{
					*P_u8PortValue = PINA;
					break;
				}
				case DIO_PORTB:
				{
					*P_u8PortValue = PINB;
					break;
				}
				case DIO_PORTC:
				{
					*P_u8PortValue = PINC;
					break;
				}
				case DIO_PORTD:
				{
					*P_u8PortValue = PIND;
					break;
				}
				default:
				{
					/*Do nothing*/
					break;
				}
			}
		}
		else
		{
			/*Do nothing*/
		}
	}
	else
	{
		/*Do nothing*/
	}
}
/**
 * @brief: Function to activate internal pull up resistor of the input pin
 * 
 * @param Copy_u8PortID: The ID of the Port containing the desired pin
 * @param Copy_u8PinID: The pin for its pull-up resistor to be activated
 */
void DIO_ActivatePullUp     (u8 Copy_u8PortID, u8 Copy_u8PinID)
{
	if(Copy_u8PortID >= DIO_PORTA && Copy_u8PortID <= DIO_PORTD)
	{
		if(Copy_u8PinID >= DIO_PIN0 && Copy_u8PinID <= DIO_PIN7)
		{
			switch(Copy_u8PortID)
			{
				case DIO_PORTA:
				{
					if(DIO_PIN_LOW == GET_BIT(DDRA, Copy_u8PinID))
					{
						SET_BIT(PORTA, Copy_u8PinID);
					}
					else
					{
						/*Do nothing*/
					}
					break;
				}
				case DIO_PORTB:
				{
					if(DIO_PIN_LOW == GET_BIT(DDRB, Copy_u8PinID))
					{
						SET_BIT(PORTB, Copy_u8PinID);
					}
					else
					{
						/*Do nothing*/
					}
					break;
				}
				case DIO_PORTC:
				{
					if(DIO_PIN_LOW == GET_BIT(DDRC, Copy_u8PinID))
					{
						SET_BIT(PORTC, Copy_u8PinID);
					}
					else
					{
						/*Do nothing*/
					}
					break;
				}
				case DIO_PORTD:
				{
					if(DIO_PIN_LOW == GET_BIT(DDRD, Copy_u8PinID))
					{
						SET_BIT(PORTD, Copy_u8PinID);
					}
					else
					{
						/*Do nothing*/
					}
					break;
				}
				default:
				{
					/*Do nothing*/
					break;
				}
			}
		}
		else
		{
			/*Do nothing*/
		}
	}
	else
	{
		/*Do nothing*/
	}
}

/**
 * @brief: Function for reading the value of the DDR register corresponding to the specified pin
 * 
 * @param Copy_u8PortID: The ID of the port containing the pin
 * @param Copy_u8PinID: The ID of the desired pin 
 * @param P_u8DDRPinValue: Pointer in which we save the desired value
 */
void DIO_ReadDDRPinValue    (u8 Copy_u8PortID, u8 Copy_u8PinID, u8* P_u8DDRPinValue)
{
	if(P_u8DDRPinValue != NULL)
	{
		if(Copy_u8PortID >= DIO_PORTA && Copy_u8PortID <= DIO_PORTD)
		{
			if(Copy_u8PinID >= DIO_PIN0 && Copy_u8PinID <= DIO_PIN7)
			{
				switch (Copy_u8PortID)
				{
					case DIO_PORTA:
					{
						if(DIO_PIN_OUTPUT == GET_BIT(DDRA, Copy_u8PinID))
						{
							*P_u8DDRPinValue = DIO_PIN_OUTPUT;
						}
						else if(DIO_PIN_INPUT == GET_BIT(DDRA, Copy_u8PinID))
						{
							*P_u8DDRPinValue = DIO_PIN_INPUT;
						}
						else
						{
							/*Do nothing*/
						}
						break;
					}
					case DIO_PORTB:
					{
						if(DIO_PIN_OUTPUT == GET_BIT(DDRB, Copy_u8PinID))
						{
							*P_u8DDRPinValue = DIO_PIN_OUTPUT;
						}
						else if(DIO_PIN_INPUT == GET_BIT(DDRB, Copy_u8PinID))
						{
							*P_u8DDRPinValue = DIO_PIN_INPUT;
						}
						else
						{
							/*Do nothing*/
						}
						break;
					}
					case DIO_PORTC:
					{
						if(DIO_PIN_OUTPUT == GET_BIT(DDRC, Copy_u8PinID))
						{
							*P_u8DDRPinValue = DIO_PIN_OUTPUT;
						}
						else if(DIO_PIN_INPUT == GET_BIT(DDRC, Copy_u8PinID))
						{
							*P_u8DDRPinValue = DIO_PIN_INPUT;
						}
						else
						{
							/*Do nothing*/
						}
						break;
					}
					case DIO_PORTD:
					{
						if(DIO_PIN_OUTPUT == GET_BIT(DDRD, Copy_u8PinID))
						{
							*P_u8DDRPinValue = DIO_PIN_OUTPUT;
						}
						else if(DIO_PIN_INPUT == GET_BIT(DDRD, Copy_u8PinID))
						{
							*P_u8DDRPinValue = DIO_PIN_INPUT;
						}
						else
						{
							/*Do nothing*/
						}
						break;
					}
					default:
					{
						/*Do nothing*/
						break;
					}
				}
			}
			else
			{
				/*Do nothing*/
			}
		}
		else
		{
			/*Do nothing*/
		}
	}
	else
	{
		/*Do nothing*/
	}
}
/**
 * @brief: Function to read the value of the direction register of the specified port
 *          (DDR register)
 * @param Copy_u8PortID: The ID of the port to be read
 * @param P_u8DDRValue: Pointer in which we save the desired value
 */
void DIO_ReadDDRRegister    (u8 Copy_u8PortID, u8* P_u8DDRValue)
{
	if(P_u8DDRValue != NULL)
	{
		if(Copy_u8PortID >= DIO_PORTA && Copy_u8PortID <= DIO_PORTD)
		{
			switch(Copy_u8PortID)
			{
				case DIO_PORTA:
				{
					*P_u8DDRValue = DDRA;
					break;
				}
				case DIO_PORTB:
				{
					*P_u8DDRValue = DDRB;
					break;
				}
				case DIO_PORTC:
				{
					*P_u8DDRValue = DDRC;
					break;
				}
				case DIO_PORTD:
				{
					*P_u8DDRValue = DDRD;
					break;
				}
				default:
				{
					/*Do nothing*/
					break;
				}
			}
		}
		else
		{
			/*Do nothing*/
		}
	}
}