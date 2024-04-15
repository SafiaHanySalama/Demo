/******************************************************************************
 *
 * Module: 
 *
 * File Name: rcc.c
 *
 * Description: 
 *
 * Author: Safia Hany
 * 
 * Date:  Feb 25, 2024
 ******************************************************************************/
#include "mcal/rcc.h"

#define RCC_BASE_ADDRESS		0x40023800

typedef struct
{
	uint32 CR;
	uint32 PLLCFGR;
	uint32 CFGR;
	uint32 CIR;
	uint32 AHB1RSTR;
	uint32 AHB2RSTR;
	uint32 Reserved;
	uint32 Reserved2;
	uint32 APB1RSTR;
	uint32 APB2RSTR;
	uint32 Reserved3;
	uint32 Reserved4;
	uint32 AHB1ENR;
	uint32 AHB2ENR;
	uint32 Reserved5;
	uint32 Reserved6;
	uint32 APB1ENR;
	uint32 APB2ENR;
	uint32 Reserved7;
	uint32 Reserved8;
	uint32 AHB1LPENR;
	uint32 AHB2LPENR;
	uint32 Reserved9;
	uint32 Reserved10;
	uint32 APB1LPENR;
	uint32 APB2LPENR;
	uint32 Reserved11;
	uint32 Reserved12;
	uint32 BDCR;
	uint32 CSR;
	uint32 Reserved13;
	uint32 Reserved14;
	uint32 SSCGR;
	uint32 PLLI2SCFGR;
	uint32 Reserved15;
	uint32 DCKCFGR;

}RCC_t;

volatile RCC_t*   const RCC       = (volatile RCC_t*)RCC_BASE_ADDRESS;

RCC_ERROR_STATUS RCC_enableClk(CLK_SRC clk)
{
	RCC_ERROR_STATUS ReturnStatus = RCC_OK;

	uint32 temp;
	temp = RCC->CR;
	if ((clk != HSI)|| (clk != HSE) ||( clk != PLL))
	{
		ReturnStatus = RCC_NOK;
	}
	else
	{
		temp &= ~clk ;
		temp |= ~clk ;
		RCC->CR  = temp ;
	}
	return ReturnStatus;
}

RCC_ERROR_STATUS RCC_disableClk(CLK_SRC clk)
{
	RCC_ERROR_STATUS ReturnStatus = RCC_OK;

	uint32 temp;
	temp = RCC->CR;
	if ((clk != HSI)|| (clk != HSE) ||( clk != PLL))
	{
		ReturnStatus = RCC_NOK;
	}
	else
	{
		temp &= ~clk ;
		RCC->CR  = temp ;
	}
	return ReturnStatus;
}


RCC_ERROR_STATUS RCC_setSysClk(CLK_SRC clk)
{
	RCC_ERROR_STATUS ReturnStatus = RCC_OK;
	uint32 temp;
	temp = RCC->CFGR;
	if ((clk != HSI)|| (clk != HSE) ||( clk != PLL))
	{
		ReturnStatus = RCC_NOK;
	}
	else
	{
		temp &= SYS_CLR_MASK ;
		temp |= clk;
		RCC->CFGR  = temp ;
	}
	return ReturnStatus;
}

RCC_ERROR_STATUS RCC_pllConfig(uint8 PLLM,uint8 PLLN,uint8 PLLP,uint8 PLLQ,PLL_SRC PLLclk)
{
	RCC_ERROR_STATUS ReturnStatus = RCC_OK;
	uint32 temp;
	temp = RCC->PLLCFGR;
	if ((PLLclk != HSI_DIV2)|| (PLLclk != HSE_DIV2) ||( PLLclk != HSE_NO_DIV))
	{
		ReturnStatus = RCC_NOK;
	}
	if (PLLM < MIN_PLLM || PLLM > MAX_PLLM || PLLN < MIN_PLLN || PLLN > MAX_PLLN
			|| PLLP < MIN_PLLP || PLLP > MAX_PLLP || PLLP == INVALID1_PLLP || PLLP == INVALID2_PLLP
			|| PLLQ < MIN_PLLQ || PLLQ > MAX_PLLQ)
	{
		ReturnStatus = RCC_NOK;
	}
	else
	{
		//Set PLL Source Clock
		temp &= PLL_SRC_CLR_MASK;
		temp |= PLLclk;
		RCC->PLLCFGR = temp;
		//Set PLL Configuration
		PLLP = (uint32)(PLLP / 2) - 1;
		temp &= PLL_CFG_CLR_MASK;
		temp = PLLQ << PLL_Q_SHIFT;
		temp |= PLLP << PLL_P_SHIFT;
		temp |= PLLN << PLL_N_SHIFT;
		temp |= PLLM;
		RCC->PLLCFGR = temp;
	}
	return ReturnStatus;
}


