/******************************************************************************
 *
 * File Name: bit_math.h
 *
 * Description: Header file for Bit Math Operations
 *
 * Author: Safia Hany
 *
 *******************************************************************************/

#ifndef COMM_BIT_MATH_H_
#define COMM_BIT_MATH_H_


// Set bit BIT in REG
#define SET_BIT(REG,BIT)    REG|=(1<<BIT)
/* Clear a certain bit in any register */
#define CLEAR_BIT(REG,BIT) (REG&=(~(1<<BIT)))
// Toggle bit BIT in REG
#define TGL_BIT(REG,BIT)    REG^=(1<<BIT)
// Get bit BIT in REG
#define GET_BIT(REG,BIT)     ((REG>>BIT)&1)
// Set high nibble in REG
#define SET_HIGH_NIB(REG)    REG |= 0xF0
// Clear high nibble in REG
#define CLR_HIGH_NIB(REG)    REG &= (~ 0xF0)
// Get high nibble in REG
#define GET_HIGH_NIB(REG)    ((REG & 0xF0)>>4)
// Toggle high nibble in REG
#define TGL_HIGH_NIB(REG)     REG ^=0xF0
// Set low nibble in REG
#define SET_LOW_NIB(REG)     REG |= 0x0F
// Clear low nibble in REG
#define CLR_LOW_NIB(REG)    REG &= (~ 0x0F)
// Get low nibble in REG
#define GET_LOW_NIB(REG)    REG & 0xF0
// Toggle low nibble in REG
#define TGL_LOW_NIB(REG)    REG ^=0x0F

// Assign VALUE to REG
#define ASSIGN_REG(REG,VALUE)      REG = VALUE
// Assign VALUE to high nibble REG
#define ASSIGN_HIGH_NIB(REG,VALUE)    REG|=(VALUE<<4)
// Assign VALUE to low nibble REG
#define ASSIGN_LOW_NIB(REG,VALUE)     REG|=(VALUE&0x0F)
// Right shift by NO in REG
#define RSHFT_REG(REG, NO)            REG|=>>NO
// Left shift by NO in REG
#define LSHFT_REG(REG, NO)          REG|=<<NO
// Circular right shift by NO in REG
#define CRSHFT_REG(REG, NO)        REG<<(8-NO)|REG>>NO
// Circular left shift by NO in REG
#define CLSHFT_REG(REG,NO)        REG>>(8-NO)|REG<<NO

#endif /* COMM_BIT_MATH_H_ */
