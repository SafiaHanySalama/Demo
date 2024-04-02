/******************************************************************************
 *
 * Module: 
 *
 * File Name: nvic.c
 *
 * Description: 
 *
 * Author: Safia Hany
 * 
 * Date:  Mar 15, 2024
 ******************************************************************************/
#include "mcal/nvic.h"

#define NVIC_BASE_ADDRESS           0xE000E100
#define SCB_BASE_ADDRESS            0xE000ED00
#define GET_REG_NUM_SHIFT			5
#define GET_IRQn_BIT_MASK			0x1F
#define SCB_AIRCR_VECTKEY_Pos       16                                             /*!< SCB AIRCR: VECTKEY Position */
#define SCB_AIRCR_VECTKEY_Msk       (0xFFFFUL << SCB_AIRCR_VECTKEY_Pos)            /*!< SCB AIRCR: VECTKEY Mask */

#define SCB_AIRCR_VECTKEYSTAT_Pos   16                                             /*!< SCB AIRCR: VECTKEYSTAT Position */
#define SCB_AIRCR_VECTKEYSTAT_Msk   (0xFFFFUL << SCB_AIRCR_VECTKEYSTAT_Pos)        /*!< SCB AIRCR: VECTKEYSTAT Mask */

#define SCB_AIRCR_PRIGROUP_Pos       8                                             /*!< SCB AIRCR: PRIGROUP Position */
#define SCB_AIRCR_PRIGROUP_Msk       (7UL << SCB_AIRCR_PRIGROUP_Pos)                /*!< SCB AIRCR: PRIGROUP Mask */

#define VECTKEY						 0x5FA
typedef struct
{
	uint32 ISER[8];
	uint32 Reserved1[24];
	uint32 ICER[8];
	uint32 Reserved2[24];
	uint32 ISPR[8];
	uint32 Reserved3[24];
	uint32 ICPR[8];
	uint32 Reserved4[24];
	uint32 IABR[8];
	uint32 Reserved5[56];
	uint8 IP[240];
	uint32 Reserved6[644];
	uint32 STIR;
}NVIC_PERI_t;

typedef struct
{
	uint32 CPUID;
	uint32 ICSR;
	uint32 VTOR;
	uint32 AIRCR;
	uint32 SCR;
	uint32 CCR;
	uint8 SHP[12];
	uint32 SHCSR;
	uint32 CFSR;
	uint32 HFSR;
	uint32 reserved;
	uint32 MMAR;
	uint32 BFAR;
	uint32 AFSR;
} SCB_PERI_t;

volatile NVIC_PERI_t *const NVIC = (volatile NVIC_PERI_t *)NVIC_BASE_ADDRESS;
volatile SCB_PERI_t *const SCB = (volatile SCB_PERI_t *)SCB_BASE_ADDRESS;

void NVIC_SetPriorityGrouping(uint32 PriorityGroup)
{
  uint32 reg_value;
  uint32 PriorityGroupTmp = (PriorityGroup & (uint32)0x07);               /* only values 0..7 are used          */

  reg_value  =  SCB->AIRCR;                                                   /* read old register configuration    */
  reg_value &= ~(SCB_AIRCR_VECTKEY_Msk | SCB_AIRCR_PRIGROUP_Msk);             /* clear bits to change               */
  reg_value  =  (reg_value                                 |
                ((uint32)VECTKEY << SCB_AIRCR_VECTKEY_Pos) |
                (PriorityGroupTmp << 8));                                     /* Insert write key and priorty group */
  SCB->AIRCR =  reg_value;
}


uint32 NVIC_GetPriorityGrouping(void)
{
  return ((SCB->AIRCR & SCB_AIRCR_PRIGROUP_Msk) >> SCB_AIRCR_PRIGROUP_Pos);   /* read priority grouping field */
}

void NVIC_EnableIRQ(IRQn_t IRQn)
{
	/*  NVIC->ISER[(IRQn >> 5)] = (1 << (IRQn & 0x1F));  enable interrupt
	 *  (uint32)((int32_t)IRQn) >> GET_REG_NUM_SHIFT
	 *  is IRQn >> 5 Means division by 2^5 which is 32
	 *  IRQn & 0x1F Means reminder 32*/
	NVIC->ISER[(uint32)((sint32)IRQn) >> GET_REG_NUM_SHIFT] = (uint32)(1 << ((uint32)((sint32)IRQn) & (uint32)GET_IRQn_BIT_MASK)); /* enable interrupt */
}

