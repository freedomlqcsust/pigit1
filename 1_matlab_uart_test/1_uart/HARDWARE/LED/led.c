#include "led.h"
//////////////////////////////////////////////////////////////////////////////////
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F407������
//LED��������
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2014/5/2
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved
//////////////////////////////////////////////////////////////////////////////////

//��ʼ��PF9��PF10Ϊ�����.��ʹ���������ڵ�ʱ��
//LED IO��ʼ��
void LED_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	//ʹ��GPIOIʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOI, ENABLE);
	//GPIOI5,GPIOi6,GPIOI7��ʼ������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	//��ͨ���ģʽ
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	//�������
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	//IO�ٶ�����Ϊ100MHz
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	//����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	//��ʼ��GPIO
	GPIO_Init(GPIOI, &GPIO_InitStructure);

	GPIO_SetBits(GPIOI, GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7); //GPIOF9,F10���øߣ�����

}






