#include "led.h"   
#include "usart.h"

 /**
  * @brief  初始化控制LED的IO
  * @param  无
  * @retval 无
  */

void LED_GPIO_Config(void)
{		
		/*定义一个GPIO_InitTypeDef类型的结构体*/
		GPIO_InitTypeDef GPIO_InitStructure;

		RCC_AHBPeriphClockCmd( RCC_AHBPeriph_GPIOA, ENABLE); 											   
		GPIO_InitStructure.GPIO_Pin = LED1;	
		GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 
		GPIO_InitStructure.GPIO_PuPd   = GPIO_PuPd_NOPULL;  
		GPIO_Init(LEDPort, &GPIO_InitStructure);		  
		GPIO_SetBits(LEDPort, LED1);
}

void LED_Delay(__IO uint32_t nCount)	 //简单的延时函数
{
	for(; nCount != 0; nCount--);
}

/*----------------------------------------------------------------*/
void LED_Test(void)
{

}


/*********************************************END OF FILE**********************/
