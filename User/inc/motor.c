#include "motor.h"
#include "motor_ctrl.h"

/* 
M1:         M2:     		M3:      		M4:     		M5:
XQ0 :PA5  	XQ4 :PB4		XQ8 :PB2		XQ12:PB13		XQ16:PA6
XQ1 :PB8	  XQ5 :PB5		XQ9 :PB10		XQ13:PB14		XQ17:PA7
XQ2 :PB9		XQ6 :PB6		XQ10:PB11		XQ14:PB15		XQ18:PB0
XQ3 :PB3		XQ7 :PB7		XQ11:PB12		XQ15:PA8		XQ19:PB1
*/

uint16_t M1_Position=0;
uint16_t M2_Position=0;
uint16_t M3_Position=0;
uint16_t M4_Position=0;
uint16_t M5_Position=0;

uint16_t M1_Speed=0;
uint16_t M2_Speed=0;
uint16_t M3_Speed=0;
uint16_t M4_Speed=0;
uint16_t M5_Speed=0;


uint8_t phasecw[4] ={0x0c,0x06,0x03,0x09};// ƒÊ ±’Î
uint8_t phaseccw[4]={0x09,0x03,0x06,0x0c};// À≥ ±’Î

void MOTOR_GPIO_Config(void){
  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_AHBPeriphClockCmd( RCC_AHBPeriph_GPIOA, ENABLE);
	RCC_AHBPeriphClockCmd( RCC_AHBPeriph_GPIOB, ENABLE);
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4| GPIO_Pin_5| GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 |
																GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 |
																GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10| GPIO_Pin_11|
															  GPIO_Pin_12| GPIO_Pin_13| GPIO_Pin_14| GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
}
void SetMotor1(unsigned char InputData)
{
    if(InputData&0x01)
    {
        GPIO_ResetBits(M1_XQ0);
    }
    else
    {
        GPIO_SetBits(M1_XQ0);
    }
    if(InputData&0x02)
    {
        GPIO_ResetBits(M1_XQ1);
    }
    else
    {
        GPIO_SetBits(M1_XQ1);

    }
    if(InputData&0x04)
    {
        GPIO_ResetBits(M1_XQ2);
    }
    else
    {
        GPIO_SetBits(M1_XQ2);
    }
    if(InputData&0x08)
    {
        GPIO_ResetBits(M1_XQ3);
    }
    else
    {
        GPIO_SetBits(M1_XQ3);
    }
}
void SetMotor2(unsigned char InputData)
{
    if(InputData&0x01)
    {
        GPIO_SetBits(M2_XQ4);
    }
    else
    {
        GPIO_ResetBits(M2_XQ4);
    }
    if(InputData&0x02)
    {
        GPIO_SetBits(M2_XQ5);
    }
    else
    {
        GPIO_ResetBits(M2_XQ5);

    }
    if(InputData&0x04)
    {
        GPIO_SetBits(M2_XQ6);
    }
    else
    {
        GPIO_ResetBits(M2_XQ6);
    }
    if(InputData&0x08)
    {
        GPIO_SetBits(M2_XQ7);
    }
    else
    {
        GPIO_ResetBits(M2_XQ7);
    }
}
void SetMotor3(unsigned char InputData)
{
    if(InputData&0x01)
    {
        GPIO_SetBits(M3_XQ8);
    }
    else
    {
        GPIO_ResetBits(M3_XQ8);
    }
    if(InputData&0x02)
    {
        GPIO_SetBits(M3_XQ9);
    }
    else
    {
        GPIO_ResetBits(M3_XQ9);

    }
    if(InputData&0x04)
    {
        GPIO_SetBits(M3_XQ10);
    }
    else
    {
        GPIO_ResetBits(M3_XQ10);
    }
    if(InputData&0x08)
    {
        GPIO_SetBits(M3_XQ11);
    }
    else
    {
        GPIO_ResetBits(M3_XQ11);
    }
}
void SetMotor4(unsigned char InputData)
{
    if(InputData&0x01)
    {
        GPIO_SetBits(M4_XQ12);
    }
    else
    {
        GPIO_ResetBits(M4_XQ12);
    }
    if(InputData&0x02)
    {
        GPIO_SetBits(M4_XQ13);
    }
    else
    {
        GPIO_ResetBits(M4_XQ13);

    }
    if(InputData&0x04)
    {
        GPIO_SetBits(M4_XQ14);
    }
    else
    {
        GPIO_ResetBits(M4_XQ14);
    }
    if(InputData&0x08)
    {
        GPIO_SetBits(M4_XQ15);
    }
    else
    {
        GPIO_ResetBits(M4_XQ15);
    }
}
void SetMotor5(unsigned char InputData)
{
    if(InputData&0x01)
    {
        GPIO_SetBits(M5_XQ16);
    }
    else
    {
        GPIO_ResetBits(M5_XQ16);
    }
    if(InputData&0x02)
    {
        GPIO_SetBits(M5_XQ17);
    }
    else
    {
        GPIO_ResetBits(M5_XQ17);

    }
    if(InputData&0x04)
    {
        GPIO_SetBits(M5_XQ18);
    }
    else
    {
        GPIO_ResetBits(M5_XQ18);
    }
    if(InputData&0x08)
    {
        GPIO_SetBits(M5_XQ19);
    }
    else
    {
        GPIO_ResetBits(M5_XQ19);
    }
}

void Set_Speed(uint8_t Motor,uint16_t Speed){
		switch(Motor){
		case 1: 
			Target1_Speed=Speed;
		case 2:
			Target2_Speed=Speed;
		case 3:
			Target3_Speed=Speed;
		case 4:
			Target4_Speed=Speed;
		case 5:
			Target5_Speed=Speed;
		}	
}
void Set_Position(uint8_t Motor,uint16_t Position){
	switch(Motor){
		case 1: 
			M1_Position+=Position;
		case 2:
			M2_Position+=Position;
		case 3:
			M3_Position+=Position;
		case 4:
			M4_Position+=Position;
		case 5:
			M5_Position+=Position;
		}	
}

