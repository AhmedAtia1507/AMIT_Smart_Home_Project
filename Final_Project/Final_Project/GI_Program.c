/**
 * @file GIE_Program.c
 * @author Ahmed Atia (atiaa6501@gmail.com)
 * 
 * @version 1.0
 * @date 2022-11-12
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "ATMEGA32_REG.h"
#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include "GI_Interface.h"

/**
 * @brief: Function to enable the global interrupt
 * 
 */
void GI_Enable(void)
{
    SET_BIT(SREG, 7);
}
/**
 * @brief: Function to disable the global interrupt
 * 
 */
void GI_Disable(void)
{
    CLEAR_BIT(SREG, 7);
}