#ifndef __ISO_RCC_H
#define	__ISO_RCC_H

#include "stm32f0xx.h"

typedef enum
{
  HSI   = 0x00, 
  HSE   = 0x04,
	PLL   = 0x08,
	HSI48 = 0x0c
}ISO_SystemClock_TypeDef;

void SystemClock_Configuration(void);

#endif /* __ISO_RCC_H */
