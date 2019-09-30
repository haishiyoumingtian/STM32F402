#include "can.h"
#include "led.h"
#include "usart.h"
#include "stm32f0xx_can.h"

typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;

/* 在中断处理函数中返回 */
uint8_t Receive_Buffer_Len=0;
uint8_t ReceiveBuffer[255];
uint8_t *pReceiveBuffer=ReceiveBuffer;

volatile TestStatus TestRx;	
static void CAN_NVIC_Configuration(void)
{

	NVIC_InitTypeDef NVIC_InitStructure; 
	
	/* Enable the USART1 Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = CEC_CAN_IRQn;	 
	NVIC_InitStructure.NVIC_IRQChannelPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}
static void CAN_GPIO_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; 
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA , ENABLE);	                        											 
	/* CAN1 Periph clock enable */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN, ENABLE);
	
	//GPIO_PinAFConfig(GPIOB,GPIO_PinSource8,GPIO_AF_4);
  //GPIO_PinAFConfig(GPIOB,GPIO_PinSource9,GPIO_AF_4);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource11,GPIO_AF_4); //GPIOA11复用为CAN1
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource12,GPIO_AF_4); //GPIOA12复用为CAN1	
	/* Configure CAN pin: RX */									             
	
	GPIO_InitStructure.GPIO_Pin    = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode   = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_PuPd   = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	/* Configure CAN pin: TX */									        

	GPIO_InitStructure.GPIO_Pin    = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode   = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType  = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed  = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd   = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}
void CAN_InterruptMode_Configuration(void)
{
	CAN_InitTypeDef        CAN_InitStructure;
	CAN_FilterInitTypeDef  CAN_FilterInitStructure;

	/* CAN register init */
	CAN_DeInit(CAN);
	CAN_StructInit(&CAN_InitStructure);
	
	/* CAN cell init */
	CAN_InitStructure.CAN_TTCM=DISABLE;           // 时间触发通信禁止
	CAN_InitStructure.CAN_ABOM=DISABLE;	          // 离线退出是在中断置位清0后退出
	CAN_InitStructure.CAN_AWUM=DISABLE;	          // 自动唤醒模式：清零sleep
	CAN_InitStructure.CAN_NART=DISABLE;	          // 自动重新传送豹纹，知道发送成功
	CAN_InitStructure.CAN_RFLM=DISABLE;	          // FIFO没有锁定，新报文覆盖旧报文
	CAN_InitStructure.CAN_TXFP=DISABLE;           // 发送报文优先级确定：标志符
	CAN_InitStructure.CAN_Mode=CAN_Mode_Normal; // 正常模式
	CAN_InitStructure.CAN_SJW=CAN_SJW_1tq;        // 1tq、BS1、BS2的值跟波特率有关
	CAN_InitStructure.CAN_BS1=CAN_BS1_8tq;
	CAN_InitStructure.CAN_BS2=CAN_BS2_7tq;
	CAN_InitStructure.CAN_Prescaler=3;					  // 分频系数为1
	CAN_Init(CAN, &CAN_InitStructure);						// 初始化CAN1
	
	/* CAN filter init */
	CAN_FilterInitStructure.CAN_FilterNumber=1;
	CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdMask;
	CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_32bit;
	CAN_FilterInitStructure.CAN_FilterIdHigh=0x0000;
	CAN_FilterInitStructure.CAN_FilterIdLow=0x0000;
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0x0000;
	CAN_FilterInitStructure.CAN_FilterMaskIdLow=0x0000;
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment=CAN_FIFO0;
	CAN_FilterInitStructure.CAN_FilterActivation=ENABLE;
	CAN_FilterInit(&CAN_FilterInitStructure);
	
	/* CAN FIFO0 message pending interrupt enable */ 
	CAN_ITConfig(CAN, CAN_IT_FMP0, ENABLE); //中断使能
}
void CAN_Transmit_Buffer(uint8_t* pBuffer,uint16_t NumByteToWrite)
{
	uint8_t NumOfPake=0,NumOfSingle=0,cnt=0;
	CanTxMsg TxMessage;
	NumOfPake=NumByteToWrite/8 ;
	NumOfSingle=NumByteToWrite%8 ;
	TxMessage.StdId=0x00;					 // 标准标识符为0
	TxMessage.ExtId=0x1234;				 // 设置扩展标示符（29位）
	TxMessage.IDE=CAN_ID_EXT;			 // 使用扩展标识符
	TxMessage.RTR=CAN_RTR_DATA;		 // 消息类型为数据帧，一帧8位
	while(NumOfPake--)
	{
				/* transmit 1 message */
			TxMessage.DLC=8;							
			for(cnt=0;cnt<8;cnt++)
			{
				TxMessage.Data[cnt]=* pBuffer;				 
				pBuffer++;
			}
			CAN_Transmit(CAN, &TxMessage);	
	}
	if(NumOfSingle)
	{
		TxMessage.DLC=NumOfSingle;							 
		for(cnt=0;cnt<NumOfSingle;cnt++)
		{
			TxMessage.Data[cnt]=* pBuffer;				 
			pBuffer++;
		}
		CAN_Transmit(CAN, &TxMessage);
	}
	
}
void USER_CAN_Init(void)
{
	CAN_NVIC_Configuration();
	CAN_GPIO_Configuration();
}


