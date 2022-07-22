/* Includes ------------------------------------------------------------------*/
#include "math.h"
#include "spwm.h"

//TIM_HandleTypeDef htim1;
float n1_Temp, n2_Temp;
float SinWave_Tab[N];
extern float Freq_Capture;
extern float PWM_Duty;
uint8_t flag=0;
/*************************************************
��������: n1_RET
��������: ����ϵ��
�������: Sin_FRQ
���ز���: SPWM��ϵ�������SinWave_Tab�õ�ռ�տ��
**************************************************/
static float n1_RET(float Sin_FRQ)
{
  static float temp;
  temp = Time_CLK;
  temp = temp / Sin_FRQ;
  temp = temp / N;
  temp = temp / 4;
  return temp; // Tc/4
}
// Tm = 1/Sin_FRQ;
// Tc = Tm/N;
// Tc = 1/Sin_FRQ*N;

// Tcy = 1/Time_CLK;		// ʱ�Ӽ�������

// Tc->Num = Tc/Tcy = Tc*Time_CLK = Time_CLK/(sin_FRQ*N);
/*************************************************
��������: n2_RET
��������: ����ϵ��
�������: M�����Ʊȣ�AN_RET��ϵ��
���ز���: AN_RET*M
**************************************************/
static float n2_RET(float M, float AN_RET)
{
  static float temp;
  temp = AN_RET;
  temp *= M; // Tc*a/4
  return temp;
}
//���Ϻ���ʵ��Ϊ��ʽ�Ĳ��
/*************************************************
��������: SinWave
��������: ����SPWM�����ұ�����ΪN
�������: ��
���ز���: ��
**************************************************/
void SinWave(float Sin_F)
{
  uint16_t i;
  for (i = 0; i < N; i++)
    SinWave_Tab[i] = sin(doublepi / N * (i + 0.75)); // ���ұ�
                                                     // mark[k] = (unsigned int)(Fs / Fc * (0.25 - a / 4 * sin(doublepi / N * (k + 0.75))));
	MY_TIM1_Init(Sin_F);
	Out_SPWM(Sin_F);
  HAL_TIM_PWM_Start_IT(&htim1, TIM_CHANNEL_1);
  HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start_IT(&htim1, TIM_CHANNEL_3);
  HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_3);

}
void Out_SPWM(float Sin_F)
{
	TIM1->ARR = TIM1_Per_Set(Sin_F); 
  n1_Temp = n1_RET(Sin_F);          // ��Sin_FHz��������ϵ��
  n2_Temp = n2_RET(0.707, n1_Temp); // 0.707=����֮���Ŷ�
}
/************************************************************************************************************/
//�߼���ʱ��1��ʼ��
//������TGA_FREQ ���ͣ�unsigned short ��λС�� Ŀ�����Ҳ�Ƶ�ʣ�ȡֵ��Χ��20~1000HZ
/************************************************************************************************************/
uint16_t TIM1_Per_Set(float Sin_FRQ)
{
  static float temp;
  temp = Time_CLK; // ��ʱ��ʱ��	Tcy = 1/Time_CLK��Tm = 1/Sin_FRQ�� Tc=Tm/Tcy;
  temp /= Sin_FRQ; // Ƶ��ΪSin_FRQ�����Ҳ�������һ���������õļ���ֵ
  temp /= N;       // �ز�һ����������Ӧ�ļ���ֵ��Tc��Ӧ��������
  temp /= 2;       // �Ӽ�ģʽ�µ����ڼ���ֵ
  return (uint16_t)temp;
}
/**
 * @brief �ⲿ�жϼ�⵽�½��ӽ���ص�����
 * 
 * @param GPIO_Pin 
 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == GPIO_PIN_9){
		flag=1;
	}
}

void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
{
  static uint16_t i=0;
  uint16_t temp;
  if (htim == &htim1&&flag==1)
  {
    temp = (uint16_t)(n1_Temp - n2_Temp * SinWave_Tab[i++]); //д��Ƚ�ͨ��1��Ԥװ�ؼĴ���
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, temp);
		temp = (uint16_t)(n1_Temp - n2_Temp * SinWave_Tab[i]); //д��Ƚ�ͨ��1��Ԥװ�ؼĴ���
   __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, temp); 
    if (i == N){
   i = 0;flag=0;
/**
 * @brief ��Ƶ������
 * //			if(Freq_Capture>10&&Freq_Capture<100)
//			{
//   if(PWM_Duty>0.50&&PWM_Duty<=0.8)
//				Out_SPWM(Freq_Capture+1);
//			else if(PWM_Duty>0.80&&PWM_Duty<=0.99)
//				Out_SPWM(Freq_Capture+0.3);
//			else if(PWM_Duty>0.99&&PWM_Duty<=0.995)
//				Out_SPWM(Freq_Capture+0.1);
//			else if(PWM_Duty>0.995&&PWM_Duty<=0.999)
//				Out_SPWM(Freq_Capture+0.05);
//			
//      else if(PWM_Duty<0.50&&PWM_Duty>=0.20)
//        Out_SPWM(Freq_Capture-1);
//      else if(PWM_Duty<0.20&&PWM_Duty>=0.01)
//        Out_SPWM(Freq_Capture-0.30);
//      else if(PWM_Duty<0.01&&PWM_Duty>=0.005)
//        Out_SPWM(Freq_Capture-0.10);
//      else if(PWM_Duty<0.005&&PWM_Duty>=0.001)
//        Out_SPWM(Freq_Capture-0.05);
//      else 
//        Out_SPWM(Freq_Capture);
 */
		}
  }
}

