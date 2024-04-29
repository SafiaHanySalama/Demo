/**********************Includes******************************/
#include "RCC.h"
/**********************Define********************************/


/* PLLQ: [27:24] */
#define RCC_PLLCFGR_PLLQ_SHIFT                  24
#define RCC_PLLCFGR_PLLQ_MASK                   0xf
/* PLLP: [17:16] */
#define RCC_PLLCFGR_PLLP_SHIFT                  16
#define RCC_PLLCFGR_PLLP_MASK                   0x3
/* PLLN: [14:6] */
#define RCC_PLLCFGR_PLLN_SHIFT                  6
#define RCC_PLLCFGR_PLLN_MASK                   0x1ff
/* PLLM: [5:0] */
#define RCC_PLLCFGR_PLLM_SHIFT                  0
#define RCC_PLLCFGR_PLLM_MASK                   0x3f


#define 	RCC_PLLP_DIV2   0x0
#define 	RCC_PLLP_DIV4   0x1
#define 	RCC_PLLP_DIV6   0x2
#define 	RCC_PLLP_DIV8   0x3
/*
#define RCC_CLK_HSIRDY   ((u32)0x00000002)
#define RCC_CLK_HSERDY   ((u32)0x00020000)
#define RCC_CLK_PLLRDY   ((u32)0x02000000)
#define RCC_CLK_PLLI2SRDY ((u32)0x08000000)
*/
#define RDY_Bit_offset 1
#define Clock_diasbled 0

/**********************Type Definitions**********************/
typedef struct{
	u32 CR;
	u32 PLLCFGR;
	u32 CFGR;
	u32 CIR;
	u32 AHB1RSTR;
	u32 AHB2RSTR;
	u32 Res1;
	u32 Res2;
	u32 APB1RSTR;
	u32 APB2RSTR;
	u32 Res3;
	u32 Res4;
	u32 AHB1ENR;
	u32 AHB2ENR;
	u32 Res5;
	u32 Res6;
	u32 APB1ENR;
	u32 APB2ENR;
	u32 Res7;
	u32 Res8;
	u32 AHB1LPENR;
	u32 AHB2LPENR;
	u32 Res9;
	u32 Res10;
	u32 APB1LPENR;
	u32 APB2LPENR;
	u32 Res11;
	u32 Res12;
	u32 BDCR;
	u32 CSR;

}RCC_reg_t;
/**********************Variables*****************************/
volatile RCC_reg_t * const RCC = (RCC_reg_t*)(0x40023800);
/**********************Static Function Prototypes************/
/**********************Implementation************************/
RCC_ErrorStatus_t enableClock(u32 clk){
	RCC_ErrorStatus_t Ret_enumErrorStatus = RCC_enumNok;
	RCC->CR |= clk;
	if(clk != RCC_EN_HSEBYP){
		while(!((RCC->CR)&(RDY_Bit_offset<<clk)));
		Ret_enumErrorStatus = RCC_enumOk;
	}
	else{
			Ret_enumErrorStatus = RCC_enumOk;
	}
	return Ret_enumErrorStatus;
}


RCC_ErrorStatus_t disableClock(u32 clk){
	RCC_ErrorStatus_t Ret_enumErrorStatus = RCC_enumNok;
	RCC->CR &= ~clk;
	if ((RCC->CR & clk) == Clock_diasbled) {
		Ret_enumErrorStatus = RCC_enumOk;
	}

	return Ret_enumErrorStatus;
}


