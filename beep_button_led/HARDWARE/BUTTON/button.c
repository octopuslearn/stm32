/*
KEY_UP---WK_UP---PA0
���¸ߵ�ƽ������

KEY2---PE2
KEY1---PE3
KEY0---PE4
���µ͵�ƽ������
*/

#include "button.h"


void BUTTON_Init()
{
/*�˴�����ʱ�ӳ�ʼ������*/	
//	RCC_AHB1PeriphClockLPModeCmd(RCC_AHB1Periph_GPIOE, ENABLE);
/*�˴�����GPIOE��ʼ������*/
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
//	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;	//���µ͵�ƽ������---����״̬
	
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	
	
	

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
//	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_DOWN;	//���¸ߵ�ƽ������---����״̬
	
	
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

//��˱���..\HARDWARE\BUTTON\button.c(38): warning: #940-D: missing return statement at end of non-void function "BUTTON_Value"
//�������ڱ���ʱ�����if else �е�return������������û��return��䣬���������Ϊ����
u8 BUTTON_Value()
{
/*���£�֧����������*/
/*	
	if(KEY2==0 || KEY1==0 || KEY0==0)	//�а�������
	{
		delay_ms(20);	//����
		if(KEY2==0)	return 3;
		else if(KEY1==0) return 2;
		else if(KEY0==0) return 1;
		else{}
	}
	return 0;	//�ް�������
*/	






	
/*���£���֧����������*/
	static u8 key_up = 1;	//�����ɿ���־������-1������-0
	if(key_up==1 && (KEY2==0 || KEY1==0 || KEY0==0))	//�а�������
	{
		key_up = 0;		//�������Ѿ�����
		delay_ms(50);	//����
		if(KEY2==0)	return 3;
		else if(KEY1==0) return 2;
		else if(KEY0==0) return 1;
	}
	else if(KEY2==1 && KEY1==1 && KEY0==1)	//û�а�������
	{
		key_up = 1;	
	}
	return 0;	//��Чֵ
	
	
	
	
	



/*���£���֧����������*/
/*���£�����	???���Ҳ�֪��ԭ��
	else if(KEY2==1 && KEY1==1 && KEY0==1)	//û�а�������
	{
		key_up = 1;	
		return 0;	//��Чֵ
	}
return 0;����д���⣬������led�İ���������Ҳ����
*/
/*
	static u8 key_up = 1;	//�����ɿ���־������-1������-0
	if(key_up==1 && (KEY2==0 || KEY1==0 || KEY0==0))	//�а�������
	{
		key_up = 0;		//�������Ѿ�����
		delay_ms(50);	//����
		if(KEY2==0)	return 3;
		else if(KEY1==0) return 2;
		else if(KEY0==0) return 1;
	}
	else if(KEY2==1 && KEY1==1 && KEY0==1)	//û�а�������
	{
		key_up = 1;	
		return 0;	//��Чֵ
	}
*/
//*/	

}

