#include "RCC.h"
#include "GPIO.h"
#include "SYSTICK.h"
#include "INIT_SYS.h"
#include "NVIC.h"

//static pfun CallBack;
//u64 fclk = 25000000L;
Peripheral_Enable_Error_t initSys(void){
	Peripheral_Enable_Error_t Ret_Error_status_t = Peripheral_Enable_enumNok;
	RCC_ErrorStatus_t error_status =controlPeripheral(RCC_APB2_USART1EN,RCC_Peripheral_Enable); 
	/*= enableClock( RCC_EN_HSE);
	
	if(error_status == RCC_enumOk){
		error_status = configurePLL(6,192,RCC_PLLCFGR_PLLP_DIV2,RCC_PLL_SRC_HSE);
	}
	if(error_status == RCC_enumOk){
		error_status = enableClock( RCC_EN_PLL);
	}
	if(error_status == RCC_enumOk){
		error_status=selectSysClock(RCC_CLK_PLL);
	}
	
	if(error_status == RCC_enumOk){
		error_status=selectSysClock(RCC_CLK_HSE);
	}
	if(error_status == RCC_enumOk){
		error_status = configure_prescalers(RCC_PRE_AHB_SYSCLK_NOT_DIVIDED);//for systick: ahb/8
	}
	if(error_status == RCC_enumOk){
		error_status = configure_prescalers(RCC_PRE_APB2_NO_DIV);
	}
	if(error_status == RCC_enumOk){
		error_status = configure_prescalers(RCC_PRE_APB1_NO_DIV);
	}
	if(error_status == RCC_enumOk){
		error_status = controlPeripheral(RCC_APB2_USART1EN,RCC_Peripheral_Enable); 
	}
	*/
	if(error_status == RCC_enumOk){
		error_status = controlPeripheral(RCC_AHB1_GPIOAEN,RCC_Peripheral_Enable); 
	}
	
	if(error_status == RCC_enumOk){
		
		Ret_Error_status_t = Peripheral_Enable_enumOk;
		
		
	}
	/*
	SYSTICK_stop();
	SYSTICK_setTimeMS(3);
	SYSTICK_setCallBackFunction(CallBack);
	SYSTICK_start(mode_Periodic);	
	*/
	return Ret_Error_status_t;
}


