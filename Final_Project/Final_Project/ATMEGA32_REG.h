/**
 * @file ATMEGA32_REG.h
 * @author Ahmed Atia (atiaa6501@gmail.com)
 * 
 * @version 1.0
 * @date 2022-11-02
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef ATMEGA32_REG_H_
#define ATMEGA32_REG_H_

#include "STD_TYPES.h"   

/****************************DIO Registers****************************/
/*PORT: Output register memory*/ /*PIN: Input Register memory*/ /*DDR: Direction register memory*/
/*PORT A Registers*/
#define PORTA               (*((volatile u8*)0x3B))
#define PINA                (*((volatile u8*)0x39))
#define DDRA                (*((volatile u8*)0x3A))

/*PORT B Registers*/
#define PORTB               (*((volatile u8*)0x38))
#define PINB                (*((volatile u8*)0x36))
#define DDRB                (*((volatile u8*)0x37))

/*PORT C Registers*/
#define PORTC               (*((volatile u8*)0x35))
#define PINC                (*((volatile u8*)0x33))
#define DDRC                (*((volatile u8*)0x34))

/*PORT D Registers*/
#define PORTD               (*((volatile u8*)0x32))
#define PIND                (*((volatile u8*)0x30))
#define DDRD                (*((volatile u8*)0x31))

/****************************External Interrupt Registers****************************/
//MCU Control Register
#define MCUCR               (*((volatile u8*)0x55))
//MCU Control & Status Register
#define MCUCSR              (*((volatile u8*)0x54))
//General Interrupt Control Register
#define GICR                (*((volatile u8*)0x5B))
//General Interrupt Flag Register
#define GIFR                (*((volatile u8*)0x5A))
//Status Register
#define SREG                (*((volatile u8*)0x5F))

/********************************ADC Registers********************************/
//ADC Multiplexer Selection Register
#define ADMUX               (*((volatile u8*)0x27))
//ADC Control and Status Register A
#define ADCSRA              (*((volatile u8*)0x26))
//ADC Data Register low
#define ADCL                (*((volatile u8*)0x24))
//ADC Data Register High
#define ADCH                (*((volatile u8*)0x25))
//ADC Data Register
#define ADC_u16             (*((volatile u16*)0x24))
//Special FunctionIO Register
#define SFIOR               (*((volatile u8*)0x50))

/********************************Timers Registers********************************/
//Timer/Counter Interrupt Mask Register
#define TIMSK               (*((volatile u8*)0x59))
//Timer/Counter Interrupt Flag Register
#define TIFR                (*((volatile u8*)0x58))

/********************Timer0 Registers********************/
//Timer/Counter Control Register
#define TCCR0               (*((volatile u8*)0x53))
//Timer/Counter Register
#define TCNT0               (*((volatile u8*)0x52))
//Output Compare Register
#define OCR0                (*((volatile u8*)0x5C))

/********************Timer1 Registers********************/
//Timer/Counter1 Control Register A
#define TCCR1A              (*((volatile u8*)0x4F))
//Timer/Counter1 Control Register B
#define TCCR1B              (*((volatile u8*)0x4E))
//Timer/Counter1 Register
#define TCNT1_u16           (*((volatile u16*)0x4C))
//Output Compare Register 1 A
#define OCR1A_u16           (*((volatile u16*)0x4A))
//Output Compare Register 1 B
#define OCR1B_u16           (*((volatile u16*)0x48))
//Input Capture Register 1
#define ICR1_u16            (*((volatile u16*)0x46))

/********************Timer2 Registers********************/
/*Timer/Counter2 Control Register*/
#define TCCR2               (*((volatile u8*)0x45))
/*Timer/Counter2 Register*/
#define TCNT2               (*((volatile u8*)0x44))
/*Output Compare Register 2*/
#define OCR2                (*((volatile u8*)0x43))
/********************Watchdog timer Registers********************/
/*Watchdog Timer Control Register*/
#define WDTCR               (*((volatile u8*)0x41))

/********************************UART Registers********************************/
/*UART I/O Data Register*/
#define UDR                 (*((volatile u8*)0x2C))
/*UART Control and Status Register A*/
#define UCSRA               (*((volatile u8*)0x2B))
/*UART Control and Status Register B*/
#define UCSRB               (*((volatile u8*)0x2A))
/*UART Control and Status Register C*/
#define UCSRC               (*((volatile u8*)0x40))
/*UART Baud Rate Register Low*/
#define UBRRL               (*((volatile u8*)0x29))
/*USART Baud Rate Registers High*/
#define UBRRH               (*((volatile u8*)0x40))

/********************************SPI Registers*********************************/
/*SPI Control Register*/
#define SPCR                (*((volatile u8*)0x2D))
/*SPI Status Register*/
#define SPSR                (*((volatile u8*)0x2E))
/*SPI Data Register*/
#define SPDR                (*((volatile u8*)0x2F))

/********************************TWI Registers********************************/
/*TWI Bit Rate Register*/
#define TWBR                (*((volatile u8*)0x20))
/*TWI Control Register*/
#define TWCR                (*((volatile u8*)0x56))
/*TWI Status Register*/
#define TWSR                (*((volatile u8*)0x21))
/*TWI Data Register*/
#define TWDR                (*((volatile u8*)0x23))
/*TWI (Slave) Address Register*/
#define TWAR                (*((volatile u8*)0x22))

/**************************Internal EEPROM Registers**************************/
/*EEPROM Address Register High*/
#define EEARH               (*((volatile u8*)0x3F))
/*EEPROM Address Register Low*/
#define EEARL               (*((volatile u8*)0x3E))
/*EEPROM Address Register*/
#define EEAR_u16            (*((volatile u16*)0x3E))
/*EEPROM Data Register*/
#define EEDR                (*((volatile u8*)0x3D))
/*EEPROM Control Register*/
#define EECR                (*((volatile u8*)0x3C))
#endif /*ATMEGA32_REG_H_*/