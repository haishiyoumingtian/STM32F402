#ifndef __MOTOR_CTRL_H
#define	__MOTOR_CTRL_H

#include "stm32f0xx.h"

extern uint16_t Initial_Speed; 	//起步速度
extern uint16_t Motor1_Speed;
extern uint16_t Motor2_Speed;
extern uint16_t Motor3_Speed;
extern uint16_t Motor4_Speed;
extern uint16_t Motor5_Speed;

extern uint16_t Target1_Speed;  //目标速度
extern uint16_t Target2_Speed;
extern uint16_t Target3_Speed;
extern uint16_t Target4_Speed;
extern uint16_t Target5_Speed;

extern uint8_t Speed1Mode_Statue;  //速度模式标志位
extern uint8_t Speed2Mode_Statue;
extern uint8_t Speed3Mode_Statue;
extern uint8_t Speed4Mode_Statue;
extern uint8_t Speed5Mode_Statue;


extern uint16_t Initial_Speed;
#define Initial_Arr  48000000/4/Initial_Speed

void Speed_Mode(uint8_t Motor,uint16_t Speed,uint8_t Statue);
void Position_Mode(uint8_t Motor,uint16_t Position);
void Motor_Ctrl(uint32_t arr);
int Speed_PID(uint16_t Current_Speed,uint16_t Target_Speed,uint8_t Motor);
void Speed_Adjustment(void);


#endif 
