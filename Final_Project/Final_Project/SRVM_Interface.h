/**
 * @file SRVM_Interface.h
 * @author Ahmed Atia (atiaa6501@gmail.com)
 * 
 * @version 1.0
 * @date 2023-03-04
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef SRVM_INTERFACE_H_
#define SRVM_INTERFACE_H_

/**
 * @brief: Function to initialize the Servo motor Peripheral
 * 
 */
void SRVM_Init(void);

#define SRVM_ANGLE_POSITIVE                     1
#define SRVM_ANGLE_NEGATIVE                     2
/**
 * @brief: Function to set the angle of the servo motor
 * 
 * @param Copy_u8RotationAngleSign: Sign of angle of servo motor 
 * @param Copy_u8RotationAngle: : Angle of Servo motor 
 */
void SRVM_SetRotationAngle(u8 Copy_u8RotationAngleSign,u8 Copy_u8RotationAngle);
#endif /*SRVM_INTERFACE_H_*/