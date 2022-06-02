#include "reg52.h"			 //此文件中定义了单片机的一些特殊功能寄存器

typedef unsigned int uint;	  //对数据类型进行声明定义
typedef unsigned char uchar;

#define GPIO_KEY P1				//对P1口进行宏定义

sbit beep=P1^5;						//宏定义蜂鸣器接口

void KeyDown(void);
void delay(uint i);
void BEEP(uint a);				//函数声明
	
char KeyValue=-1;	//用来存放读取到的键值

uint pwm[16]={10,20,30,40,50,60,70,80,90,100,110,120,130,140,150,160};//通过延时产生不同的频率信号

//主函数
void main(){							
	while(1){
		KeyValue=-1;
		KeyDown();
		if(KeyValue!=-1)
		{
			BEEP(pwm[KeyValue]);		
		}
	}
}

//按键扫描函数
void KeyDown(void){
	char a=0;
	GPIO_KEY=0x0f;
	if(GPIO_KEY!=0x0f)
	{
		delay(1000);
		if(GPIO_KEY!=0x0f)
		{	
			GPIO_KEY=0X0F;
			switch(GPIO_KEY)
			{
				case(0X07):	KeyValue=0;break;
				case(0X0b):	KeyValue=1;break;
				case(0X0d): KeyValue=2;break;
				case(0X0e):	KeyValue=3;break;
			}
			GPIO_KEY=0XF0;
			switch(GPIO_KEY)
			{
				case(0X70):	KeyValue=KeyValue;break;
				case(0Xb0):	KeyValue=KeyValue+4;break;
				case(0Xd0): KeyValue=KeyValue+8;break;
				case(0Xe0):	KeyValue=KeyValue+12;break;
			}
			
		}
	}
	while((a<50)&&(GPIO_KEY!=0xf0))
	{
		delay(100);
		a++;
	}
}

//蜂鸣器鸣响函数
void BEEP(uint a){			

	uint b=0;
	beep=0;
	while(b<450){
		beep=~beep;
		delay(a);
		b++;
	}
		
}

//延时函数
void delay(uint i){
	while(i--);	
}
