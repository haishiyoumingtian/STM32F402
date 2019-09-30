/******************** (C) COPYRIGHT  风驰嵌入式开发工作室 ********************
 * 文件名  ：iso_rcc.c
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
  * 
  * 
  ******************************************************************************
  */
	
#include "rcc.h"	
void SystemClock_Configuration(void)
{
	
    	/* 选择锁相环（PLL）时钟源为HSE 1分频，倍频数为6，则PLL输出频率为 8MHz * 6 = 48MHz */
    	RCC_PLLConfig(RCC_PLLSource_HSI_Div2, RCC_PLLMul_12);

    	/* 使能PLL */ 
    	RCC_PLLCmd(ENABLE);

    	/* 等待PLL输出稳定 */
    	while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);

    	/* 选择SYSCLK时钟源为PLL */
    	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

    	/* 等待PLL成为SYSCLK时钟源 */
    	while(RCC_GetSYSCLKSource() != PLL);
	
}


