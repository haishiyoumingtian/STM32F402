#include "adc.h"
#include "stm32f0xx_conf.h"
#include "usart.h"

__IO uint16_t ADC_ConvertedValue[3];
__IO uint16_t TempSensVoltmv = 0, ADC1_Votage = 0, ADC2_Votage=0;

/**
  * @brief  使能ADC1和DMA1的时钟，初始化PB.08
  * @param  无
  * @retval 无
  */
static void ADC1_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/* Enable ADC1 and GPIOB clock */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	
	/* Configure PB.08  as analog input */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_Init(GPIOA, &GPIO_InitStructure);				// PB0,输入时不用设置速率
}

/**
  * @brief  配置ADC1的工作模式为MDA模式
  * @param  无
  * @retval 无
  */
static void ADC1_Mode_Config(void)
{
	ADC_InitTypeDef     ADC_InitStructure;
  DMA_InitTypeDef     DMA_InitStructure;
	//NVIC_InitTypeDef    NVIC_InitStructure;
  
  /* ADC1 DeInit */  
  ADC_DeInit(ADC1);
  
  /* ADC1 Periph clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
  
  /* DMA1 clock enable */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1 , ENABLE);
  
  /* DMA1 Channel1 Config */
  DMA_DeInit(DMA1_Channel1);
  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&ADC1->DR;
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)ADC_ConvertedValue;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
  DMA_InitStructure.DMA_BufferSize = 3;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
  DMA_Init(DMA1_Channel1, &DMA_InitStructure);
	
	  /* Enable DMA1 Channelx Transfer Complete interrupt */
//  DMA_ITConfig(DMA1_Channel1, DMA_IT_TC, ENABLE);

//  /* Enable DMA1 channel2 IRQ Channel */
//  NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel1_IRQn;
//  NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
//  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//  NVIC_Init(&NVIC_InitStructure);
  
  /* DMA1 Channel1 enable */
  DMA_Cmd(DMA1_Channel1, ENABLE);
  
  /* ADC DMA request in circular mode */
  ADC_DMARequestModeConfig(ADC1, ADC_DMAMode_Circular);
  
  /* Enable ADC_DMA */
  ADC_DMACmd(ADC1, ENABLE);  
  
  /* Initialize ADC structure */
  ADC_StructInit(&ADC_InitStructure);
  
  /* Configure the ADC1 in continous mode withe a resolutuion equal to 12 bits  */
  ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE; 
  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_ScanDirection = ADC_ScanDirection_Upward;
  ADC_Init(ADC1, &ADC_InitStructure); 
	 ADC_Cmd(ADC1, DISABLE); 
 
//  /* Convert the ADC1 temperature sensor  with 55.5 Cycles as sampling time 1448*/ 
  ADC_ChannelConfig(ADC1, ADC_Channel_TempSensor , ADC_SampleTime_55_5Cycles);  
  ADC_TempSensorCmd(ENABLE);
  /* Convert the ADC1 Vref  with 55.5 Cycles as sampling time */ 
	ADC_ChannelConfig(ADC1, ADC_Channel_1 , ADC_SampleTime_55_5Cycles);
  ADC_ChannelConfig(ADC1, ADC_Channel_2 , ADC_SampleTime_55_5Cycles); 
//  ADC_VbatCmd(ENABLE);
  
  /* ADC Calibration */
  ADC_GetCalibrationFactor(ADC1);
  
  /* Enable ADC1 */
  ADC_Cmd(ADC1, ENABLE);     
  /* Wait the ADCEN falg */
  while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_ADEN)); 
  /* ADC1 regular Software Start Conv */ 
  ADC_StartOfConversion(ADC1);
}

/**
  * @brief  ADC1初始化
  * @param  无
  * @retval 无
  */
void ADC1_Init(void)
{
	ADC1_GPIO_Config();
	ADC1_Mode_Config();
}