static void MY_TIM1_Init(float Sin_F)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* TIM1 clock enable */
  __HAL_RCC_TIM1_CLK_ENABLE();

  /* TIM1 interrupt Init */
  HAL_NVIC_SetPriority(TIM1_CC_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(TIM1_CC_IRQn);

  /* USER CODE END TIM1_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};
  TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = Prescal;
  htim1.Init.CounterMode = TIM_COUNTERMODE_CENTERALIGNED2;
  htim1.Init.Period = TIM1_Per_Set(Sin_F);
	htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterOutputTrigger2 = TIM_TRGO2_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
  {
    Error_Handler();
  }
  sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
  sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
  sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
  sBreakDeadTimeConfig.DeadTime = 0;
  sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
  sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
  sBreakDeadTimeConfig.BreakFilter = 0;
  sBreakDeadTimeConfig.Break2State = TIM_BREAK2_DISABLE;
  sBreakDeadTimeConfig.Break2Polarity = TIM_BREAK2POLARITY_HIGH;
  sBreakDeadTimeConfig.Break2Filter = 0;
  sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
  if (HAL_TIMEx_ConfigBreakDeadTime(&htim1, &sBreakDeadTimeConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */
  HAL_TIM1_MspPostInit(&htim1);
  /* USER CODE END TIM1_Init 2 */
}

static void HAL_TIM1_MspPostInit(TIM_HandleTypeDef *timHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if (timHandle->Instance == TIM1)
  {
   /* USER CODE BEGIN TIM1_MspPostInit 0 */

  /* USER CODE END TIM1_MspPostInit 0 */

    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**TIM1 GPIO Configuration
    PA7     ------> TIM1_CH1N
    PB1     ------> TIM1_CH3N
    PA8     ------> TIM1_CH1
    PA10    ------> TIM1_CH3
    */
    GPIO_InitStruct.Pin = GPIO_PIN_7|GPIO_PIN_8;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF1_TIM1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_1;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF1_TIM1;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF1_TIM1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* USER CODE BEGIN TIM1_MspPostInit 1 */

    /* USER CODE END TIM1_MspPostInit 1 */
  }
}

extern void TIM1_CC_IRQHandler(void)
{
  /* USER CODE BEGIN TIM1_CC_IRQn 0 */

  /* USER CODE END TIM1_CC_IRQn 0 */
  HAL_TIM_IRQHandler(&htim1);
  /* USER CODE BEGIN TIM1_CC_IRQn 1 */

  /* USER CODE END TIM1_CC_IRQn 1 */
}
