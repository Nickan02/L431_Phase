#ifndef _KEY_H
#define _KEY_H
#include "main.h"
#include "gpio.h"
//////////////////////////////////////////////////////////////////////////////////
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F103������
//KEY��������
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2019/11/15
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved
//////////////////////////////////////////////////////////////////////////////////

//����ķ�ʽ��ͨ��λ��������ʽ��ȡIO
//#define KEY0        PCin(5) 	//KEY0����PC5
//#define KEY1        PAin(15) 	//KEY1����PA15
//#define WK_UP       PAin(0)	    //WKUP����PA0

//����ķ�ʽ��ͨ��ֱ�Ӳ���HAL�⺯����ʽ��ȡIO
#define KEY1       	HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_10)  //KEY3����PB10
#define KEY2       	HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_11)  //KEY4����PB11
#define KEY3       	HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_0)   //KEY3����PB0
#define KEY4     		HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_1)   //KEY4����PB1
#define KEY1_PRES 	1
#define KEY2_PRES		2
#define KEY3_PRES   3
#define KEY4_PRES   4
void KEY_Init(void);
uint8_t KEY_Scan(uint8_t mode);

#endif
