#ifndef __USART1_H
#define	__USART1_H

#include "stm32f0xx.h"
#include <stdio.h>
typedef enum
{
  USART1_TX   = GPIO_Pin_9, 
  USART1_RX   = GPIO_Pin_10
}ISO_USART1_TypeDef;
typedef struct
{
	unsigned char ReceiveNum       :6;
  unsigned char ReceiveEndFlag   :1;
  unsigned char ReceiveFinishFlag:1;
} UsartReceiveNumBit_TypeDef;
#define Max_RX_Buffer_Len  64
extern UsartReceiveNumBit_TypeDef  UsartReceiveNum;
extern uint8_t USART_RX_Buffer[Max_RX_Buffer_Len];
void USART_SendString(char *str);
void USART1_Config(void);
void AutoBauRate_StartBitMethod(void);
void NVIC_Configuration(void);
int fputc(int ch, FILE *f);
int fgetc(FILE *f);

#endif /* __USART1_H */
