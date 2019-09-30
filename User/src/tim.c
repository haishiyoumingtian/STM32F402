#include "tim.h"
#include "usart.h"


//uint16_t IndexWave[]={479,959,1439,1919,2399,2879,3359,3839,4913,4799,9599,14399,19199,23999,28799,33599,38399,49133,47999,
//										  47999,49133,38399,33599,28799,23999,19199,14399,9599,4799,4913,3839,3359,2879,2399,1919,1439,959,479};
//void TIM3_GPIO_Config(void) 
//{
//  GPIO_InitTypeDef GPIO_InitStructure;

//  /* GPIOB Clocks enable */
//  RCC_AHBPeriphClockCmd( RCC_AHBPeriph_GPIOA, ENABLE);
//	RCC_AHBPeriphClockCmd( RCC_AHBPeriph_GPIOB, ENABLE);
//  
//  /* GPIOA Configuration: Channel 1, 2, 3 and 4 as alternate function push-pull */
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 ;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
//  GPIO_Init(GPIOA, &GPIO_InitStructure);
//	
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 ;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
//  GPIO_Init(GPIOB, &GPIO_InitStructure);
//	
//  GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_1);
//  GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_1);
//  GPIO_PinAFConfig(GPIOB, GPIO_PinSource0, GPIO_AF_1);
//  GPIO_PinAFConfig(GPIOB, GPIO_PinSource1, GPIO_AF_1);
//}

void TIM3_Mode_Config(uint32_t arr)
{
	
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	//TIM_OCInitTypeDef  TIM_OCInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	//uint16_t TimerPeriod = 0;

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3 , ENABLE);
  /* Time Base configuration */
  TIM_TimeBaseStructure.TIM_Prescaler = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseStructure.TIM_Period = 47999;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

  /* Channel 1, 2 Configuration in PWM mode */
//  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
//  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
//  TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
//  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
//  TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
//  TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
//  TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;

  NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	
//  TIM_OCInitStructure.TIM_Pulse = 0;
//  TIM_OC1Init(TIM3, &TIM_OCInitStructure);

//  TIM_OCInitStructure.TIM_Pulse = 0;
//  TIM_OC2Init(TIM3, &TIM_OCInitStructure);
//	
//	TIM_OCInitStructure.TIM_Pulse = 0;
//  TIM_OC3Init(TIM3, &TIM_OCInitStructure);

//  TIM_OCInitStructure.TIM_Pulse = 0;
//  TIM_OC4Init(TIM3, &TIM_OCInitStructure);

  /* TIM1 counter enable */
  TIM_Cmd(TIM3, ENABLE);
  /* TIM1 Main Output Enable */
//  TIM_CtrlPWMOutputs(TIM3, ENABLE);
	TIM_ITConfig(TIM3,TIM_IT_Update, ENABLE);
}

void TIM2_Mode_Config(uint32_t arr)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , ENABLE);

  TIM_TimeBaseStructure.TIM_Prescaler = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseStructure.TIM_Period = 47999;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

  NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  TIM_Cmd(TIM2, ENABLE);
	TIM_ITConfig(TIM2,TIM_IT_Update, ENABLE);
}
void TIM14_Mode_Config(uint32_t arr)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14 , ENABLE);

  TIM_TimeBaseStructure.TIM_Prescaler = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseStructure.TIM_Period = 47999;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
  TIM_TimeBaseInit(TIM14, &TIM_TimeBaseStructure);

  NVIC_InitStructure.NVIC_IRQChannel = TIM14_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  TIM_Cmd(TIM14, ENABLE);
	TIM_ITConfig(TIM14,TIM_IT_Update, ENABLE);
}
void TIM16_Mode_Config(uint32_t arr)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM16 , ENABLE);

  TIM_TimeBaseStructure.TIM_Prescaler = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseStructure.TIM_Period = 47999;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
  TIM_TimeBaseInit(TIM16, &TIM_TimeBaseStructure);

  NVIC_InitStructure.NVIC_IRQChannel = TIM16_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  TIM_Cmd(TIM16, ENABLE);
	TIM_ITConfig(TIM16,TIM_IT_Update, ENABLE);
}
void TIM17_Mode_Config(uint32_t arr)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM17 , ENABLE);

  TIM_TimeBaseStructure.TIM_Prescaler = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseStructure.TIM_Period = 47999;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
  TIM_TimeBaseInit(TIM17, &TIM_TimeBaseStructure);

  NVIC_InitStructure.NVIC_IRQChannel = TIM17_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  TIM_Cmd(TIM17, ENABLE);
	TIM_ITConfig(TIM17,TIM_IT_Update, ENABLE);
}

