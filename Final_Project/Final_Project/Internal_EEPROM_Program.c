/**
 * @file Internal_EEPROM_Program.c
 * @author Ahmed Atia (atiaa6501@gmail.com)
 * 
 * @version 1.0
 * @date 2023-02-28
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "ATMEGA32_REG.h"
#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include "Internal_EEPROM_Interface.h"
#include "Internal_EEPROM_Private.h"

/**
 * @brief: Function to write a data byte into the designated adress in the EEPROM
 * 
 * @param Copy_u16ByteAddress: The EEPROM Byte Address in which the data byte will be stored
 * @param Copy_u8DataByte: The Data byte to be stored
 */
void Internal_EEPROM_WriteByte(u16 Copy_u16ByteAddress, u8 Copy_u8DataByte)
{
    if((Copy_u16ByteAddress >= 0) && (Copy_u16ByteAddress <= INTERNAL_EEPROM_MAX_ADDRESS))
    {
        /*Waiting for the previous write to be completed*/
        while(1 == GET_BIT(EECR, EEWE));

        /*Writing EEPROM Address in which we want to write the byte*/
        EEAR_u16 = Copy_u16ByteAddress;

        /*Writing the byte which we want to write*/
        EEDR = Copy_u8DataByte;
        
        /*Setting EEMWE Bit in EECR Register to allow me to write in EEPROM*/
        /*By setting EEWE Bit in the EECR register*/
        EECR |= (1 << EEMWE);
		EECR |= (1 << EEWE); 
    }
    else
    {
        /*Do nothing*/
    }
}
/**
 * @brief: Function to read a data byte from the designated adress in the EEPROM
 * 
 * @param Copy_u16ByteAddress: The EEPROM Byte Address from which the data byte will be read
 * @param P_u8DataByte: Pointer to store the data byte read from EEPROM 
 */
void Internal_EEPROM_ReadByte(u16 Copy_u16ByteAddress, u8* P_u8DataByte)
{
    if(P_u8DataByte != NULL)
    {
        if((Copy_u16ByteAddress >= 0) && (Copy_u16ByteAddress <= INTERNAL_EEPROM_MAX_ADDRESS))
        {
            /*As we can't read from EEPROM while writing into it*/
            /*We have to wait for the previous write to be completed*/
            while(1 == GET_BIT(EECR, EEWE));

            /*Writing EEPROM Address in which we want to read the byte stored*/
            EEAR_u16 = Copy_u16ByteAddress;
            
            /*Setting this bit will start the EEPROM Read operation*/
            EECR |= (1 << EERE);

            *P_u8DataByte = EEDR;
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