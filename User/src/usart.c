	/******************** (C) COPYRIGHT  风驰嵌入式开发工作室 ********************
 * 文件名  ：iso_usart1.c
 * 描述    ：STM32F0-LED       
 * 实验平台：M0-ISO开发板
 * 库版本  ：V1.3.0
 * 作者    ：风驰 QQ:779814207/2366260464
 * 博客    ：
 * 淘宝    ：http://shop71177993.taobao.com/
 * 修改时间: 2014-12-15
**********************************************************************************/	
/**
  ******************************************************************************
  * @file    iso_led.c 
  * @author  Fengchi  Technology Team
  * @version V1.3.0
  * @date    15-December-2014
  * @brief   led
  ******************************************************************************
  * @attention
  * USART1_TX<----->PA9
  * USART1_RX<----->PA10
  ******************************************************************************
  */
#include "usart.h"
#include "led.h" 

UsartReceiveNumBit_TypeDef UsartReceiveNum;

uint8_t USART_RX_Buffer[Max_RX_Buffer_Len];
 /**
  * @brief  USART1 接收中断配置
  * @param  无
  * @retval 无
  */
static void USART1_NVIC_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStructure; 
	
	/* Enable the USART1 Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;	 
	NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

 
 /**
  * @brief  USART1 GPIO 配置,工作模式配置。115200 8-N-1
  * @param  无
  * @retval 无
  */
void USART1_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	
	USART_Cmd(USART1, DISABLE);
	USART_DeInit(USART1);
	
	/* config USART1 clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	/*开启GPIOA的外设时钟*/
	RCC_AHBPeriphClockCmd( RCC_AHBPeriph_GPIOA, ENABLE); 
	/*配置映射外设管脚*/
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_1);
  GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_1);  
	/* USART1 GPIO config */
	/* Configure USART1 Tx (PA.09) as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin    = USART1_TX;
	GPIO_InitStructure.GPIO_Mode   = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType  = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed  = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd   = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);    
	/* Configure USART1 Rx (PA.10) as input mode */
	GPIO_InitStructure.GPIO_Pin    = USART1_RX;
	GPIO_InitStructure.GPIO_Mode   = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_PuPd   = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	

	/* USART1 mode config */
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART1, &USART_InitStructure);
	
	/* 使能串口1接收中断 */
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);	
	USART_Cmd(USART1, ENABLE);
  USART_ClearFlag(USART1, USART_FLAG_TC);
  
  USART1_NVIC_Config();
}

void AutoBauRate_StartBitMethod(void)
{ 
 
  /* Configure the AutoBaudRate method */
  USART_AutoBaudRateConfig(USART1, USART_AutoBaudRate_StartBit);
  
  /* Enable AutoBaudRate feature */
  USART_AutoBaudRateCmd(USART1, ENABLE);
  
  /* Wait until Receive enable acknowledge flag is set */
  while(USART_GetFlagStatus(USART1, USART_FLAG_REACK) == RESET);
	
  /* Wait until Transmit enable acknowledge flag is set */  
  while(USART_GetFlagStatus(USART1, USART_FLAG_TEACK) == RESET);

  /* Loop until the end of Autobaudrate phase */
  while(USART_GetFlagStatus(USART1, USART_FLAG_ABRF) == RESET);
 
  /* If AutoBaudBate error occurred */
  if (USART_GetFlagStatus(USART1, USART_FLAG_ABRE) != RESET)
  {
    /* Turn on LED3 */
    ISO_LED(LED3,ON);
  }
  else
  {
    /* Turn on LED2 */
    ISO_LED(LED2,ON);
	}
    
  
}





 /**
  * @brief  重定向c库函数printf到USART1
  * @param  
  * @retval 
  */
#pragma import(__use_no_semihosting) 
struct __FILE
{
    int handle;
};
FILE __stdout;   
_sys_exit(int x)
{
	x = x;
}
int fputc(int ch, FILE *f)
{
	 USART_SendData(USART1,ch);
	 while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
	 return ch;
}

void USART_SendString(char *str)
 
{
         uint8_t index=0;
 
         do
 
         {
 
                   USART_SendData(USART1,str[index]);
 
                   while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
 
                   index++;
 
         }
 
         while(str[index]!=0);
}



 /**
  * @brief  重定向c库函数scanf到USART1
  * @param  
  * @retval 
  */
int fgetc(FILE *f)
{
		/* 等待串口1输入数据 */
		while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);

		return (int)USART_ReceiveData(USART1);
}
/*********************************************END OF FILE**********************/
