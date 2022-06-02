#include "reg52.h"			 //���ļ��ж����˵�Ƭ����һЩ���⹦�ܼĴ���

typedef unsigned int uint;	  //���������ͽ�����������
typedef unsigned char uchar;

#define GPIO_KEY P1				//��P1�ڽ��к궨��

sbit beep=P1^5;						//�궨��������ӿ�

void KeyDown(void);
void delay(uint i);
void BEEP(uint a);				//��������
	
char KeyValue=-1;	//������Ŷ�ȡ���ļ�ֵ

uint pwm[16]={10,20,30,40,50,60,70,80,90,100,110,120,130,140,150,160};//ͨ����ʱ������ͬ��Ƶ���ź�

//������
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

//����ɨ�躯��
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

//���������캯��
void BEEP(uint a){			

	uint b=0;
	beep=0;
	while(b<450){
		beep=~beep;
		delay(a);
		b++;
	}
		
}

//��ʱ����
void delay(uint i){
	while(i--);	
}