RCC_ErrorStatus_t configurePLL(u16 M, u16 N,u8 P,u32 source){
	RCC_ErrorStatus_t Ret_enumErrorStatus = RCC_enumNok;
	if ((RCC->CR & RCC_EN_PLL) == Clock_diasbled) {
		if( ((source == RCC_PLL_SRC_HSE) && ((RCC->CR & RCC_EN_HSE)==Clock_diasbled))  ||\
				((source == RCC_PLL_SRC_HSI) && ((RCC->CR & RCC_EN_HSI)==Clock_diasbled))){
			Ret_enumErrorStatus = RCC_enumPLLSourceNotEnabled;
		}
		else if((M<2 && M>63 )&&(P != RCC_PLLP_DIV2 && P!= RCC_PLLP_DIV4 && P!= RCC_PLLP_DIV6 && P!= RCC_PLLP_DIV8)&&\
				(N<192 && N>432)){
			Ret_enumErrorStatus = RCC_enumWrongPLLConfiguration;
		}
		else{
			u32 temp = (M<< RCC_PLLCFGR_PLLM_SHIFT) | (N<<RCC_PLLCFGR_PLLN_SHIFT)\
					| (P<<RCC_PLLCFGR_PLLP_SHIFT) | source;
			u32 clear_N_M_P_src_mask = ~(RCC_PLLCFGR_PLLN_MASK | RCC_PLLCFGR_PLLM_MASK |RCC_PLLCFGR_PLLP_MASK | _RCC_PLLCFGR_PLLSRC );
			RCC->PLLCFGR = (RCC->PLLCFGR &clear_N_M_P_src_mask) | temp;
			Ret_enumErrorStatus = RCC_enumOk;
		}
	}
	return Ret_enumErrorStatus;
}


RCC_ErrorStatus_t controlPeripheral(u64 peripheral, u8 control){
	RCC_ErrorStatus_t Ret_enumErrorStatus = RCC_enumNok;
	if(control == RCC_Peripheral_Disable || control == RCC_Peripheral_Enable){
		Ret_enumErrorStatus = RCC_enumOk;
		u32* ptr = (u32*) &peripheral;
		//u32 temp;
		ptr++;
		switch(*ptr){
			case 1:
				RCC->AHB1ENR = (RCC->AHB1ENR & ~peripheral)|((u32)peripheral^control);
				break;
			case 2:
				RCC->APB1ENR = (RCC->APB1ENR & ~peripheral)|((u32)peripheral^control);
				break;
			case 4:
				RCC->APB2ENR = (RCC->APB2ENR & ~peripheral)|((u32)peripheral^control);
				break;
			default:
				Ret_enumErrorStatus = RCC_enumNok;
				break;
		}
	}
	return Ret_enumErrorStatus;
}


RCC_ErrorStatus_t selectSysClock(RCC_enuClock_t sysclk){
	RCC_ErrorStatus_t Ret_enumErrorStatus = RCC_enumNok;
	switch(sysclk){
		 case RCC_CLK_HSI:
			if((RCC->CR & RCC_EN_HSI)==Clock_diasbled){
				Ret_enumErrorStatus = RCC_enumSysClockNotEnabled;
			}else{
				Ret_enumErrorStatus = RCC_enumOk;
			}
			break;
		 case RCC_CLK_HSE:
			 if((RCC->CR & RCC_EN_HSE)==Clock_diasbled){
			 	Ret_enumErrorStatus = RCC_enumSysClockNotEnabled;
			 }else{
			 	Ret_enumErrorStatus = RCC_enumOk;
			 }
			 break;
		 case RCC_CLK_PLL:
			 if((RCC->CR & RCC_EN_PLL) == Clock_diasbled){
				 Ret_enumErrorStatus = RCC_enumSysClockNotEnabled;
			}else{
			   	Ret_enumErrorStatus = RCC_enumOk;
		    }
			break;
		 default:
			 Ret_enumErrorStatus = RCC_enumNok;
			 break;
	}
	if(Ret_enumErrorStatus == RCC_enumOk) RCC->CFGR |= sysclk;
	return Ret_enumErrorStatus;
}


RCC_ErrorStatus_t configure_prescalers(u64 prescale){
	RCC_ErrorStatus_t Ret_enumErrorStatus = RCC_enumNok;
	u32* ptr = (u32*)&prescale;
	ptr++;
	switch(*ptr){
		case 0x8:
			Ret_enumErrorStatus = RCC_enumOk;
			RCC->CFGR &= ~RCC_PRE_AHB_SYSCLK_DIV_BY_512;
			break;
		case 0x9:
			Ret_enumErrorStatus = RCC_enumOk;
			RCC->CFGR &= ~RCC_PRE_APB1_DIV_BY_16;
			break;
		case 0xA:
			Ret_enumErrorStatus = RCC_enumOk;
			RCC->CFGR &= ~RCC_PRE_APB2_DIV_BY_16;
			break;
		default:
			Ret_enumErrorStatus = RCC_enumNok;
			break;
	}
	RCC->CFGR |= (u32)prescale;
	return Ret_enumErrorStatus;
}
