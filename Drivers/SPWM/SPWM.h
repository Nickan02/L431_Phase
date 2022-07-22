/*
 * @Author       : Leeer
 * @Date         : 2022-07-07 20:31:05
 * @FilePath     : \MDK-ARMd:\keil\CubePreserve\L431_Phase\Drivers\SPWM\SPWM.h
 * @Description  : 
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SPWM_H
#define __SPWM_H
#include "stdint.h"
#include "main.h"
#include "tim.h"
extern TIM_HandleTypeDef htim1;
#define doublepi 								6.283185307   		// 2pi
#define Time_CLK 								(80000000/(Prescal+1))			// 最好能被80MHz整除,168/8 = 21MHz;
#define N												600
//#define Sin_F										50		// 50Hz的SPWM波-》500hz正弦波
#define Prescal             	  (8 -1)
// extern float n1_Temp,n2_Temp;
    /**TIM1 GPIO Configuration
    PA7     ------> TIM1_CH1N
    PA8     ------> TIM1_CH1
    PA10     ------> TIM1_CH3
		PB1     ------> TIM1_CH3N
    */
// float n1_RET(float AN_RET);
// float n2_RET(float M,float AN_RET);
void SinWave (float Sin_F);
void Out_SPWM(float Sin_F);
uint16_t TIM1_Per_Set(float Sin_FRQ);
//
/*静态函数，只在SPWM.C调用*/
static void MY_TIM1_Init(float Sin_F);
static void HAL_TIM1_MspPostInit(TIM_HandleTypeDef* timHandle);
static void MY_DMA_Init(void);
#endif /* __SPWM_H */



