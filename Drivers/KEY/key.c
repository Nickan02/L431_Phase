#include "key.h"
#include "delay.h"


//������ʼ������
void KEY_Init(void)
{

    GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_0|GPIO_PIN_1;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}


//����������
//���ذ���ֵ
//mode:0,��֧��������;1,֧��������;
//0��û���κΰ�������
//1��WKUP���� WK_UP
//ע��˺�������Ӧ���ȼ�,KEY1>KEY2>KEY3>KEY4!!
uint8_t KEY_Scan(uint8_t mode)
{
    static uint8_t key_up=1;     //�����ɿ���־
    if(mode)key_up=1;    //֧������
    if(key_up&&(KEY1==0||KEY2==0||KEY3==0||KEY4==0))
    {
        key_up=0;
        if(KEY1==0)       return KEY1_PRES;
        else if(KEY2==0) 	return KEY2_PRES;
        else if(KEY3==0) 	return KEY3_PRES;
        else if(KEY4==0) 	return KEY4_PRES;
        else	return 0;
    } else if(KEY1==1&&KEY2==1&&KEY3==1&&KEY4==1)key_up=1;
    return 0;   //�ް�������
}

