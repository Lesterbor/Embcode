/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : ElectronicOrgan.c
  * @brief          : ElectronicOrgan program body
  * @author         : Lesterbor
  * @time	    	: 2020-02-21
  *
  ******************************************************************************
  * @attention
  *
  *
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

	#include "reg52.h"

/* USER CODE END Includes */
/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PT */

	#define GPIO_KEY P1
	
	typedef unsigned int uint;
	typedef unsigned char uchar;

	sbit beep=P1^5;

	char KeyValue=-1;

	//通过延时产生不同的频率信号
	uint pwm[16]={10,20,30,40,50,60,70,80,90,100,110,120,130,140,150,160};

/* USER CODE END PT */

/* Exported functions prototypes ---------------------------------------------*/
/* USER CODE BEGIN EFP */

	void KeyDown(void);
	void delay(uint i);
	void BEEP(uint a);

/* USER CODE END EFP */
/* Function definition -------------------------------------------------------*/
/* USER CODE BEGIN FD */

/**
  * @Function name  main
  * @Introduce      主函数						
  * @Return 	    NULL
  */
  void main(){							
	while(1){
		KeyValue=-1;
		KeyDown();
		if(KeyValue!=-1){
			BEEP(pwm[KeyValue]);		
		}
	}
  }

/**
  * @Function name  KeyDown
  * @Introduce      按键扫描函数						
  * @Return 	    NULL
  */
  void KeyDown(void){
	char a=0;
	GPIO_KEY=0x0f;
	if(GPIO_KEY!=0x0f){
		delay(1000);
		if(GPIO_KEY!=0x0f){	
			GPIO_KEY=0X0F;
			switch(GPIO_KEY){
				case(0X07):	KeyValue=0;break;
				case(0X0b):	KeyValue=1;break;
				case(0X0d): KeyValue=2;break;
				case(0X0e):	KeyValue=3;break;
			}
			GPIO_KEY=0XF0;
			switch(GPIO_KEY){
				case(0X70):	KeyValue=KeyValue;break;
				case(0Xb0):	KeyValue=KeyValue+4;break;
				case(0Xd0): KeyValue=KeyValue+8;break;
				case(0Xe0):	KeyValue=KeyValue+12;break;
			}
			
		}
	}
	while((a<50)&&(GPIO_KEY!=0xf0)){
		delay(100);
		a++;
	}
}
/**
  * @Function name  BEEP
  * @Introduce      蜂鸣器鸣响函数						
  * @Return 	    NULL
  */
  void BEEP(uint a){			
	uint b=0;
	beep=0;
	while(b<450){
		beep=~beep;
		delay(a);
		b++;
	}
 		
  }
/**
  * @Function name  delay
  * @Introduce      延时函数					
  * @Return 	    NULL
  */
  void delay(uint i){
	while(i--);	
  }
