#include "stm32f0xx_it.h"
#include "tim.h"
#include "usart.h"
#include "can.h"
#include "stm32f0xx_can.h"
#include "adc.h"
#include "motor.h"
#include "led.h"
#include "motor_ctrl.h"

/** @addtogroup Template_Project
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M0 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
}

/******************************************************************************/
/*                 STM32F0xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f0xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles USART1 interrupt request.
  * @param  None
  * @retval None
  */
void USART1_IRQHandler(void)
{
		uint8_t UsartRes;
	    //接收中断(接收到的数据必须是0x0d 0x0a结尾)
			if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  
			{
					UsartRes =USART_ReceiveData(USART1);//读取接收到的数据
					if(0==UsartReceiveNum.ReceiveFinishFlag)//接收未完成 UsartReceiveNum的ReceiveFinishFlag=0
					{
							if(1==UsartReceiveNum.ReceiveEndFlag)//接收到了0x0d UsartReceiveNum 的ReceiveEndFlag=1
							{
								if(UsartRes!=0x0a)//接收到标志位后下一个不是0x0a,表示接收错误,重新开始
								{	 
									UsartReceiveNum.ReceiveNum=0;	
									UsartReceiveNum.ReceiveEndFlag=0;
									UsartReceiveNum.ReceiveFinishFlag=0;
								}									
								else 
								{
									UsartReceiveNum.ReceiveFinishFlag=1;	//接收完成了UsartReceiveNum的 ReceiveFinishFlag=1
									USART_RX_Buffer[UsartReceiveNum.ReceiveNum]='\0' ;/*只是为了方便大于信息*/
								}
							}
							else //还没收到0X0D
							{	
								if(UsartRes==0x0d)UsartReceiveNum.ReceiveEndFlag=1;
								else
								{
									USART_RX_Buffer[UsartReceiveNum.ReceiveNum]=UsartRes ;
									UsartReceiveNum.ReceiveNum++;
									//接收数据长度大于缓存的长度表示错误,重新开始接收
									if(UsartReceiveNum.ReceiveNum>(Max_RX_Buffer_Len-1))	
									{
										UsartReceiveNum.ReceiveNum=0;	
										UsartReceiveNum.ReceiveEndFlag=0;
										UsartReceiveNum.ReceiveFinishFlag=0;
									}
	
								}		 
							}
					}   		 
			} 
}
uint8_t M1_k=0;
uint8_t M2_k=0;
uint8_t M3_k=0;
uint8_t M4_k=0;
uint8_t M5_k=0;
void TIM2_IRQHandler(void){
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)	//TIM_IT_Update
 	{			
		u8 direction=1;
		TIM_ClearITPendingBit (TIM2, TIM_IT_Update);	//必须要清除中断标志位 
		if(M1_Position!=0 || Speed1Mode_Statue==1){
			M1_Position--;
			if(1 == direction) SetMotor1(phasecw[M1_k]);
			else SetMotor1(phaseccw[M1_k]);
		}
		M1_k++;
		if(M1_k>=4){
			M1_k=0;
		}
	}
}
void TIM3_IRQHandler(void)
{	
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)	//TIM_IT_Update
 	{			
		u8 direction=1;
		TIM_ClearITPendingBit (TIM3, TIM_IT_Update);	//必须要清除中断标志位 	
		if(M2_Position!=0 || Speed2Mode_Statue==1){
			M2_Position--;
			if(1 == direction) SetMotor2(phasecw[M2_k]);
			else SetMotor2(phaseccw[M2_k]);				
		}
		M2_k++;
		if(M2_k>=4){
			M2_k=0;
		}
		
	}
}

void TIM14_IRQHandler(void){
		if (TIM_GetITStatus(TIM14, TIM_IT_Update) != RESET)	//TIM_IT_Update
 	{			
		u8 direction=1;
		TIM_ClearITPendingBit (TIM14, TIM_IT_Update);	//必须要清除中断标志位 
		if(M3_Position!=0 || Speed3Mode_Statue==1){
			M3_Position--;
			if(1 == direction) SetMotor3(phasecw[M3_k]);
			else SetMotor3(phaseccw[M3_k]);
		}
		M3_k++;
		if(M3_k>=4){
			M3_k=0;
		}
	}
}
void TIM16_IRQHandler(void){
		if (TIM_GetITStatus(TIM16, TIM_IT_Update) != RESET)	//TIM_IT_Update
 	{			
		u8 direction=1;
		TIM_ClearITPendingBit (TIM16, TIM_IT_Update);	//必须要清除中断标志位 
		if(M4_Position!=0 || Speed4Mode_Statue==1){
			M4_Position--;
			if(1 == direction) SetMotor4(phasecw[M4_k]);
			else SetMotor4(phaseccw[M4_k]);			
		}
		M4_k++;
		if(M4_k>=4){
			M4_k=0;
		}
	}
}
void TIM17_IRQHandler(void){
		if (TIM_GetITStatus(TIM17, TIM_IT_Update) != RESET)	//TIM_IT_Update
 	{			
		u8 direction=1;
		TIM_ClearITPendingBit (TIM17, TIM_IT_Update);	//必须要清除中断标志位 
		if(M5_Position!=0 || Speed5Mode_Statue==1){
			M5_Position--;
			if(1 == direction) SetMotor5(phasecw[M5_k]);
			else 	SetMotor5(phaseccw[M5_k]);		
		}
		M5_k++;
		if(M5_k>=4){
			M5_k=0;
		}
	}
}
void CEC_CAN_IRQHandler(void)
{
	uint8_t cnt=0;
  CanRxMsg RxMessage;
	RxMessage.StdId=0x00;
	RxMessage.ExtId=0x00;
	RxMessage.IDE=0;
	RxMessage.DLC=0;
	RxMessage.FMI=0;
  
	if( CAN_GetITStatus(CAN, CAN_IT_FMP0) == SET )
  {
		
    CAN_Receive(CAN, CAN_FIFO0, &RxMessage);
		if((RxMessage.ExtId==0x1234)  && 
			 (RxMessage.IDE==CAN_ID_EXT))
		{
			for(cnt=0;cnt<RxMessage.DLC;cnt++)
			{
				* pReceiveBuffer=RxMessage.Data[cnt];
				pReceiveBuffer++;
			}
			Receive_Buffer_Len +=RxMessage.DLC;
			CAN_FIFORelease(CAN,CAN_FIFO0);
			printf("\r\n CAN Receive Buffer==%s,RxMessage.DLC==%d \r\n",\
							pReceiveBuffer-RxMessage.DLC,Receive_Buffer_Len);
		}
		printf("get it!\r\n");
		CAN_ClearITPendingBit(CAN,CAN_IT_FMP0);
  }
}

//void DMA1_Channel1_IRQHandler(void)
//{
//			if(DMA_GetFlagStatus(DMA1_FLAG_TC1)!= RESET)	//判断通道2传输完成
//			{
//					/* Convert Vref voltage value in mv */
//					TempSensVoltmv = (uint16_t)((ADC_ConvertedValue[2]* 3300) / 0xFFF);
//					VCCVoltmv  = (uint16_t)((ADC_ConvertedValue[1]* 3300) / 0xFFF);
//					RightSensVoltmv = (uint16_t)((ADC_ConvertedValue[0]* 3300) / 0xFFF); 
//					DMA_ClearFlag(DMA1_FLAG_TC1);//清除通道1传输完成标志
//		  }
//}


/**
  * @}
  */ 


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