RCC_ERROR_STATUS RCC_enablePeri(RCC_BUS_ID_t busID, uint32 P_id)
{
	RCC_ERROR_STATUS ReturnStatus = RCC_OK;
	uint32 temp;
	if (busID < RCC_AHB1 || busID > RCC_APB2)
	{
		ReturnStatus = RCC_NOK;
	}
	else{
		switch (busID)
		{
		case RCC_AHB1:
			temp = RCC->AHB1ENR;
			P_id &= ~(0x00000000); 
			temp &= ~(P_id);
			temp |= P_id;
			RCC->AHB1ENR = temp;
			break;
		case RCC_AHB2:
			temp = RCC->AHB2ENR;
			temp &= ~(P_id);
			temp |= P_id;
			RCC->AHB2ENR = temp;
			break;
		case RCC_APB1:
			temp = RCC->APB1ENR;
			temp &= ~(P_id);
			temp |= P_id;
			RCC->APB1ENR = temp;
			break;
		case RCC_APB2:
			temp = RCC->APB2ENR;
			temp &= ~(P_id);
			temp |= P_id;
			RCC->APB2ENR = temp;
			break;
		default:
			ReturnStatus = RCC_NOK;
		}
	}
	return ReturnStatus;
}
RCC_ERROR_STATUS RCC_disablePeri(RCC_BUS_ID_t busID, uint32 P_id)
{
	RCC_ERROR_STATUS ReturnStatus = RCC_OK;
	uint32 temp;
	if (busID < RCC_AHB1 || busID < RCC_APB2)
	{
		ReturnStatus = RCC_NOK;
	}
	switch (busID)
	{
	case RCC_AHB1:
		temp = RCC->AHB1ENR;
		temp &= ~(P_id);
		RCC->AHB1ENR = temp;
		break;
	case RCC_AHB2:
		temp = RCC->AHB2ENR;
		temp &= ~(P_id);
		RCC->AHB2ENR = temp;
		break;
	case RCC_APB1:
		temp = RCC->APB1ENR;
		temp &= ~(P_id);
		RCC->APB1ENR = temp;
		break;
	case RCC_APB2:
		temp = RCC->APB2ENR;
		temp &= ~(P_id);
		RCC->AHB2ENR = temp;
		break;
	default:
		ReturnStatus = RCC_NOK;
	}
	return ReturnStatus;
}
RCC_ERROR_STATUS RCC_prescalerConfig(RCC_BUS_ID_t busID, uint32 prescalar)
{
	RCC_ERROR_STATUS ReturnStatus = RCC_OK;
	uint32 temp;
	 temp = RCC->CFGR;
	if (busID< RCC_AHB1 || busID< RCC_APB2)
	{
		ReturnStatus = RCC_NOK;
	}
	switch (busID)
	{
	case RCC_AHB1:
	case RCC_AHB2:
		if (prescalar > AHB_512) ReturnStatus = RCC_NOK;
		else
		{
			temp &= AHB_PRE_CLR_MASK ;
			temp |= prescalar ;
			RCC->CFGR = temp ;
		}
		break;
	case RCC_APB1:
		if (prescalar > APB1_16) ReturnStatus = RCC_NOK;
		else
		{
			temp &= APB1_PRE_CLR_MASK ;
			temp |= prescalar ;
			RCC->CFGR = temp ;
		}
		break;
	case RCC_APB2:
		if (prescalar > APB2_16) ReturnStatus = RCC_NOK;
		else
		{
			temp &= APB2_PRE_CLR_MASK ;
			temp |= prescalar ;
			RCC->CFGR = temp ;
		}
		break;
	default:
		ReturnStatus = RCC_NOK;
	}
	return ReturnStatus;
}
