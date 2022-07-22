
#ifndef __PID_H_
#define __PID_H_
#include "main.h"

/*
P:������(��������)Խ�󣬿������ķŴ���ԽС�����ز���������Խƽ�ȣ�
			������ԽС���������ķŴ���Խ�󣬱��ز���������Խ������

I:�����������õ�ʵ�ʾ��Ǹı����������ı仯���ʣ�
���������ͨ���������õ�������ڱ������õ���������һ��ʱ���������ġ�
����ʱ��С����ʾ�����ٶȴ󣬻������þ�ǿ����֮������ʱ�ʴ���������þ�����
�������ʱ������󣬱�ʾû�л������ã��������ͳ�Ϊ��������������


D:�������Ծ�źź�΢����һ��ʼ��������仯ֵ��΢��������ʧ�������仯�ı�ֵ����΢�ַŴ���Kd��
��΢�����棬΢�։���ĵ�λ��ʱ�䣬����΢��ʱ��(����΢������)Ϊ���ȡ��΢�ֵĹ��ܡ�



*/




typedef struct 
{ 
		float P;//����	
		float	I;		//����
		float	D;		//΢��			
		float	limit;
		float Integral;				//����
		float Last_Error;		//�����ϴε�δ�ﵽĿ���ֵ
		float Previous_Error;		//��һ�ε����
}PID_InitTypeDef;

//typedef struct
//{
//  float Integral;				//����
//  float Last_Error;		//�����ϴε�δ�ﵽĿ���ֵ
//  float Previous_Error;		//��һ�ε����
//}Error;


//float PID_Control(Error *Element_sptr, PID *Control_pid, float Input, float Point);
uint16_t PID_Error_Deal(double Average_Vol,uint16_t MAX,uint16_t MIN,uint16_t	Output_Duty,float Target_Voltage,PID_InitTypeDef *PID_Parameter);
#endif

