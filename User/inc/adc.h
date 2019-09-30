#ifndef __ISO_ADC_H
#define	__ISO_ADC_H


#include "stm32f0xx.h"

#define ADC1_DR_Address                0x40012440
extern __IO uint16_t ADC_ConvertedValue[3];
extern __IO uint16_t TempSensVoltmv ;
extern __IO uint16_t ADC1_Votage ;
extern __IO uint16_t ADC2_Votage ;
void ADC1_Init(void);

#endif /* __ISO_ADC_H */
