#ifndef __ISO_CAN_H
#define	__ISO_CAN_H

#include "stm32f0xx.h"

typedef enum
{
  CAN_TX   = GPIO_Pin_9, 
  CAN_RX   = GPIO_Pin_8
}ISO_CAN_TypeDef;
extern  uint8_t Receive_Buffer_Len;
extern uint8_t *pReceiveBuffer;
void USER_CAN_Init(void);
void USER_CAN_Test(void);
void CAN_Loopback_Test(void);
void CAN_Transmit_Buffer(uint8_t* pBuffer,uint16_t NumByteToWrite);
void CAN_InterruptMode_Configuration(void);

#endif /* __ISO_CAN_H */

