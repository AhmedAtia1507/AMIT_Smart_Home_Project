/**
 * @file SRVM_Config.h
 * @author Ahmed Atia (atiaa6501@gmail.com)
 * 
 * @version 1.0
 * @date 2023-03-04
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef SRVM_CONFIG_H_
#define SRVM_CONFIG_H_

/*
        Servo motor pin connection
1) TMR_TIMER1_OCR1A -----> OC PIN D5
2) TMR_TIMER1_OCR1B -----> OC PIN D4
*/
#define SRVM_OC_CONNECTED      TMR_TIMER1_OCR1A
#endif /*SRVM_CONFIG_H_*/