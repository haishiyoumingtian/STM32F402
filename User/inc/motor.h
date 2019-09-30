#ifndef __MOTOR_H
#define __MOTOR_H

#include "stm32f0xx.h"
#include "stm32f0xx_conf.h"

extern uint8_t phasecw[4];// 逆时针
extern uint8_t phaseccw[4];// 顺时针


#define M1_XQ0 GPIOA,GPIO_Pin_5 //电机1引脚定义
#define M1_XQ1 GPIOB,GPIO_Pin_8 //电机1引脚定义
#define M1_XQ2 GPIOB,GPIO_Pin_9 //电机1引脚定义
#define M1_XQ3 GPIOB,GPIO_Pin_3 //电机1引脚定义

#define M2_XQ4 GPIOB,GPIO_Pin_4 //电机2引脚定义
#define M2_XQ5 GPIOB,GPIO_Pin_5 //电机2引脚定义
#define M2_XQ6 GPIOB,GPIO_Pin_6 //电机2引脚定义
#define M2_XQ7 GPIOB,GPIO_Pin_7 //电机2引脚定义

#define M3_XQ8  GPIOB,GPIO_Pin_2  //电机3引脚定义
#define M3_XQ9  GPIOB,GPIO_Pin_10 //电机3引脚定义
#define M3_XQ10 GPIOB,GPIO_Pin_11 //电机3引脚定义
#define M3_XQ11 GPIOB,GPIO_Pin_12 //电机3引脚定义

#define M4_XQ12 GPIOB,GPIO_Pin_13 //电机4引脚定义
#define M4_XQ13 GPIOB,GPIO_Pin_14 //电机4引脚定义
#define M4_XQ14 GPIOB,GPIO_Pin_15 //电机4引脚定义
#define M4_XQ15 GPIOA,GPIO_Pin_8  //电机4引脚定义

#define M5_XQ16 GPIOA,GPIO_Pin_6 //电机5引脚定义
#define M5_XQ17 GPIOA,GPIO_Pin_7 //电机5引脚定义
#define M5_XQ18 GPIOB,GPIO_Pin_0 //电机5引脚定义
#define M5_XQ19 GPIOB,GPIO_Pin_1 //电机5引脚定义

extern uint16_t M1_Position; //电机位置输入
extern uint16_t M2_Position; //电机位置输入
extern uint16_t M3_Position; //电机位置输入
extern uint16_t M4_Position; //电机位置输入
extern uint16_t M5_Position; //电机位置输入

extern uint16_t M1_Speed; //电机速度输入
extern uint16_t M2_Speed; //电机速度输入
extern uint16_t M3_Speed; //电机速度输入
extern uint16_t M4_Speed; //电机速度输入
extern uint16_t M5_Speed; //电机速度输入

void MOTOR_GPIO_Config(void);
void SetMotor1(unsigned char InputData); 
void SetMotor2(unsigned char InputData);
void SetMotor3(unsigned char InputData);
void SetMotor4(unsigned char InputData);
void SetMotor5(unsigned char InputData);
void Set_Speed(uint8_t Motor,uint16_t Speed);
void Set_Position(uint8_t Motor,uint16_t Position);








#endif /* __DELAY_H */

