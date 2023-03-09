/**
 * @file BIT_MATH.h
 * @author Ahmed Atia (atiaa6501@gmail.com)
 * 
 * @version 1.0
 * @date 2022-11-02
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef BIT_MATH_H_
#define BIT_MATH_H_

#define SET_BIT(REG, BIT)           (REG |= (1 << BIT))
#define CLEAR_BIT(REG,BIT)          (REG &= ~(1 << BIT))
#define GET_BIT(REG, BIT)           ((REG >> BIT) & 1)
#define TOGGLE_BIT(REG, BIT)        (REG ^= (1 << BIT))
#endif /*BIT_MATH_H_*/