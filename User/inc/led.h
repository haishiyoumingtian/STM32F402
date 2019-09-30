#ifndef __ISO_LED_H
#define	__ISO_LED_H

#include "stm32f0xx.h"
typedef enum
{
  LED1   = GPIO_Pin_0, 
  LED2   = GPIO_Pin_0, 
  LED3   = GPIO_Pin_0
}ISO_LED_TypeDef;

#define LEDPort GPIOA

/** the macro definition to ISO the led on or off 
  * OFF - off
  * ON - on
  */
#define ON  0
#define OFF 1

/* 带参宏，可以像内联函数一样使用 */
#define ISO_LED(ISO_LEDPin,a)	if (a)	\
					GPIO_SetBits(LEDPort,ISO_LEDPin);\
					else		\
					GPIO_ResetBits(LEDPort,ISO_LEDPin)

/* 直接操作寄存器的方法控制IO */
#define	CtrlGPIOHi(GPIO_Port,i)			{GPIO_Port->BSRR=i;}			//设置为高电平		
#define CtrlGPIOLo(GPIO_Port,i)			{GPIO_Port->BRR=i;}				//输出低电平
#define CtrlGPIOToggle(GPIO_Port,i)	{GPIO_Port->ODR ^=i;}			//输出反转状态

/* 定义控制IO的宏 */
#define LED1_TOGGLE		CtrlGPIOToggle(LEDPort,LED1)
#define LED1_OFF		  CtrlGPIOHi(LEDPort,LED1)
#define LED1_ON			  CtrlGPIOLo(LEDPort,LED1)

void LED_GPIO_Config(void);
void LED_Test(void);
void LED_Delay(__IO uint32_t nCount);

#endif /* __ISO_LED_H */
