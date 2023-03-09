/**
 * @file Internal_EEPROM_Private.h
 * @author Ahmed Atia (atiaa6501@gmail.com)
 * 
 * @version 1.0
 * @date 2023-02-28
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef INTERNAL_EEPROM_PRIVATE_H_
#define INTERNAL_EEPROM_PRIVATE_H_

#define INTERNAL_EEPROM_MAX_ADDRESS         1023

/**************EECR Register Bits*******************/
/*EEPROM Read Enable*/
#define EERE                                0
/*EEPROM Write Enable*/
#define EEWE                                1
/*EEPROM Master Write Enable*/
#define EEMWE                               2
/*EEPROM Ready Interrupt Enable*/
#define EERIE                               3
#endif /*INTERNAL_EEPROM_PRIVATE_H_*/