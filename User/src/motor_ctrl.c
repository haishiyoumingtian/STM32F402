#include "motor_ctrl.h"
#include "motor.h"
#include "tim.h"

uint16_t Initial_Speed= 100; 	//起步速度
uint16_t Motor1_Speed = 100;
uint16_t Motor2_Speed = 100;
uint16_t Motor3_Speed = 100;
uint16_t Motor4_Speed = 100;
uint16_t Motor5_Speed = 100;

uint16_t Target1_Speed = 100;  //目标速度
uint16_t Target2_Speed = 100;
uint16_t Target3_Speed = 100;
uint16_t Target4_Speed = 100;
uint16_t Target5_Speed = 100;

uint8_t Speed1Mode_Statue = 0;  //速度模式标志位
uint8_t Speed2Mode_Statue = 0;
uint8_t Speed3Mode_Statue = 0;
uint8_t Speed4Mode_Statue = 0;
uint8_t Speed5Mode_Statue = 0;

static uint16_t Speed_KP=4;
static uint16_t Speed_KI=1;
uint16_t Motor1_I_pool[6];
uint16_t Motor2_I_pool[6];
uint16_t Motor3_I_pool[6];
uint16_t Motor4_I_pool[6];
uint16_t Motor5_I_pool[6];


//速度模式，传入电机号与目标速度
void Speed_Mode(uint8_t Motor,uint16_t Speed,uint8_t Statue){
	if(Speed>=100&&Speed<=500)
		Set_Speed(Motor,Speed);
	switch(Motor){
		case 1:
			Speed1Mode_Statue = Statue;
		case 2:
			Speed2Mode_Statue = Statue;
		case 3:
			Speed3Mode_Statue = Statue;
		case 4:
			Speed4Mode_Statue = Statue;
		case 5:
			Speed5Mode_Statue = Statue;
	}
}
//位置模式，默认最大速度为200.
void Position_Mode(uint8_t Motor,uint16_t Position){
	Set_Position(Motor,Position);
}
void Motor_Ctrl(uint32_t arr){
	TIM2_Mode_Config(arr);
	TIM3_Mode_Config(arr);
	TIM14_Mode_Config(arr);
	TIM16_Mode_Config(arr);
	TIM17_Mode_Config(arr);
}
int Speed_PID(uint16_t Current_Speed,uint16_t Target_Speed,uint8_t Motor){
	int err;
	int i;
	switch (Motor){
		case 1:
			err = Target_Speed-Current_Speed;
			for(i=3;i>=0;i--){
				Motor1_I_pool[i+1]=Motor1_I_pool[i];
			}
			Motor1_I_pool[0]=err;
			Motor1_I_pool[5]=0;
			for(i=0;i<=4;i++){
				Motor1_I_pool[5]+=Motor1_I_pool[i];
			}
			if(err>0)Motor1_I_pool[5]+=err;
			else Motor1_I_pool[5]-=err;
			if(Motor1_I_pool[5]>=300){
				Motor1_I_pool[5]=300;
			}
			Current_Speed=Current_Speed+err*Speed_KP/10+Motor1_I_pool[5]*Speed_KI/10;
			return Current_Speed;
		case 2:
			err = Target_Speed-Current_Speed;
			for(i=3;i>=0;i--){
				Motor2_I_pool[i+1]=Motor2_I_pool[i];
			}
			Motor2_I_pool[0]=err;
			Motor2_I_pool[5]=0;
			for(i=0;i<=4;i++){
				Motor2_I_pool[5]+=Motor2_I_pool[i];
			}
			if(err>0)Motor2_I_pool[5]+=err;
			else Motor2_I_pool[5]-=err;
			if(Motor2_I_pool[5]>=300){
				Motor2_I_pool[5]=300;
			}
			Current_Speed=Current_Speed+err*Speed_KP/10+Motor2_I_pool[5]*Speed_KI/10;
			return Current_Speed;
		case 3:
			err = Target_Speed-Current_Speed;
			for(i=3;i>=0;i--){
				Motor3_I_pool[i+1]=Motor3_I_pool[i];
			}
			Motor3_I_pool[0]=err;
			Motor3_I_pool[5]=0;
			for(i=0;i<=4;i++){
				Motor3_I_pool[5]+=Motor3_I_pool[i];
			}
			if(err>0)Motor3_I_pool[5]+=err;
			else Motor3_I_pool[5]-=err;
			if(Motor3_I_pool[5]>=300){
				Motor3_I_pool[5]=300;
			}
			Current_Speed=Current_Speed+err*Speed_KP/10+Motor3_I_pool[5]*Speed_KI/10;
			return Current_Speed;
		case 4:
			err = Target_Speed-Current_Speed;
			for(i=3;i>=0;i--){
				Motor4_I_pool[i+1]=Motor4_I_pool[i];
			}
			Motor4_I_pool[0]=err;
			Motor4_I_pool[5]=0;
			for(i=0;i<=4;i++){
				Motor4_I_pool[5]+=Motor4_I_pool[i];
			}
			if(err>0)Motor4_I_pool[5]+=err;
			else Motor4_I_pool[5]-=err;
			if(Motor4_I_pool[5]>=300){
				Motor4_I_pool[5]=300;
			}
			Current_Speed=Current_Speed+err*Speed_KP/10+Motor4_I_pool[5]*Speed_KI/10;
			return Current_Speed;
		case 5:
			err = Target_Speed-Current_Speed;
			for(i=3;i>=0;i--){
				Motor5_I_pool[i+1]=Motor5_I_pool[i];
			}
			Motor5_I_pool[0]=err;
			Motor5_I_pool[5]=0;
			for(i=0;i<=4;i++){
				Motor5_I_pool[5]+=Motor5_I_pool[i];
			}
			if(err>0)Motor5_I_pool[5]+=err;
			else Motor5_I_pool[5]-=err;
			if(Motor5_I_pool[5]>=300){
				Motor5_I_pool[5]=300;
			}
			Current_Speed=Current_Speed+err*Speed_KP/10+Motor5_I_pool[5]*Speed_KI/10;
			return Current_Speed;
	}
	return 0;
}
void Speed_Adjustment(void){
	//电机1速度调整，TIM2
	if(Motor1_Speed!=Target1_Speed && Speed1Mode_Statue==1){
		Motor1_Speed=Speed_PID(Motor1_Speed,Target1_Speed,1);
		TIM2_Mode_Config(48000000/4/Motor1_Speed);
	}
	//电机2速度调整，TIM3
	if(Motor2_Speed!=Target2_Speed && Speed2Mode_Statue==1){
		Motor2_Speed=Speed_PID(Motor2_Speed,Target2_Speed,2);
		TIM3_Mode_Config(48000000/4/Motor2_Speed);
	}
	//电机3速度调整，TIM14
	if(Motor3_Speed!=Target3_Speed && Speed3Mode_Statue==1){
		Motor3_Speed=Speed_PID(Motor3_Speed,Target3_Speed,3);
		TIM14_Mode_Config(48000000/4/Motor3_Speed);
	}
	//电机4速度调整，TIM16
	if(Motor4_Speed!=Target4_Speed && Speed4Mode_Statue==1){
		Motor4_Speed=Speed_PID(Motor4_Speed,Target4_Speed,4);
		TIM16_Mode_Config(48000000/4/Motor4_Speed);
	}
	//电机5速度调整，TIM17
	if(Motor5_Speed!=Target5_Speed && Speed5Mode_Statue==1){
		Motor5_Speed=Speed_PID(Motor5_Speed,Target5_Speed,5);
		TIM17_Mode_Config(48000000/4/Motor5_Speed);
	}
}


