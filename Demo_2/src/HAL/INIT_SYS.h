#ifndef HAL_INCLUDE_INIT_SYS_H_
#define HAL_INCLUDE_INIT_SYS_H_


typedef void(*pfun)(void); 
typedef enum{
	Peripheral_Enable_enumNok,
	Peripheral_Enable_enumOk
}Peripheral_Enable_Error_t;

Peripheral_Enable_Error_t initSys(void);
void initSys_setCBF(pfun cbf);

#endif // HAL_INCLUDE_INIT_SYS_H_