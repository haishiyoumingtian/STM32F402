#include "led.h"  
#include "tim.h"
#include "usart.h"
#include "string.h"
#include "can.h"
#include "adc.h"
#include "delay.h"
#include "motor.h"
#include "motor_ctrl.h"


int main(void)
{
	uint8_t buffer[8]={1,1,0,0,0,0,0,0};
	SystemInit ();
	LED_GPIO_Config();	
	USART1_Config();
	MOTOR_GPIO_Config();
	USER_CAN_Init();
	ADC1_Init();
	SysTick_Init();
	CAN_InterruptMode_Configuration();
	GPIO_SetBits(GPIOA,GPIO_Pin_4);
	LED_Delay(0x0FFFFF);
	GPIO_ResetBits(GPIOA,GPIO_Pin_4);
	Motor_Ctrl(Initial_Arr);
  while (1)
  {
		TempSensVoltmv = (uint16_t)((ADC_ConvertedValue[2]* 3300) / 0xFFF);
		ADC1_Votage = (uint16_t)((ADC_ConvertedValue[1]* 3300) / 0xFFF);
		ADC2_Votage = (uint16_t)((ADC_ConvertedValue[0]* 3300) / 0xFFF); 
		printf("The current TempSensVolt = %d mV\r\n", TempSensVoltmv); 
		printf("The current ADC1_Votage = %d mV\r\n", ADC1_Votage); 
		printf("The current ADC2_Votage = %d mV\r\n\r\n", ADC2_Votage); 
		CAN_Transmit_Buffer(buffer,8);
		Speed_Adjustment();
		ISO_LED(LED1,ON);		    // ÁÁ
		LED_Delay(0x0FFFFF);
		ISO_LED(LED1,OFF);		  // Ãð
		LED_Delay(0x0FFFFF);
  }
}

