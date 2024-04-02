/******************************************************************************
 *
 * Module: 
 *
 * File Name: nvic.h
 *
 * Description: 
 *
 * Author: Safia Hany
 * 
 * Date:  Mar 15, 2024
 ******************************************************************************/
#ifndef INCLUDE_NVIC_H_
#define INCLUDE_NVIC_H_

#include "library/Stm32F4xx.h"
#include "Std_Types.h"

#define PRIGROUP_0			0
#define PRIGROUP_1			1
#define PRIGROUP_2			2
#define PRIGROUP_3			3
#define PRIGROUP_4			4

/** @brief  Set Priority Grouping

  The function sets the priority grouping field using the required unlock sequence.
  The parameter PriorityGroup is assigned to the field SCB->AIRCR [10:8] PRIGROUP field.
  Only values from 0..7 are used.
  In case of a conflict between priority grouping and available
  priority bits (__NVIC_PRIO_BITS), the smallest possible priority group is set.

    @param [in]      PriorityGroup  Priority grouping field.
 */
void NVIC_SetPriorityGrouping(uint32 PriorityGroup);

/** @brief  Get Priority Grouping

  The function reads the priority grouping field from the NVIC Interrupt Controller.

    @return                Priority grouping field (SCB->AIRCR [10:8] PRIGROUP field).
 */
uint32 NVIC_GetPriorityGrouping(void);

/** @brief  Enable External Interrupt

    The function enables a device-specific interrupt in the NVIC interrupt controller.

    @param [in]      IRQn  External interrupt number. Value cannot be negative.
 */
void NVIC_EnableIRQ(IRQn_t IRQn);

/** @brief  Disable External Interrupt

    The function disables a device-specific interrupt in the NVIC interrupt controller.

    @param [in]      IRQn  External interrupt number. Value cannot be negative.
 */
void NVIC_DisableIRQ(IRQn_t IRQn);

/** @brief  Get Pending Interrupt

    The function reads the pending register in the NVIC and returns the pending bit
    for the specified interrupt.

    @param [in]      IRQn  Interrupt number.

    @return             0  Interrupt status is not pending.
    @return             1  Interrupt status is pending.
 */
uint32 NVIC_GetPendingIRQ(IRQn_t IRQn);

/** @brief  Set Pending Interrupt

    The function sets the pending bit of an external interrupt.

    @param [in]      IRQn  Interrupt number. Value cannot be negative.
 */
void NVIC_SetPendingIRQ(IRQn_t IRQn);
/** @brief  Set Interrupt Priority

    The function sets the priority of an interrupt.

    @param [in]      IRQn  Interrupt number.
    @param [in]  priority  Priority to set.
 */
void NVIC_SetPriority(IRQn_t IRQn, uint32 priority);
/** @brief  Get Interrupt Priority

    The function reads the priority of an interrupt. The interrupt
    number can be positive to specify an external (device specific)
    interrupt, or negative to specify an internal (core) interrupt.


    @param [in]   IRQn  Interrupt number.
    @return             Interrupt Priority. Value is aligned automatically to the implemented
                        priority bits of the microcontroller.
 */
 uint32 NVIC_GetPriority(IRQn_t IRQn);


/** @brief  Encode Priority

    The function encodes the priority for an interrupt with the given priority group,
    preemptive priority value, and subpriority value.
    In case of a conflict between priority grouping and available
    priority bits (__NVIC_PRIO_BITS), the samllest possible priority group is set.

    @param [in]     PriorityGroup  Used priority group.
    @param [in]   PreemptPriority  Preemptive priority value (starting from 0).
    @param [in]       SubPriority  Subpriority value (starting from 0).
    @return                        Encoded priority. Value can be used in the function \ref NVIC_SetPriority().
 */
 uint32 NVIC_EncodePriority (uint32 PriorityGroup, uint32 PreemptPriority, uint32 SubPriority);

/** @brief  Decode Priority

    The function decodes an interrupt priority value with a given priority group to
    preemptive priority value and subpriority value.
    In case of a conflict between priority grouping and available
    priority bits (__NVIC_PRIO_BITS) the samllest possible priority group is set.

    @param [in]         Priority   Priority value, which can be retrieved with the function \ref NVIC_GetPriority().
    @param [in]     PriorityGroup  Used priority group.
    @param [out] pPreemptPriority  Preemptive priority value (starting from 0).
    @param [out]     pSubPriority  Subpriority value (starting from 0).
 */
 void NVIC_DecodePriority (uint32 Priority, uint32 PriorityGroup, uint32* pPreemptPriority, uint32* pSubPriority);

void NVIC_SoftwareInterrupt(IRQn_t IRQn);
#endif /* INCLUDE_NVIC_H_ */
