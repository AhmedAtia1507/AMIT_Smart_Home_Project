/**
 * @file Internal_EEPROM_Interface.h
 * @author Ahmed Atia (atiaa6501@gmail.com)
 * 
 * @version 1.0
 * @date 2023-02-28
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef INTERNAL_EEPROM_INTERFACE_H_
#define INTERNAL_EEPROM_INTERFACE_H_
/**
 * @brief: Function to write a data byte into the designated address in the EEPROM
 * 
 * @param Copy_u16ByteAddress: The EEPROM Byte Address in which the data byte will be stored
 * @param Copy_u8DataByte: The Data byte to be stored
 */
void Internal_EEPROM_WriteByte(u16 Copy_u16ByteAddress, u8 Copy_u8DataByte);
/**
 * @brief: Function to read a data byte from the designated address in the EEPROM
 * 
 * @param Copy_u16ByteAddress: The EEPROM Byte Address from which the data byte will be read
 * @param P_u8DataByte: Pointer to store the data byte read from EEPROM 
 */
void Internal_EEPROM_ReadByte(u16 Copy_u16ByteAddress, u8* P_u8DataByte);
#endif /*INTERNAL_EEPROM_INTERFACE_H_*/