#ifndef __TIM_H
#define __TIM_H

#include "stm32f0xx.h"


extern uint16_t IndexWave[];
//void TIM3_GPIO_Config(void) ;
void TIM2_Mode_Config(uint32_t arr);
void TIM3_Mode_Config(uint32_t arr);
void TIM14_Mode_Config(uint32_t arr);
void TIM16_Mode_Config(uint32_t arr);
void TIM17_Mode_Config(uint32_t arr);
 
#endif /* __DELAY_H */