void NVIC_DisableIRQ(IRQn_t IRQn)
{
  NVIC->ICER[((uint32)(IRQn) >> GET_REG_NUM_SHIFT)] = (1 << ((uint32)(IRQn) & GET_IRQn_BIT_MASK)); /* disable interrupt */
}

uint32 NVIC_GetPendingIRQ(IRQn_t IRQn)
{
  return((uint32) ((NVIC->ISPR[(uint32)(IRQn) >> GET_REG_NUM_SHIFT] & (1 << ((uint32)(IRQn) & GET_IRQn_BIT_MASK)))?1:0)); /* Return 1 if pending else 0 */
}

void NVIC_SetPendingIRQ(IRQn_t IRQn)
{
  NVIC->ISPR[((uint32)(IRQn) >> GET_REG_NUM_SHIFT)] = (1 << ((uint32)(IRQn) & GET_IRQn_BIT_MASK)); /* set interrupt pending */
}

void NVIC_ClearPendingIRQ(IRQn_t IRQn)
{
  NVIC->ICPR[((uint32)(IRQn) >> GET_REG_NUM_SHIFT)] = (1 << ((uint32)(IRQn) & GET_IRQn_BIT_MASK)); /* Clear pending interrupt */
}
void NVIC_SetPriority(IRQn_t IRQn, uint32 priority)
{
  if(IRQn < 0) {
    SCB->SHP[((uint32)(IRQn) & 0xF)-4] = ((priority << (8 - __NVIC_PRIO_BITS)) & 0xff); } /* set Priority for Cortex-M  System Interrupts */
  else {
    NVIC->IP[(uint32)(IRQn)] = ((priority << (8 - __NVIC_PRIO_BITS)) & 0xff);    }        /* set Priority for device specific Interrupts  */
}

 uint32 NVIC_GetPriority(IRQn_t IRQn)
{

  if(IRQn < 0) {
    return((uint32)(SCB->SHP[((uint32)(IRQn) & 0xF)-4] >> (8 - __NVIC_PRIO_BITS)));  } /* get priority for Cortex-M  system interrupts */
  else {
    return((uint32)(NVIC->IP[(uint32)(IRQn)]           >> (8 - __NVIC_PRIO_BITS)));  } /* get priority for device specific interrupts  */
}

 uint32 NVIC_EncodePriority (uint32 PriorityGroup, uint32 PreemptPriority, uint32 SubPriority)
{
  uint32 PriorityGroupTmp = (PriorityGroup & 0x07);          /* only values 0..7 are used          */
  uint32 PreemptPriorityBits;
  uint32 SubPriorityBits;

  PreemptPriorityBits = ((7 - PriorityGroupTmp) > __NVIC_PRIO_BITS) ? __NVIC_PRIO_BITS : 7 - PriorityGroupTmp;
  SubPriorityBits     = ((PriorityGroupTmp + __NVIC_PRIO_BITS) < 7) ? 0 : PriorityGroupTmp - 7 + __NVIC_PRIO_BITS;

  return (
           ((PreemptPriority & ((1 << (PreemptPriorityBits)) - 1)) << SubPriorityBits) |
           ((SubPriority     & ((1 << (SubPriorityBits    )) - 1)))
         );
}

 void NVIC_DecodePriority (uint32 Priority, uint32 PriorityGroup, uint32* pPreemptPriority, uint32* pSubPriority)
{
  uint32 PriorityGroupTmp = (PriorityGroup & 0x07);          /* only values 0..7 are used          */
  uint32 PreemptPriorityBits;
  uint32 SubPriorityBits;

  PreemptPriorityBits = ((7 - PriorityGroupTmp) > __NVIC_PRIO_BITS) ? __NVIC_PRIO_BITS : 7 - PriorityGroupTmp;
  SubPriorityBits     = ((PriorityGroupTmp + __NVIC_PRIO_BITS) < 7) ? 0 : PriorityGroupTmp - 7 + __NVIC_PRIO_BITS;

  *pPreemptPriority = (Priority >> SubPriorityBits) & ((1 << (PreemptPriorityBits)) - 1);
  *pSubPriority     = (Priority                   ) & ((1 << (SubPriorityBits    )) - 1);
}
void NVIC_SoftwareInterrupt(IRQn_t IRQn)
{
  NVIC->STIR = IRQn;
}
