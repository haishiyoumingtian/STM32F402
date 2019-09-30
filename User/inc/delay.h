#ifndef __SYSTICK_H
#define __SYSTICK_H

#include "stm32f0xx.h"

void SysTick_Init(void);
void TimingDelay_Decrement(void);
void Delay_us(__IO u32 nTime);         // 单位10us
#define Delay_ms(x) Delay_us(100*x)	 //单位ms


#endif /* __ISO_SYSTICK_H */
